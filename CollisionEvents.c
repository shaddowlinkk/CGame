//
// Created by sip26 on 9/25/2020.
//

#include "CollisionEvents.h"
#include "LinkedList.h"
#include "CollisionDetection.h"
#include "CollisionActions.h"
#include "InputEvents.h"
#include "Room.h"

#define MAX(a,b) (((a) > (b)) ? (a) : (b))
/**
 * see if thare is a  collision of one of the trigger areas
 * @param data a instens of the game data
 */
void doorTiggerCollision(GameData *data){
    for (int i = 0; i < data->triggerCount; i++) {
        if(checkCollision(data->triggerList[i].Rect,Findnode(&data->start,0)->sprite)){
            data->currentRoom=enterRoom(data->triggerList[i].doornum,data->currentRoom);
            Findnode(&data->start,0)->sprite.x=data->window_w/2;
            Findnode(&data->start,0)->sprite.y=data->window_h/2;
        }
    }
}
/**
 * this is function is used to whether an entity is colliding with any entity in a list of entitys
 * @param entity the entitys that you want to check collisions with
 * @param list the list of  entitys that you want to check against
 */
void staticObjectCollision(Entity *entity, node *list){
    node **tracer= &list;
    if(!*tracer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"no list data in entity linked list collition");
    }else {
        int count=0;
        while (*tracer) {
            int side=optCheckCollisions(&entity->box,&(*tracer)->item.box,(MAX(entity->box.h,entity->box.w)+(MAX(entity->box.h,entity->box.w)*.1)));
        if(side!=-1){
            stopEntityMovement(entity,&(*tracer)->item);
        }
        count++;
        tracer = &(*tracer)->next;
        }

    }
}