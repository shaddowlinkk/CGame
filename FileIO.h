//
// Created by nathan on 9/10/2020.
//
#include <stdio.h>
#include "GameCore.h"
#ifndef CGAME_FILEIO_H
#define CGAME_FILEIO_H
void writeToFile(char *name,Entity *entity);
Entity readEntityFromFile(char *name,SDL_Renderer *rend);
#endif //CGAME_FILEIO_H
