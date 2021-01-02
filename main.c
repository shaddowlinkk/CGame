
#include "GameCore.h"
#include "MapRenderer.h"
#include "InputEvents.h"
#include "Rendering.h"
#include "LinkedList.h"
#include "FileIO.h"
#include "CollisionEvents.h"
#include "BoundingboxUtil.h"
#include "Room.h"
#include "CollisionDetection.h"
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
/**
 * This function moves the cutting SDL_Rect to the next frame of the animation
 * @param entity what ever entity you are trying to animate.
 * @param state the animation state that corresponds to the action you are trying to animate
 */
void animate(Entity *entity, int state){
    // todo need to remove that and make it native to the rendering loop
        entity->cutter.y = (entity->cutter.h*state);
        entity->cutter.x = (entity->cutter.w * (((entity->cutter.x / entity->cutter.w)+1)% (entity->animationStates[state]-1)));

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
                animate(&(*tracer)->item,(*tracer)->item.state);
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
            setBoundingBox(&(*tracer)->item.box,(*tracer)->item.sprite.x,(*tracer)->item.sprite.y);
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



    //inisalizing the list and loading in data
/*    SDL_Surface  *surface = IMG_Load(".\\Textures\\inv.png");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend,surface);
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
    inv.box=initBoundingBox(0,0,60,172);
    memset(inv.textureName,0x00,sizeof(20));
    strcpy(inv.textureName,"inv.png");
    inv.state=0;
    writeEntityToFile("invent.ent",&inv);

    surface = IMG_Load(".\\Textures\\test.png");
    tex = SDL_CreateTextureFromSurface(rend,surface);
    Entity ply;
    ply.ID=0;
    ply.cutter.x=0;
    ply.cutter.y=0;
    ply.cutter.w=16;
    ply.cutter.h=32;
    ply.sprite.w=16;
    ply.sprite.h=32;
    ply.sprite.x=352;
    ply.sprite.y=352;
    ply.spriteSheet=tex;
    ply.state=0;
    memset(ply.animationStates,0x00,sizeof(15));
    ply.animationStates[0]=7;
    ply.animationStates[1]=11;
    ply.animationStates[2]=11;
    ply.animationStates[3]=8;
    ply.animationStates[4]=9;
    ply.animationStates[5]=16;
    ply.velx=0;
    ply.vely=0;
    ply.box=initBoundingBox(352,352,32,16);;
    memset(ply.textureName,0x00,sizeof(20));
    strcpy(ply.textureName,"test.png");
    writeEntityToFile("player.ent",&ply);
    SDL_FreeSurface(surface);*/

    gameData.inventory=readEntityFromFile("invent.ent",rend);
//    gameData.inventory=inv;


    LoadBigMapFile("newmap.map",&gameData);
    LoadTileData(&gameData);

    gameData.start=NULL;
    gameData.currentRoom=initRooms();
    Insertnode(&gameData.start,NewElement(readEntityFromFile("player.ent",rend)));
//    Insertnode(&gameData.start,NewElement(ply));

    BoundingBox testBox = initBoundingBox(100,100,20,10);
    int count=0;
    Entity *player = Findnode(&gameData.start,0);

    SDL_RenderClear(rend);
    int running=1;
    SDL_Rect re;
    re.w=gameData.window_w-64;
    re.h=gameData.window_h-64;
    re.x=32;
    re.y=32;
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
                }/*
                if(event.key.keysym.scancode==SDL_SCANCODE_F3){
                    count+=5;
                    rotateBoundingBox(&testBox,count);
                }
                if(event.key.keysym.scancode==SDL_SCANCODE_W){
                    moveBoundingBox(&testBox,0,-1);
                }
                if(event.key.keysym.scancode==SDL_SCANCODE_A){
                    moveBoundingBox(&testBox,-1,0);
                }
                if(event.key.keysym.scancode==SDL_SCANCODE_S){
                    moveBoundingBox(&testBox,0,1);
                }
                if(event.key.keysym.scancode==SDL_SCANCODE_D){
                    moveBoundingBox(&testBox,1,0);
                }*/
            }
        }
        // clear old frame
        SDL_RenderClear(rend);

        //game logic



        linkEntityToUserInput(Findnode(&gameData.start,0),&gameData);
        //bindEntitysToRect(&gameData,re);
        staticObjectCollision(player, gameData.currentRoom->staticBlocks);
        moveEntity(&gameData);

        //creating next frame
        renderMapFromFile(rend,&gameData);

        doorTiggerCollision(&gameData);

        //renderRoomCode(&gameData,rend,font,color);
        //renderTriggerBox(&gameData,rend);
        //renderEntityBoxList(&gameData,rend);
        //renderWallBox(&gameData,rend);
        //renderBoundingBox(&player->box,rend);
        //SDL_RenderDrawRect(rend,&re);
        renderEntitys(&gameData,rend);
        renderInventory(&gameData,rend);
;

        //present to screee
        SDL_RenderPresent(rend);
        animateEntitys(&gameData);
    }

    TTF_CloseFont(font);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
