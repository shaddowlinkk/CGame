//
// Created by nathan on 9/23/2020.
//

#ifndef CGAME_COLLISIONDETECTION_H
#define CGAME_COLLISIONDETECTION_H
#include <math.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
typedef struct Point
{
    int x;
    int y;
}Point;
bool doIntersect(Point p1, Point q1, Point p2, Point q2);
bool checkCollision( SDL_Rect a, SDL_Rect b );
#endif //CGAME_COLLISIONDETECTION_H
