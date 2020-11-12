//
// Created by nathan on 9/3/2020.
//

#include "InputEvents.h"
/**
 * links an entity to user input
 * @param entity the entity that you want to link
 * @param gameData current states of global data
 * @return returns the input state that what found
 */
int linkEntityToUserInput(Entity *entity, GameData *gameData){
    int states=0;
    entity->state=0;
    entity->vely=0;
    entity->velx=0;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if((state[SDL_SCANCODE_DOWN]||state[SDL_SCANCODE_S])&&(state[SDL_SCANCODE_LEFT]||state[SDL_SCANCODE_A])){
        states=1;
        entity->state=1;
        entity->velx = -2;
        entity->vely = 2;
    }
    else if((state[SDL_SCANCODE_DOWN]||state[SDL_SCANCODE_S])&&(state[SDL_SCANCODE_RIGHT]||state[SDL_SCANCODE_D])){
        states=2;
        entity->state=2;
        entity->velx = 2;
        entity->vely = 2;
    }
    else if((state[SDL_SCANCODE_UP]||state[SDL_SCANCODE_W])&&(state[SDL_SCANCODE_LEFT]||state[SDL_SCANCODE_A])){
        states=1;
        entity->state=1;
        entity->velx = -2;
        entity->vely = -2;
    }
    else if((state[SDL_SCANCODE_UP]||state[SDL_SCANCODE_W])&&(state[SDL_SCANCODE_RIGHT]||state[SDL_SCANCODE_D])){
        states=2;
        entity->state=2;
        entity->velx = 2;
        entity->vely = -2;
    }
    else if(state[SDL_SCANCODE_UP]||state[SDL_SCANCODE_W]){
        states=4;
        entity->state=4;
        entity->vely = -2;
    }
    else if(state[SDL_SCANCODE_DOWN]||state[SDL_SCANCODE_S]){
        states=3;
        entity->state=3;
        entity->vely = 2;
    }
    else if(state[SDL_SCANCODE_LEFT]||state[SDL_SCANCODE_A]){
        states=1;
        entity->state=1;
        entity->velx = -2;
    }
    else if(state[SDL_SCANCODE_RIGHT]||state[SDL_SCANCODE_D]){
        states=2;
        entity->state=2;
        entity->velx = 2;
    }
    return states;
}

/**
 * set the bound of the movement area to the window screen
 * @param entity entity that you want to bind to the window
 * @param gameData current stat of global data
 */
void bindEntityToBoard(Entity *entity, GameData gameData){
    if(entity->sprite.x<0) {
        entity->sprite.x=1;
    }
    if(entity->sprite.x>(gameData.window_w-entity->sprite.w)){
        entity->sprite.x=(gameData.window_w-entity->sprite.w)-1;
    }
    if(entity->sprite.y>(gameData.window_h-entity->sprite.h)){
        entity->sprite.y=(gameData.window_h-entity->sprite.h)-1;
    }
    if(entity->sprite.y<0 )
        entity->sprite.y=1;
}

/**
 * set the bound of the movement area to a rect
 * @param entity entity that you want to bind to the window
 * @param rect the rectangle that you want the entity to be bound in
 */
void bindEntityToRect(Entity *entity, SDL_Rect rect){
    if(entity->sprite.x<(rect.x)) {
        entity->sprite.x=(rect.x)+1;
    }
    if(entity->sprite.x>(rect.w-entity->sprite.w)+rect.x){
        entity->sprite.x=(rect.w-entity->sprite.w)+rect.x-1;
    }
    if(entity->sprite.y>(rect.h-entity->sprite.h)+rect.y){
        entity->sprite.y=(rect.h-entity->sprite.h)+rect.y-1;
    }
    if(entity->sprite.y<(rect.y))
        entity->sprite.y=(rect.y)+1;
}
void bindEntitysToBoard(GameData data){
    node **tracer = &data.start;
    if(!*tracer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"no list data in entity linked list 5");
    }else {
        while (*tracer) {
            if ((*tracer)->item.sprite.x < 0) {
                (*tracer)->item.sprite.x = 1;
            }
            if ((*tracer)->item.sprite.x > (data.window_w - (*tracer)->item.sprite.w)) {
                (*tracer)->item.sprite.x = (data.window_w - (*tracer)->item.sprite.w) - 1;
            }
            if ((*tracer)->item.sprite.y > (data.window_h - (*tracer)->item.sprite.h)) {
                (*tracer)->item.sprite.y = (data.window_h - (*tracer)->item.sprite.h) - 1;
            }
            if ((*tracer)->item.sprite.y < 0)
                (*tracer)->item.sprite.y = 1;
            tracer = &(*tracer)->next;
        }
    }
}

void bindEntitysToRect(GameData *data, SDL_Rect rect){
    node **tracer = &data->start;
    if(!*tracer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"no list data in entity linked list 4");
    }else {
        while (*tracer) {
            if ((*tracer)->item.sprite.x < (rect.x)) {
                (*tracer)->item.sprite.x = (rect.x) + 1;
            }
            if ((*tracer)->item.sprite.x > (rect.w - (*tracer)->item.sprite.w) + rect.x) {
                (*tracer)->item.sprite.x = (rect.w - (*tracer)->item.sprite.w) + rect.x - 1;
            }
            if ((*tracer)->item.sprite.y > (rect.h - (*tracer)->item.sprite.h) + rect.y) {
                (*tracer)->item.sprite.y = (rect.h - (*tracer)->item.sprite.h) + rect.y - 1;
            }
            if ((*tracer)->item.sprite.y < (rect.y))
                (*tracer)->item.sprite.y = (rect.y) + 1;
            tracer = &(*tracer)->next;
        }
    }

}


