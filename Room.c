//
// Created by nathan on 9/23/2020.
//

#include "Room.h"
Room *newRoom(unsigned int indor , Room *prevroom){
    Room *new;
    new = (Room *) malloc(sizeof(Room));
    new->door=1;
    new->door=new->door<<((indor+2)%4);
    INIT_ROOM_ARRAY(new->rooms);
    new->rooms[(indor+2)%4]=prevroom;
    new->mapName="";
    new->gened=0;
    return new;
}
void freeRoomsAtDepth(Room *room,int depth,Room *last){
    for (int i = 0; i < 4; ++i) {
        if (room->rooms[i] != NULL && (room->rooms[i] != last)) {
            freeRoomsAtDepth(room->rooms[i], (depth == 0) ? 0 : depth - 1, room);
        }
    }
    if (depth == 0) {
        for (int i = 0; i < 4; ++i) {
            if (room->rooms[i] != NULL ) {
                if( (room->rooms[i] != last)){
                    Room *old=room->rooms[i];
                    room->rooms[i]=NULL;
                    free(old);
                } else{
                    room->rooms[i]=NULL;
                }
            }
        }
    }
}
int genRoomALL(Room *room){
    for(int i=0;i<4;i++) {
        *(room->rooms + i) =  newRoom(i, room);
        room->door =0x0f;
    }
    return 32;
}
int genRoom(Room *room){

    int lvc=(rand()%5);
    for(int i=0;i<lvc;i++) {
        unsigned int mask=0x01;
        unsigned int doornum = (rand() % 4);
        *(room->rooms + doornum) = (((room->door) & (mask << doornum)) != 0) ? room->rooms[doornum] : newRoom(doornum, room);
        room->door |= (mask << doornum);
    }
    room->gened=1;
    return lvc;
}
Room *initRooms(){
    Room *new;
    new = (Room *) malloc(sizeof(Room));
    INIT_ROOM_PTR(new);
    genRoomALL(new);
    return new;
}
Room *enterRoom(int door,Room *inRoom){
    if(inRoom->rooms[door]->gened==0) {
        genRoom(inRoom->rooms[door]);
    }
    return inRoom->rooms[door];
}