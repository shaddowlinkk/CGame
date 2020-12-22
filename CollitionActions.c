//
// Created by nathan on 12/22/2020.
//

#include "CollitionActions.h"
#include "BoundingboxUtil.h"

void stopEntityMovement(Entity *mover,int side){
    if(side==0){
        mover->sprite.y=mover->sprite.y-5;
        setBoundingBox(&mover->box,mover->sprite.x,mover->sprite.y);
        mover->velx=0;
        mover->vely=0;
    }
    if(side==2){
        mover->sprite.y=mover->sprite.y+5;
        setBoundingBox(&mover->box,mover->sprite.x,mover->sprite.y);
        mover->velx=0;
        mover->vely=0;
    }
    if(side==1){
        mover->sprite.x=mover->sprite.x+5;
        setBoundingBox(&mover->box,mover->sprite.x,mover->sprite.y);
        mover->velx=0;
        mover->vely=0;
    }

    if(side==3){
        mover->sprite.x=mover->sprite.x-5;
        setBoundingBox(&mover->box,mover->sprite.x,mover->sprite.y);
        mover->velx=0;
        mover->vely=0;
    }

}