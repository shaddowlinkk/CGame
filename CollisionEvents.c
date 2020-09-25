//
// Created by sip26 on 9/25/2020.
//

#include "CollisionEvents.h"
#include "LinkedList.h"
#include "CollisionDetection.h"
#include <stdbool.h>

void doorTiggerCollition(GameData *data){
    for (int i = 0; i < data->triggerCount; i++) {
        if(checkCollision(data->triggerList[i].Rect,Findnode(&data->start,0)->sprite)){
            data->currentRoom=enterRoom(data->triggerList[i].doornum,data->currentRoom);
            Findnode(&data->start,0)->sprite.x=data->window_w/2;
            Findnode(&data->start,0)->sprite.y=data->window_h/2;
        }
    }
}