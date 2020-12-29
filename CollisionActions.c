//
// Created by nathan on 12/22/2020.
//

#include "CollisionActions.h"
#include "math.h"
#include "BoundingboxUtil.h"

/*TODO Give point p¬1,p1 get Δx and  Δy to move the box away
NEED TO IMPLEMENT
Xp1,p2= (xp1-xp2)
yp1,p2= (yp1-yp2)
θ = tan-1(yp1,p2 /Xp1,p2)
HR =(HR∈ℝ|(π/2)>HR>-( π/2) ⋃ 1 ≤ tan(HR)≥ -1 )
HL =(HL∈ℝ|(π/2)<HR<-( π/2) ⋃ 1 ≤ tan(HR)≥ -1 )

VUR =( VUR ∈ℝ|(π/2)> VUR >-( π/2) ⋃ 1 ≥ tan(VUR)  )
VDR=(VL∈ℝ|(π/2)> VUR >-( π/2) ⋃ tan(VDR) ≤ -1 )

VUL =( VUR ∈ℝ|(π/2)< VUL <-( π/2) ⋃ -1 ≥ tan(VDL)  )
VDL=(VDL∈ℝ|(π/2)<VDL <-( π/2) ⋃ tan(tan(VDL) ≤ 1 )


Δx ={HR ⋂ θ then 1, HL ⋂ θ then -1 else 0 }
Δy ={( VUR⋀VUL) ⋂ θ then -1, (VDR⋀VDL) ⋂ θ then 1 else 0 }

*/



void stopEntityMovement(Entity *mover,Entity *collision){
 double x =(collision->box.center.x-mover->box.center.x),y =(collision->box.center.y-mover->box.center.y);
 double theta=atan((y/x));
 mover->vely=0;
 mover->velx=0;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"collition:%lf",(theta));
 if(( theta<(M_PI/2)&& theta>0)||( theta>((3*M_PI)/2)&& theta<(2*M_PI))){
     double value = tan(theta);
     if(value<=1 && value>=-1){
         mover->sprite.x=mover->sprite.x+1;
     }
     if(value >=1){
         mover->sprite.y=mover->sprite.y+1;
     }
     if(value <=-1){
         mover->sprite.y=mover->sprite.y-1;
     }
 }else if(( theta>(M_PI/2)&& theta<((3*M_PI)/2))){
     double value = tan(theta);
     if(value<=1 && value>=-1){
         mover->sprite.x=mover->sprite.x-1;
     }
     if(value >=1){
         mover->sprite.y=mover->sprite.y+1;
     }
     if(value <=-1){
         mover->sprite.y=mover->sprite.y-1;
     }
 }else{
     mover->sprite.y=mover->sprite.y-1;
     mover->sprite.x=mover->sprite.x-1;
 }
}