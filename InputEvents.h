//
// Created by nathan on 9/3/2020.
//
#include "GameCore.h"
#ifndef CGAME_INPUTEVENTS_H
#define CGAME_INPUTEVENTS_H
int linkEntityToUserInput(Entity *entity, GameData *gameData);
void bindEntityToBoard(Entity *entity, GameData gameData);
void bindEntityToRect(Entity *entity, SDL_Rect rect);
void bindEntitysToRect(GameData *data, SDL_Rect rect);
void bindEntitysToBoard(GameData data);
#endif //CGAME_INPUTEVENTS_H
