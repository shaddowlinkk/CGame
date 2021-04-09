//
// Created by nathan on 4/9/2021.
//

#include "base_code.h"

#include "MapRenderer.h"
#include "InputEvents.h"
#include "Rendering.h"
#include "LinkedList.h"
#include "FileIO.h"
#include "CollisionEvents.h"
#include "BoundingboxUtil.h"
#include "Room.h"
#include "CollisionDetection.h"
//#define MAX(a,b) (((a) > (b)) ? (a) : (b))

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

DWORD WINAPI mainSystem(void *vararg) {
    SystemData *system=(SystemData *)vararg;
    //todo update rendering and inputEvents so that thay pass a ptr not all of gameData
    srand(time(0));
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
    int running;
    Entity *player;
    DWORD wait = WaitForSingleObject(system->LockGameData, 2);
    if (wait==WAIT_OBJECT_0) {
        system->gameData->inventory = readEntityFromFile("invent.ent", *system->render);
//    system->gameData.inventory=inv;


        LoadBigMapFile("dtemp.map", system->gameData);
        LoadTileData(system->gameData);

        system->gameData->start = NULL;
        system->gameData->currentRoom = initRooms();
        Insertnode(&system->gameData->start, NewElement(readEntityFromFile("player.ent", *system->render)));
//    Insertnode(&system->gameData.start,NewElement(ply));

        BoundingBox testBox = initBoundingBox(100, 100, 20, 10);
        int count = 0;
        player = Findnode(&system->gameData->start, 0);

        running = 1;
        SDL_Rect re;
        re.w = system->gameData->window_w - 64;
        re.h = system->gameData->window_h - 64;
        re.x = 32;
        re.y = 32;
        ReleaseMutex(system->LockGameData);
    }else{
        running =0;
    }
    SDL_Event event;
    while(running) {
        DWORD wait = WaitForSingleObject(system->mainSystem, INFINITE);
        if (wait==WAIT_OBJECT_0) {
            int states = 0;
            // Process events
             wait = WaitForSingleObject(system->LockGameData, 2);
            if (wait == WAIT_OBJECT_0) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        running = 0;
                    } else if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.scancode == SDL_SCANCODE_F2) {
                            system->gameData->inventory.state = ((system->gameData->inventory.state + 1) % 2);
                        }
                        /* if(event.key.keysym.scancode==SDL_SCANCODE_F3){
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
                //linkEntityToUserInput(Findnode(&system->gameData->start, 0), system->gameData);
                //staticObjectCollision(player, system->gameData->currentRoom->staticBlocks);
                // moveEntity(system->gameData);
                ReleaseMutex(system->LockGameData);
                SetEvent(system->rendering);
            } else {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "no mutex");
            }
            ResetEvent(system->mainSystem);
        }
    }


    return 0;
}
