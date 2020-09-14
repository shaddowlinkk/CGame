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
    SDL_Surface *s = IMG_Load(".\\Textures\\Floor.png");
    ground.tileTexture=SDL_CreateTextureFromSurface(rend,s);
    for (int y=0;y<sizeof(*gameData->map)/4;y++){
        for (int x=0;x<sizeof(*gameData->map)/4;x++){
                ground.tileRect.x = (x * 32);
                ground.tileRect.y = (y * 32);
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"%i",gameData->Tiles[gameData->map[y][x]].tileRect.x);
                SDL_RenderCopy(rend, ground.tileTexture, &gameData->Tiles[gameData->map[y][x]].tileRect, &ground.tileRect);
        }
    }
}
