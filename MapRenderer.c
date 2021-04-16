//
// Created by nathan on 9/2/2020.
//

#include "MapRenderer.h"
#include "BoundingboxUtil.h"
#include "LinkedList.h"
/**
 * renders the backbround map;
 * @param rend renderer
 * @param gameData current states of the gloabl game data
 */
void rendermap(SDL_Renderer *rend,GameData *gameData){
    // temp def of a tile
    MapTile ground;
    ground.tileRect.h=32;
    ground.tileRect.w=32;
    ground.tileRect.x=0;
    ground.tileRect.y=0;
    SDL_Surface *s = IMG_Load("Ground02.png");
    ground.tileTexture=SDL_CreateTextureFromSurface(rend,s);


    for (int y=0;y<((int)(gameData->window_h/32));y++){
        for (int x=0;x<((int)(gameData->window_w/32));x++){
            ground.tileRect.x=(x*32);
            ground.tileRect.y=(y*32);
            SDL_RenderCopy(rend,ground.tileTexture,NULL,&ground.tileRect);
        }
    }
}
/**
 * this function renders the map from gamedata map data
 * @param rend SDl_render that you want to render to
 * @param gameData the game data that you want to read from
 */
void renderMapFromFile(SDL_Renderer *rend,GameData *gameData){
    // todo re write to use facade texture
    MapTile ground;
    Trigger trigger;
    ground.tileRect.h=32;
    ground.tileRect.w=32;
    ground.tileRect.x=0;
    ground.tileRect.y=0;
    int size = mapsize;
    unsigned int mask=0x01;
    memset(gameData->triggerList,0,sizeof(gameData->triggerList));
    gameData->triggerCount=0;
    Entity wall;
    wall.sprite=ground.tileRect;
    wall.ID=0;
    for (int y=0;y<size;y++){
        for (int x=0;x<size;x++){
            trigger.Rect.h=32;
            trigger.Rect.w=32;
            ground.tileRect.x = (x * 32);
            ground.tileRect.y = (y * 32);
            trigger.Rect.x=(x*32);
            trigger.Rect.y=(y*32);
            //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"%i",gameData->map[y][x]);
            if(gameData->map[y][x]>=7 && gameData->map[y][x]<=10){
                //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"????");
                wall.sprite=ground.tileRect;
                wall.ID=0;
                ground.tileRect.h=32;
                ground.tileRect.w=64;
                if (gameData->map[y][x]==9 || gameData->map[y][x] ==7){
                    wall.box=initBoundingBox(ground.tileRect.x,ground.tileRect.y,ground.tileRect.h,ground.tileRect.w);
                    if (gameData->currentRoom->bound==0)
                        Insertnode(&gameData->currentRoom->staticBlocks,NewElement(wall));
                    trigger.Rect.x=(x*32)+16;
                    trigger.Rect.h=2;
                    if(gameData->map[y][x] ==7&&(gameData->currentRoom->door&(mask<<3))!=0){
                        SDL_RenderCopy(rend, gameData->GroundSheet, &gameData->Tiles[gameData->map[y][x]].tileRect,&ground.tileRect);
                        trigger.doornum=3;
                        trigger.Rect.y+=32;
                        gameData->triggerList[gameData->triggerCount]=trigger;
                        gameData->triggerCount++;
                        gameData->map[y][x+1]=-1;
                    }else if(gameData->map[y][x] ==9&&(gameData->currentRoom->door&(mask<<1))!=0){
                        SDL_RenderCopy(rend, gameData->GroundSheet, &gameData->Tiles[gameData->map[y][x]].tileRect,&ground.tileRect);
                        trigger.doornum=1;
                        trigger.Rect.y-=2;
                        gameData->triggerList[gameData->triggerCount]=trigger;
                        gameData->triggerCount++;
                        gameData->map[y][x+1]=-1;
                    }else{
                        gameData->map[y][x+1]=2;
                        ground.tileRect.h=32;
                        ground.tileRect.w=32;
                        SDL_RenderCopy(rend, gameData->GroundSheet, &gameData->Tiles[2].tileRect,&ground.tileRect);
                    }

                }else{
                    wall.box=initBoundingBox(ground.tileRect.x,ground.tileRect.y,ground.tileRect.h+32,ground.tileRect.w-32);
                    if (gameData->currentRoom->bound==0)
                        Insertnode(&gameData->currentRoom->staticBlocks,NewElement(wall));
                    trigger.Rect.y=(y*32)+16;
                    trigger.Rect.h=32;
                    trigger.Rect.w=2;

                    SDL_Point p;
                    p.x=0;
                    p.y=0;
                    ground.tileRect.x+=32;
                    gameData->map[y+1][x]=-1;
                    if(gameData->map[y][x]==8 &&(gameData->currentRoom->door&mask)!=0){
                        SDL_RenderCopyEx(rend,gameData->GroundSheet,&gameData->Tiles[gameData->map[y][x]].tileRect,&ground.tileRect,90,&p,SDL_FLIP_VERTICAL);
                        trigger.doornum=0;
                        trigger.Rect.x+=32;
                        gameData->triggerList[gameData->triggerCount]=trigger;
                        gameData->triggerCount++;
                    }else if(gameData->map[y][x]==10&&(gameData->currentRoom->door&(mask<<2))!=0){
                        SDL_RenderCopyEx(rend,gameData->GroundSheet,&gameData->Tiles[gameData->map[y][x]].tileRect,&ground.tileRect,90,&p,SDL_FLIP_NONE);
                        trigger.doornum=2;
                        trigger.Rect.x-=2;
                        gameData->triggerList[gameData->triggerCount]=trigger;
                        gameData->triggerCount++;
                    }else{
                        gameData->map[y+1][x]=2;
                        ground.tileRect.x-=32;
                        ground.tileRect.h=32;
                        ground.tileRect.w=32;
                        SDL_RenderCopy(rend, gameData->GroundSheet, &gameData->Tiles[2].tileRect,&ground.tileRect);
                    }
                }
            }else if((gameData->map[y][x]==2)){
                wall.box=initBoundingBox(ground.tileRect.x,ground.tileRect.y,ground.tileRect.h,ground.tileRect.w);
                if (gameData->currentRoom->bound==0)
                    Insertnode(&gameData->currentRoom->staticBlocks,NewElement(wall));
                SDL_RenderCopy(rend, gameData->GroundSheet, &gameData->Tiles[gameData->map[y][x]].tileRect,&ground.tileRect);
            }else{
                SDL_RenderCopy(rend, gameData->GroundSheet, &gameData->Tiles[gameData->map[y][x]].tileRect,&ground.tileRect);
            }
            ground.tileRect.h=32;
            ground.tileRect.w=32;
        }
    }
    if (gameData->currentRoom->bound==0)
            gameData->currentRoom->bound=1;
}
