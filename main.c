
#include "GameCore.h"
#include "MapRenderer.h"
#include "InputEvents.h"
#include "Rendering.h"
#include "LinkedList.h"
#include "FileIO.h"
#include "CollisionEvents.h"
#include "net_utils.h"
#include <windows.h>
#include "NetCode.h"

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

void animateEntitys(GameData data){
    //count slows the animation todo need to remove that and make it native to the rendering loop
    static int count =0;
    node **tracer = &data.start;
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
void moveEntity(GameData data){
    node **tracer = &data.start;
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

    gameData.outrender=rend;
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
    LoadBigMapFile("dtemp.map",&gameData);
    LoadTileData(&gameData);
    EntityPacket tmp;

    gameData.start=NULL;
    gameData.currentRoom=initRooms();
    Entity player= readEntityFromFile("play.ent",rend);
    player.ID=0;
    Insertnode(&gameData.start,NewElement(player));
    Entity other=readEntityFromFile("play.ent",rend);
    other.ID=1;
    Entity *entity=Findnode(&gameData.start,0);
    clock_t start, end;
    double cpu_time_used=0.0;
    SDL_RenderClear(rend);
    int running=1;
    SDL_Event event;
    startServerCon(&gameData);
    while(running) {
        start=clock();
        int states = 0;
        // Process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        // clear old frame
        SDL_RenderClear(rend);

        //game logic
        SDL_Rect re;
        re.w = gameData.window_w - 64;
        re.h = gameData.window_h - 64;
        re.x = 32;
        re.y = 32;


        linkEntityToUserInput(Findnode(&gameData.start, 0), gameData);
        bindEntitysToRect(gameData, re);
        moveEntity(gameData);

        tmp.x = entity->sprite.x;
        tmp.y = entity->sprite.y;
        tmp.state = entity->state;
        tmp.ID = 100;
        //creating next frame
        renderMapFromFile(rend,&gameData);

        doorTiggerCollition(&gameData);

        //SDL_RenderDrawRect(rend,&re);
        //renderRoomCode(&gameData,rend,font,color);
        //renderTriggerBox(&gameData,rend);
        //renderEntityBoxList(gameData,rend);
        renderEntitys(gameData,rend);

        //present to screeen
        SDL_RenderPresent(rend);
        animateEntitys(gameData);
        end = clock();
        cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
    }

    TTF_CloseFont(font);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
