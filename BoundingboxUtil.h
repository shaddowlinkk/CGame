//
// Created by nathan on 12/12/2020.
//

#ifndef CGAME_BOUNDINGBOXUTIL_H
#define CGAME_BOUNDINGBOXUTIL_H

#include "GameCore.h"
void rotateBoundingBox(BoundingBox *box,int degree);
BoundingBox initBoundingBox(int x, int y , int h , int w);
void moveBoundingBox(BoundingBox *outBox,int dx,int dy);
void setBoundingBox(BoundingBox *outBox,int x,int y);
#endif //CGAME_BOUNDINGBOXUTIL_H
