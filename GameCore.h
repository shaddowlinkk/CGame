//
// Created by nathan on 9/1/2020.
//

#ifndef CGAME_GAMECORE_H
#define CGAME_GAMECORE_H
#include <SDL2/SDL.h>

struct Entity{
    int ID;
    SDL_Rect sprite;// a rectangle that represent the sprite on the board
    SDL_Rect cutter;// a rectangle that is used to cut the sprite sheet if needed
    SDL_Texture *spriteSheet; // if the Entity has an animation you will need cutter to cut with SDL_renderCopy

};

typedef  struct Entity  Entity;

struct CoreGameData{
    Entity  entityList[20];
};

#endif //CGAME_GAMECORE_H
