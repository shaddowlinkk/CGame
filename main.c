
#include "GameCore.h"
#include "MapRenderer.h"
#include "InputEvents.h"
#include "Rendering.h"
#include "LinkedList.h"
#include "FileIO.h"
#include "CollisionEvents.h"
//#include "CollisionDetection.h"
/**
 * This function moves the cutting SDL_Rect to the next frame of the animation
 * @param entity what ever entity you are trying to animate.
 * @param state the animation state that corresponds to the action you are trying to animate
 */
void animate(Entity *entity, int state){
    //count slows the animation todo need to remove that and make it native to the rendering loop
    static int count =0;
    if(count==3) {
        count=0;
        entity->cutter.y = (entity->cutter.h*state);
        entity->cutter.x = (entity->cutter.w * (((entity->cutter.x / entity->cutter.w)+1)% (entity->animationStates[state]-1)) );
    }
    count++;
}

void animateEntitys(GameData *data){
    //count slows the animation todo need to remove that and make it native to the rendering loop
    static int count =0;
    node **tracer = &data->start;
    if(!*tracer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"no list data in entity linked list 6");
    }else {
        if (count == 3) {
            count = 0;
            while (*tracer) {
                (*tracer)->item.cutter.y = ((*tracer)->item.cutter.h * (*tracer)->item.state);
                (*tracer)->item.cutter.x = ((*tracer)->item.cutter.w * ((((*tracer)->item.cutter.x / (*tracer)->item.cutter.w) + 1) % ((*tracer)->item.animationStates[(*tracer)->item.state] - 1)));
                tracer = &(*tracer)->next;
            }

        }
        count++;
    }
}

/**
 * moves an entity based on velocity
 * @param entity the entity that you want to move
 */
void moveEntity(GameData *data){
    node **tracer = &data->start;
    if(!*tracer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"no list data in entity linked list 3");
    }else {
        while (*tracer) {
            (*tracer)->item.sprite.x += (*tracer)->item.velx;
            (*tracer)->item.sprite.y += (*tracer)->item.vely;
            tracer = &(*tracer)->next;
        }
    }
}



int main(int argc, char **argv) {
    //todo update rendering and inputEvents so that thay pass a ptr not all of gameData
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    srand(time(0));
    GameData gameData;
    SDL_Window *win = SDL_CreateWindow("CGame",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,(mapsize*32),mapsize*32,SDL_WINDOW_OPENGL);
    SDL_GetWindowSize(win,&gameData.window_w,&gameData.window_h);
    if (!win){
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *rend = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(rend,255,255,255,255);
    if(!rend){
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 2;
    }
    SDL_Surface *s = IMG_Load(".\\Textures\\Floor.png");
    gameData.GroundSheet=SDL_CreateTextureFromSurface(rend,s);
    SDL_FreeSurface(s);
    TTF_Font * font = TTF_OpenFont("arial.ttf", 25);
    SDL_Color color = { 255, 255, 255 };

/*    Entity new;
    new.ID=0;
    new.spriteSheet=tex;
    new.sprite.h=32;
    new.sprite.w=16;
    new.cutter.h=32;
    new.cutter.w=16;
    new.cutter.x=0;
    new.cutter.y=0;
    new.sprite.x=gameData.window_w/2;
    new.sprite.y=gameData.window_h/2;
    new.animationStates[0]=7;
    new.animationStates[1]=11;
    new.animationStates[2]=11;
    new.animationStates[3]=8;
    new.animationStates[4]=9;
    new.animationStates[5]=16;
    memset(new.textureName,0x00,sizeof(20));
    strcpy(new.textureName,"test.png");*/


    //writeToFile(&new);

    //inisalizing the list and loading in data
    SDL_Surface  *surface = IMG_Load(".\\Textures\\inv.png");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);

    Entity inv;
    inv.cutter.x=0;
    inv.cutter.y=0;
    inv.cutter.w=172;
    inv.cutter.h=60;
    inv.sprite.w=172;
    inv.sprite.h=60;
    inv.sprite.x=32;
    inv.sprite.y=32;
    inv.spriteSheet=tex;
    inv.state=0;

    gameData.inventory=inv;

    LoadBigMapFile("dtemp.map",&gameData);
    LoadTileData(&gameData);

    gameData.start=NULL;
    gameData.currentRoom=initRooms();
    Insertnode(&gameData.start,NewElement(readEntityFromFile("play.ent",rend)));



    SDL_RenderClear(rend);
    int running=1;
    SDL_Event event;
    while(running) {
        int states=0;
        // Process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }else if (event.type == SDL_KEYDOWN){
                if(event.key.keysym.scancode==SDL_SCANCODE_F2){
                    gameData.inventory.state= ((gameData.inventory.state+1)%2);
                }
            }
        }
        // clear old frame
        SDL_RenderClear(rend);

        //game logic
        SDL_Rect re;
        re.w=gameData.window_w-64;
        re.h=gameData.window_h-64;
        re.x=32;
        re.y=32;


        linkEntityToUserInput(Findnode(&gameData.start,0),&gameData);
        bindEntitysToRect(&gameData,re);
        moveEntity(&gameData);

        //creating next frame
        renderMapFromFile(rend,&gameData);

        doorTiggerCollition(&gameData);

        SDL_RenderDrawRect(rend,&re);
        renderRoomCode(&gameData,rend,font,color);
        renderTriggerBox(&gameData,rend);
        renderEntityBoxList(&gameData,rend);
        renderEntitys(&gameData,rend);
        if (gameData.inventory.state!=0){
            Entity *temp = Findnode(&gameData.start,0);
            gameData.inventory.sprite.x=temp->sprite.x-(172/2)+(temp->cutter.w/2);
            gameData.inventory.sprite.y=temp->sprite.y-(60);
            SDL_RenderCopy(rend,gameData.inventory.spriteSheet,&gameData.inventory.cutter,&gameData.inventory.sprite);
        }

        //present to screeen
        SDL_RenderPresent(rend);
        animateEntitys(&gameData);
    }

    TTF_CloseFont(font);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
