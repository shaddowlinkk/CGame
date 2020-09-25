//
// Created by nathan on 9/6/2020.
//

#include "UtilRender.h"
#include "CollisionDetection.h"
#include "LinkedList.h"
#include <stdbool.h>
/**
 * renderd the SDL RECT that defines how an entity is renders
 * @param data the game state
 * @param rend an SDL renderer
 */
void renderTriggerBox(GameData *data, SDL_Renderer *rend){

    for (int i = 0; i < data->triggerCount; i++) {
        if(checkCollision(data->triggerList[i].Rect,Findnode(&data->start,0)->sprite)){
            data->currentRoom=enterRoom(data->triggerList[i].doornum,data->currentRoom);
            Findnode(&data->start,0)->sprite.x=data->window_w/2;
            Findnode(&data->start,0)->sprite.y=data->window_h/2;
        }
        else
          SDL_RenderDrawRect(rend, &data->triggerList[i].Rect);
    }
}
void renderEntityBoxList(GameData data, SDL_Renderer *rend){
    node **tracer = &data.start;
    if(!*tracer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"no list data in entity linked list 1");
    }else {
        while (*tracer) {
            SDL_RenderDrawRect(rend, &(*tracer)->item.sprite);
            tracer = &(*tracer)->next;
        }
    }
}

void renderEntitys(GameData data, SDL_Renderer *rend){
    node **tracer = &data.start;
    if(!*tracer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"no list data in entity linked list 2");
    }else {
        while (*tracer) {
            SDL_RenderCopy(rend, (*tracer)->item.spriteSheet,&(*tracer)->item.cutter,&(*tracer)->item.sprite);
            tracer = &(*tracer)->next;
        }
    }
}
void renderRoomCode(GameData *data, SDL_Renderer *rend,TTF_Font *font, SDL_Color color){
    char buffer[100];
    SDL_Surface * surface;
    SDL_Texture * texture;
    sprintf(buffer, "room: %p", data->currentRoom);
    surface = TTF_RenderText_Solid(font, buffer, color);
    texture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);


    SDL_Rect dstrect = { 0, 0, 256,32 };
    SDL_RenderCopy(rend,texture,NULL,&dstrect);
    SDL_DestroyTexture(texture);
}
