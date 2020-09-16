
#include "GameCore.h"
#include "MapRenderer.h"
#include "InputEvents.h"
#include "UtilRender.h"
#include "LinkedList.h"
#include "FileIO.h"
#include <direct.h>
#include <stdio.h>

/**
 * This function moves the cutting SDL_Rect to the next frame of the animation
 * @param entity what ever entity you are trying to animate.
 * @param state the animation state that corresponds to the action you are trying to animate
 */
void animate(Entity *entity, int state){
    //count slows the animation todo need to remove that and make it native to the rendering loop
    static int count =0;
    if(count==5) {
        count=0;
        entity->cutter.y = (entity->cutter.h*state);
        entity->cutter.x = (entity->cutter.w * (((entity->cutter.x / entity->cutter.w)+1)% (entity->animationStates[state]-1)) );
    }
    count++;
}

void animateEntitys(GameData data){
    //count slows the animation todo need to remove that and make it native to the rendering loop
    static int count =0;
    node **tracer = &data.start;
    if(!*tracer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"no list data in entity linked list 6");
    }else {
        if (count == 5) {
            count = 0;
            while (*tracer) {
                (*tracer)->item.cutter.y = ((*tracer)->item.cutter.h * (*tracer)->item.state);
                (*tracer)->item.cutter.x = ((*tracer)->item.cutter.w * ((((*tracer)->item.cutter.x / (*tracer)->item.cutter.w) + 1) % ((*tracer)->item.animationStates[(*tracer)->item.state] - 1)));
                tracer = &(*tracer)->next;
            }

        }
        count++;
    }
}

/**
 * moves an entity based on velocity
 * @param entity the entity that you want to move
 */
void moveEntity(GameData data){
    node **tracer = &data.start;
    if(!*tracer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"no list data in entity linked list 3");
    }else {
        while (*tracer) {
            (*tracer)->item.sprite.x += (*tracer)->item.velx;
            (*tracer)->item.sprite.y += (*tracer)->item.vely;
            tracer = &(*tracer)->next;
        }
    }
}



int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);
    GameData gameData;
    SDL_Window *win = SDL_CreateWindow("CGame",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,704,704,SDL_WINDOW_OPENGL);
    SDL_GetWindowSize(win,&gameData.window_w,&gameData.window_h);
    if (!win){
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *rend = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(rend,255,255,255,255);
    if(!rend){
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 2;
    }
/*    SDL_Surface  *surface = IMG_Load(".\\Textures\\Floor.png");
    if(!surface){
        char tmp[100];
        getcwd(tmp,100);
        SDL_Log("%s",tmp );
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 3;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    if(!tex){
        SDL_Log("error %s\n",SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 4;
    }*/


/*    Entity new;
    new.ID=0;
    new.spriteSheet=tex;
    new.sprite.h=32;
    new.sprite.w=16;
    new.cutter.h=32;
    new.cutter.w=16;
    new.cutter.x=0;
    new.cutter.y=0;
    new.sprite.x=gameData.window_w/2;
    new.sprite.y=gameData.window_h/2;
    new.animationStates[0]=7;
    new.animationStates[1]=11;
    new.animationStates[2]=11;
    new.animationStates[3]=8;
    new.animationStates[4]=9;
    new.animationStates[5]=16;
    memset(new.textureName,0x00,sizeof(20));
    strcpy(new.textureName,"test.png");*/


    //writeToFile(&new);

    //inisalizing the list and loading in data
    LoadBigMapFile("dtemp.map",&gameData);
    LoadTileData(&gameData);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"ss:%i",gameData.map[4][4]);
    gameData.start=NULL;
    Insertnode(&gameData.start,NewElement(readEntityFromFile("play.ent",rend)));


/*    SDL_Rect t;
    t.w=64;
    t.h=32;
    t.x=32+32;
    t.y=32;

    SDL_Rect c;
    c.w=64;
    c.h=32;
    c.x=0;
    c.y=0;
    SDL_Point p;
    p.x=0;
    p.y=0;*/
    SDL_RenderClear(rend);
    int running=1;
    SDL_Event event;
    while(running) {
        int states=0;
        // Process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        // clear old frame
        SDL_RenderClear(rend);

        //game logic
        SDL_Rect re;
        re.w=gameData.window_w-64;
        re.h=gameData.window_h-64;
        re.x=32;
        re.y=32;


        linkEntityToUserInput(Findnode(&gameData.start,0),gameData);
        bindEntitysToRect(gameData,re);
        moveEntity(gameData);

        //creating next frame
        //rendermap(rend,&gameData);
        renderMapFromFile(rend,&gameData);

        SDL_RenderDrawRect(rend,&re);
        renderEntityBoxList(gameData,rend);
        renderEntitys(gameData,rend);
        //todo messing with rotationg
     //   SDL_RenderCopyEx(rend,tex,&c,&t,90,&p,SDL_FLIP_VERTICAL);

        //present to screeen
        SDL_RenderPresent(rend);
        animateEntitys(gameData);
    }
    return 0;
}
