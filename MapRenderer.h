//
// Created by nathan on 9/2/2020.
//
#include "GameCore.h"
#ifndef CGAME_MAPRENDERER_H
#define CGAME_MAPRENDERER_H
void rendermap(SDL_Renderer *rend,GameData *gameData);
void renderMapFromFile(SDL_Renderer *rend,GameData *gameData);
void LoadBigMapFile(char *name,GameData *data);
#endif //CGAME_MAPRENDERER_H
