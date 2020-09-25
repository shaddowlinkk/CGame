//
// Created by nathan on 9/1/2020.
//

#ifndef CGAME_GAMECORE_H
#define CGAME_GAMECORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Room.h"
#define mapsize 22



typedef struct _Entity{
    int ID;
    int state;
    SDL_Rect sprite;// a rectangle that represent the sprite on the board
    SDL_Rect cutter;// a rectangle that is used to cut the sprite sheet if needed
    SDL_Texture *spriteSheet; // if the Entity has an animation you will need cutter to cut with SDL_renderCopy
    char textureName[20];
    int velx,vely;
    int animationStates[15];
}Entity;

typedef struct _TriggerAreas{
    SDL_Rect Rect;
    int doornum;
}Trigger;

typedef struct _node
{
    Entity item;
    struct _node *next;
} node;

typedef struct _MapTile{
    SDL_Texture *tileTexture;
    SDL_Rect tileRect;
}MapTile;

typedef struct _CoreGameData{
    //map needs to be first for some reason
    int map[mapsize][mapsize];
    SDL_Texture *GroundSheet;
    Trigger triggerList[20];
    node *start;
    int triggerCount;
    MapTile Tiles[100];
    int window_h,window_w;
    Room *currentRoom;
}GameData;

#endif //CGAME_GAMECORE_H
