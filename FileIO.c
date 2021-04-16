//
// Created by nathan on 9/10/2020.
//

#include "FileIO.h"
/**
 * this functions that save a entitys to a file
 * @param name file name to save to
 * @param entity the entity that you want to save
 */
void writeEntityToFile(char *name,Entity *entity){
    FILE *player;
    char filepath[31]=".\\entitys\\";
    strcat(filepath,name);
    player=fopen(filepath,"wb");
    fwrite(entity,sizeof(Entity),1,player);
    fclose(player);
}
/**
 * this function read a function into the system
 * @param name the file name of the entity file
 * @param rend an SDl_render to make the entity texture data
 * @return the entity that is read from the file
 */
Entity readEntityFromFile(char *name,SDL_Renderer *rend){
    Entity entity;
    FILE *player;
    char filepath[]=".\\entitys\\";
    strcat(filepath,name);

    //reading from file
    player=fopen(filepath,"rb");
    fread(&entity,sizeof(Entity),1,player);
    fclose(player);

    //geting the texture for entity
    char path[32]=".\\Textures\\";
    strcat(path,entity.textureName);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,path);
    SDL_Surface  *surface = IMG_Load(path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    entity.spriteSheet=tex;
    return entity;
}
/**
 * this loads a map into the system
 * @param name the file name of the map you want to load
 * @param data pointer to the game data to load map into
 */
 /// this function has depricated
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
}/**
 * this loads a map into the system
 * @param name the file name of the map you want to load
 * @param data pointer to the game data to load map into
 */
 /// reads in a .map file map size 22
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
/**
 * this loads in all this tile data for the  map
 * @param data the pointer to game data to load into
 */
void LoadTileData(GameData *data){
    FILE *tiles;
    tiles=fopen(".\\entitys\\TileData.dat","r");
    SDL_Rect temp;
    for(int i =0;i<20;i++){
        fread(&temp,sizeof(struct SDL_Rect),1,tiles);
        data->Tiles[i].tileRect=temp;
    }
}