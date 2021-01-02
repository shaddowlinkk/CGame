//
// Created by nathan on 9/6/2020.
//
#include "GameCore.h"
#ifndef CGAME_UTILRENDER_H
#define CGAME_UTILRENDER_H

void renderTriggerBox(GameData *data, SDL_Renderer *rend);
void renderEntityBoxList(GameData *data, SDL_Renderer *rend);
void renderEntitys(GameData *data, SDL_Renderer *rend);
void renderRoomCode(GameData *data, SDL_Renderer *rend,TTF_Font *font, SDL_Color color);
void renderBoundingBox(BoundingBox *box , SDL_Renderer *rend);
void renderWallBox(GameData *data, SDL_Renderer *rend);
void renderInventory(GameData *gameData,SDL_Renderer *rend);
#endif //CGAME_UTILRENDER_H
