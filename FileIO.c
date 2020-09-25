//
// Created by nathan on 9/10/2020.
//

#include "FileIO.h"
void writeEntityToFile(char *name,Entity *entity){
    FILE *player;
    char filepath[31]=".\\Entitys\\";
    strcat(filepath,name);
    player=fopen(filepath,"wb");
    fwrite(entity,sizeof(Entity),1,player);
    fclose(player);
}

Entity readEntityFromFile(char *name,SDL_Renderer *rend){
    Entity entity;
    FILE *player;
    char filepath[]=".\\Entitys\\";
    strcat(filepath,name);

    //reading from file
    player=fopen(filepath,"rb");
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

void LoadMapFile(char *name,GameData *data){
    FILE *map;
    map= fopen(name,"rb");
    unsigned char tmp[4];
    int count=0;
    memset(data->map,0,sizeof(data->map));
    while (fread(tmp,4,1,map)) {
/*        if (tmp[3]==1) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "%x", tmp[0]);
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "%x", tmp[1]);
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "%x", tmp[2]);
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "%x", tmp[3]);
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "%x", (tmp[0]|(tmp[1]<<8)|(tmp[2]<<16)|(tmp[3]<<24)));
    }*/
        data->map[(count/(sizeof(*data->map)/4))][(count%(sizeof(*data->map)/4))] += (tmp[0]<<24) | (tmp[1]<<16) | (tmp[2]<<8) | (tmp[3]);
        count++;
    }
}
void LoadBigMapFile(char *name,GameData *data){
    FILE *map;
    map= fopen(name,"rb");
    memset(data->map,0x00,mapsize);
    int tmp,count=0;
    while (fread(&tmp,sizeof(int),1,map)){
        data->map[(count/mapsize)][(count%mapsize)]=tmp;
        count++;
    }
    fclose(map);
}
void LoadTileData(GameData *data){
    FILE *tiles;
    tiles=fopen(".\\Entitys\\TileData.dat","r");
    SDL_Rect temp;
    for(int i =0;i<20;i++){
        fread(&temp,sizeof(struct SDL_Rect),1,tiles);
        data->Tiles[i].tileRect=temp;
    }
}