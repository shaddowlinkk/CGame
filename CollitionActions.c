//
// Created by nathan on 12/22/2020.
//

#include "CollitionActions.h"
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



void stopEntityMovement(Entity *mover){
    int dx =mover->velx;
    int dy =mover->vely;
    mover->sprite.x+=(dx*-1)*2;
    mover->sprite.y+=(dy*-1)*2;
    setBoundingBox(&mover->box,mover->sprite.x,mover->sprite.y);

}