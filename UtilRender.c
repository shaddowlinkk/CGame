//
// Created by nathan on 9/6/2020.
//

#include "UtilRender.h"
/**
 * renderd the SDL RECT that defines how an entity is renders
 * @param data the game state
 * @param rend an SDL renderer
 */
void renderEntityBox(GameData data, SDL_Renderer *rend){

    for (int i = 0; i < data.entCount; i++) {
            SDL_RenderDrawRect(rend, &data.entityList[i].sprite);
    }
}
