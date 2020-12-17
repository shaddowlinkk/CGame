//
// Created by nathan on 12/12/2020.
//

#include "BoundingboxUtil.h"
#include <math.h>

// rotates a point around the origine
SDL_Point pointRotation(SDL_Point center,SDL_Point point, int degree) {
    SDL_Point out;
    double corection = M_PI/180;
    out.x = ((point.x-center.x) * cos((degree*corection)))-((point.y-center.y) * sin((degree*corection)))+center.x;
    out.y  = ((point.x-center.x) * sin((degree*corection)))+((point.y-center.y) * cos((degree*corection)))+center.y;
    return out;
}

BoundingBox rotateBoundingBox(BoundingBox box,int degree){
    box.coords[0]=pointRotation(box.center,box.coords[0],degree);
    box.coords[1]=pointRotation(box.center,box.coords[1],degree);
    box.coords[2]=pointRotation(box.center,box.coords[2],degree);
    box.coords[3]=pointRotation(box.center,box.coords[3],degree);
    return box;
}

BoundingBox initBoundingBox(int x, int y , int h , int w){
    BoundingBox outBox;
    SDL_Point coord;coord.x=x;coord.y=y;
    outBox.coords[0] = coord;
    coord.x+=w;
    outBox.coords[1] = coord;
    coord.y+=h;
    outBox.coords[3] = coord;
    coord.x=x;
    outBox.coords[2] = coord;
    coord.x=x+(w/2);coord.y=y+(h/2);
    outBox.center=coord;
    return outBox;
}