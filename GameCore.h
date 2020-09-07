//
// Created by nathan on 9/1/2020.
//

#ifndef CGAME_GAMECORE_H
#define CGAME_GAMECORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "LinkedList.h"


typedef struct MapTile{
    SDL_Texture *tileTexture;
    SDL_Rect tileRect;
}MapTile;

typedef struct Entity{
    int ID;
    SDL_Rect sprite;// a rectangle that represent the sprite on the board
    SDL_Rect cutter;// a rectangle that is used to cut the sprite sheet if needed
    SDL_Texture *spriteSheet; // if the Entity has an animation you will need cutter to cut with SDL_renderCopy
    char *textureLocation;
    int velx,vely;
    int animationStates[];
}Entity;

typedef struct CoreGameData{
    Entity entityList[20];
    node *head;
    int entCount;
    int map[20][20];
    MapTile Tiles[100];
    int window_h,window_w;
}GameData;

#endif //CGAME_GAMECORE_H
