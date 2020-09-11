//
// Created by nathan on 9/10/2020.
//

#include "FileIO.h"
void writeEntityToFile(char *name,Entity *entity){
    FILE *player;
    char filepath[31]=".\\Entitys\\";
    strcat(filepath,name);
    player=fopen(filepath,"w");
    fwrite(entity,sizeof(Entity),1,player);
    fclose(player);
}

Entity readEntityFromFile(char *name,SDL_Renderer *rend){
    Entity entity;
    FILE *player;
    char filepath[]=".\\Entitys\\";
    strcat(filepath,name);

    //reading from file
    player=fopen(filepath,"r");
    fread(&entity,sizeof(Entity),1,player);
    fclose(player);

    //geting the texture for entity
    char path[32]=".\\Textures\\";
    strcat(path,entity.textureName);
    SDL_Surface  *surface = IMG_Load(path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    entity.spriteSheet=tex;
    return entity;
}
