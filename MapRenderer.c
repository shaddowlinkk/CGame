//
// Created by nathan on 9/2/2020.
//

#include "MapRenderer.h"
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

void renderMapFromFile(SDL_Renderer *rend,GameData *gameData){
    // temp def of a tile
    MapTile ground;
    ground.tileRect.h=32;
    ground.tileRect.w=32;
    ground.tileRect.x=0;
    ground.tileRect.y=0;
    int size = sizeof(*gameData->map)/4;
    for (int y=0;y<size;y++){
        for (int x=0;x<size;x++){
            ground.tileRect.x = (x * 32);
            ground.tileRect.y = (y * 32);
            //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"%i",gameData->map[y][x]);
            if(gameData->map[y][x]>=7 && gameData->map[y][x]<=10){
                //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"????");
                ground.tileRect.h=32;
                ground.tileRect.w=64;
                if (gameData->map[y][x]==9 || gameData->map[y][x] ==7){
                    if(gameData->map[y][x] ==7){
                        SDL_RenderCopy(rend, gameData->GroundSheet, &gameData->Tiles[gameData->map[y][x]].tileRect,&ground.tileRect);
                        gameData->map[y][x+1]=-1;
                    }else if(gameData->map[y][x] ==9){
                        SDL_RenderCopy(rend, gameData->GroundSheet, &gameData->Tiles[gameData->map[y][x]].tileRect,&ground.tileRect);
                        gameData->map[y][x+1]=-1;
                    }

                }else{
                    SDL_Point p;
                    p.x=0;
                    p.y=0;
                    ground.tileRect.x+=32;
                    gameData->map[y+1][x]=-1;
                    if(gameData->map[y][x]==8){
                        SDL_RenderCopyEx(rend,gameData->GroundSheet,&gameData->Tiles[gameData->map[y][x]].tileRect,&ground.tileRect,90,&p,SDL_FLIP_VERTICAL);
                    }else if(gameData->map[y][x]==10){
                        SDL_RenderCopyEx(rend,gameData->GroundSheet,&gameData->Tiles[gameData->map[y][x]].tileRect,&ground.tileRect,90,&p,SDL_FLIP_NONE);
                    }
                }
            }else{
                SDL_RenderCopy(rend, gameData->GroundSheet, &gameData->Tiles[gameData->map[y][x]].tileRect,&ground.tileRect);
            }
            ground.tileRect.h=32;
            ground.tileRect.w=32;
        }
    }
}
