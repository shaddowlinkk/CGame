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

void rotateBoundingBox(BoundingBox *box,int degree){
    box->coords[0]=pointRotation(box->center,box->originCoords[0],degree);
    box->coords[1]=pointRotation(box->center,box->originCoords[1],degree);
    box->coords[2]=pointRotation(box->center,box->originCoords[2],degree);
    box->coords[3]=pointRotation(box->center,box->originCoords[3],degree);
    box->degree=degree;

}

BoundingBox initBoundingBox(int x, int y , int h , int w){
    BoundingBox outBox;
    SDL_Point coord;coord.x=x;coord.y=y;
    outBox.h=h;outBox.w=w,outBox.degree=0;
    outBox.coords[0] = coord;
    outBox.originCoords[0] = coord;
    coord.x+=w;
    outBox.coords[1] = coord;
    outBox.originCoords[1] = coord;
    coord.y+=h;
    outBox.coords[2] = coord;
    outBox.originCoords[2] = coord;
    coord.x=x;
    outBox.coords[3] = coord;
    outBox.originCoords[3] = coord;
    coord.x=x+(w/2);coord.y=y+(h/2);
    outBox.center=coord;
    return outBox;
}
void moveBoundingBox(BoundingBox *outBox,int dx,int dy){
    int h=outBox->h,w=outBox->w;
    outBox->center.x=outBox->coords[0].x+(w/2);
    outBox->center.y=outBox->coords[0].y+(h/2);
    outBox->coords[0].x+=dx;
    outBox->coords[0].y+=dy;
    outBox->coords[1].x+=dx;
    outBox->coords[1].y+=dy;
    outBox->coords[2].x+=dx;
    outBox->coords[2].y+=dy;
    outBox->coords[3].x+=dx;
    outBox->coords[3].y+=dy;
    outBox->originCoords[0].x+=dx;
    outBox->originCoords[0].y+=dy;
    outBox->originCoords[1].x+=dx;
    outBox->originCoords[1].y+=dy;
    outBox->originCoords[2].x+=dx;
    outBox->originCoords[2].y+=dy;
    outBox->originCoords[3].x+=dx;
    outBox->originCoords[3].y+=dy;
}
void setBoundingBox(BoundingBox *outBox,int x,int y){

    SDL_Point coord;coord.x=x;coord.y=y;
    int h=outBox->h,w=outBox->w;
    outBox->coords[0] = coord;
    outBox->originCoords[0] = coord;
    coord.x+=w;
    outBox->coords[1] = coord;
    outBox->originCoords[1] = coord;
    coord.y+=h;
    outBox->coords[2] = coord;
    outBox->originCoords[2] = coord;
    coord.x=x;
    outBox->coords[3] = coord;
    outBox->originCoords[3] = coord;
    coord.x=x+(w/2);coord.y=y+(h/2);
    outBox->center=coord;
    rotateBoundingBox(outBox,outBox->degree);

}