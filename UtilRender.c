//
// Created by nathan on 9/6/2020.
//

#include "UtilRender.h"
void renderEntityBox(GameData data, SDL_Renderer *rend){

    for (int i = 0; i < data.entCount; i++) {
            SDL_RenderDrawRect(rend, &data.entityList[i].sprite);
    }
}
