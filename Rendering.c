//
// Created by nathan on 9/6/2020.
//

#include "Rendering.h"
#include <stdio.h>
/**
 * renderd the SDL RECT that defines how an entity is renders
 * @param data the game state
 * @param rend an SDL renderer
 */
void renderTriggerBox(GameData *data, SDL_Renderer *rend){

    for (int i = 0; i < data->triggerCount; i++) {
          SDL_RenderDrawRect(rend, &data->triggerList[i].Rect);
    }
}
void renderEntityBoxList(GameData *data, SDL_Renderer *rend){
    node **tracer = &data->start;
    if(!*tracer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"no list data in entity linked list 1");
    }else {
        while (*tracer) {
            SDL_RenderDrawRect(rend, &(*tracer)->item.sprite);
            tracer = &(*tracer)->next;
        }
    }
}

void renderEntitys(GameData *data, SDL_Renderer *rend){
    node **tracer = &data->start;
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

void renderBoundingBox(BoundingBox *box , SDL_Renderer *rend){
    SDL_Point rect[5];
    rect[0]=box->coords[0];
    rect[1]=box->coords[1];
    rect[2]=box->coords[2];
    rect[3]=box->coords[3];
    rect[4]=box->coords[0];
    SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLines(rend,rect,5);
    SDL_SetRenderDrawColor(rend, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawPoint(rend,box->center.x,box->center.y);
    SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
}
void renderWallBox(GameData *data, SDL_Renderer *rend){
    node **trace = &data->currentRoom->staticBlocks;
    while (*trace){
        renderBoundingBox(&(*trace)->item.box,rend);
        trace = &(*trace)->next;
    }
}