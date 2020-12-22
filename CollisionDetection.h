//
// Created by nathan on 9/23/2020.
//

#ifndef CGAME_COLLISIONDETECTION_H
#define CGAME_COLLISIONDETECTION_H
#include <math.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "GameCore.h"

bool doIntersect(SDL_Point p1, SDL_Point q1, SDL_Point p2, SDL_Point q2);
bool checkCollision( SDL_Rect a, SDL_Rect b );
int optCheckCollisions(BoundingBox *box1, BoundingBox *box2,int dist);
#endif //CGAME_COLLISIONDETECTION_H
