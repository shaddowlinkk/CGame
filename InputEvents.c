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
int linkEntityToUserInput(Entity *entity, GameData gameData){
    int states=0;
    entity->vely=0;
    entity->velx=0;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if((state[SDL_SCANCODE_DOWN]||state[SDL_SCANCODE_S])&&(state[SDL_SCANCODE_LEFT]||state[SDL_SCANCODE_A])){
        states=1;
        entity->velx = -1;
        entity->vely = 1;
    }
    else if((state[SDL_SCANCODE_DOWN]||state[SDL_SCANCODE_S])&&(state[SDL_SCANCODE_RIGHT]||state[SDL_SCANCODE_D])){
        states=2;
        entity->velx = 1;
        entity->vely = 1;
    }
    else if((state[SDL_SCANCODE_UP]||state[SDL_SCANCODE_W])&&(state[SDL_SCANCODE_LEFT]||state[SDL_SCANCODE_A])){
        states=1;
        entity->velx = -1;
        entity->vely = -1;
    }
    else if((state[SDL_SCANCODE_UP]||state[SDL_SCANCODE_W])&&(state[SDL_SCANCODE_RIGHT]||state[SDL_SCANCODE_D])){
        states=2;
        entity->velx = 1;
        entity->vely = -1;
    }
    else if(state[SDL_SCANCODE_UP]||state[SDL_SCANCODE_W]){
        states=4;
        entity->vely = -1;
    }
    else if(state[SDL_SCANCODE_DOWN]||state[SDL_SCANCODE_S]){
        states=3;
        entity->vely = 1;
    }
    else if(state[SDL_SCANCODE_LEFT]||state[SDL_SCANCODE_A]){
        states=1;
        entity->velx = -1;
    }
    else if(state[SDL_SCANCODE_RIGHT]||state[SDL_SCANCODE_D]){
        states=2;
        entity->velx = 1;
    }
    return states;
}

/**
 * set the bound of the movment area to the window screen
 * @param entity entity that you want to bind to the window
 * @param gameData current stat of global data
 */
void bindEntityToBoard(Entity *entity, GameData gameData){
    //todo bug::-> can get out of the screen when in bot left corner with inputs(AS SD)
    if(entity->sprite.x<0 || entity->sprite.x>(gameData.window_w-entity->sprite.w)) {
        entity->velx *= -1;
    }
    if(entity->sprite.y<0 || entity->sprite.y>(gameData.window_h-entity->sprite.h))
        entity->vely*= -1;
}

