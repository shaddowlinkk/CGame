//
// Created by nathan on 10/6/2020.
//

#ifndef CGAME_CLIENT_H
#define CGAME_CLIENT_H
#include "GameCore.h"
typedef struct _packet{
    int state,x,y;
}EntityPacket;
EntityPacket *updateEntity(EntityPacket data);

#endif //CGAME_CLIENT_H
