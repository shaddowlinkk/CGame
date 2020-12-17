//
// Created by nathan on 9/10/2020.
//
#include <stdio.h>
#include "GameCore.h"
#ifndef CGAME_FILEIO_H
#define CGAME_FILEIO_H
void writeEntityToFile(char *name,Entity *entity);
Entity readEntityFromFile(char *name,SDL_Renderer *rend);
void LoadMapFile(char *name,GameData *data);
void LoadTileData(GameData *data);
//void renderMapFromFile(SDL_Renderer *rend,GameData *gameData);
#endif //CGAME_FILEIO_H
