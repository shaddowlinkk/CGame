//
// Created by nathan on 9/23/2020.
//

#ifndef CGAME_ROOM_H
#define CGAME_ROOM_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct _room{
    unsigned int door:4;
    char *mapName;
    struct _room *rooms[4];
    int gened:1;
}Room;
#define INIT_ROOM_PTR(x) x->door=0,x->mapName="",x->rooms[0]=NULL,x->rooms[1]=NULL,x->rooms[2]=NULL,x->rooms[3]=NULL,x->gened=0;
#define INIT_ROOM_ARRAY(x) x[0]=NULL,x[1]=NULL,x[2]=NULL,x[3]=NULL;
Room *initRooms();
Room *enterRoom(int door,Room *inRoom);
void freeRoomsAtDepth(Room *room,int depth,Room *last);
#endif //CGAME_ROOM_H
