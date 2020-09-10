
#include "GameCore.h"
#include "MapRenderer.h"
#include "InputEvents.h"
#include "UtilRender.h"
#include "LinkedList.h"
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
/*    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"X:%i",(entity->cutter.x));
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Y:%i",(entity->cutter.y));*/
    if(count==5) {
        count=0;
        entity->cutter.y = (entity->cutter.h*state);
        entity->cutter.x = (entity->cutter.w * (((entity->cutter.x / entity->cutter.w)+1)% (entity->animationStates[state]-1)) );
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"X:%i",(((entity->cutter.x / entity->cutter.w)+1)% (entity->animationStates[state]-1)));
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Y:%i",(entity->cutter.h*state));
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"A:%i",(entity->animationStates[state]));
    }

    count++;
}

/**
 * moves an entity based on velocity
 * @param entity the entity that you want to move
 */
void moveEntity(Entity *entity){
    entity->sprite.x += entity->velx;
    entity->sprite.y += entity->vely;
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
    SDL_Surface  *surface = IMG_Load("test.png");
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
    }

    int running=1;
    SDL_Event event;
    Entity new;
/*    gameData.entityList[0].spriteSheet=tex;
    gameData.entityList[0].sprite.h=32;
    gameData.entityList[0].ID=0;
    gameData.entityList[0].sprite.w=16;
    gameData.entityList[0].sprite.x=gameData.window_w/2;
    gameData.entityList[0].sprite.y=gameData.window_h/2;
    gameData.entityList[0].animationStates[0]=7;
    gameData.entityList[0].animationStates[1]=11;
    gameData.entityList[0].animationStates[2]=11;
    gameData.entityList[0].animationStates[3]=8;
    gameData.entityList[0].animationStates[4]=9;
    gameData.entityList[0].animationStates[5]=16;
    gameData.entityList[0].cutter=new.sprite;*/

    new.spriteSheet=tex;
    new.sprite.h=32;
    new.ID=0;
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
    gameData.entCount=1;
    //inisalizing the list
    node *head=NULL;
    Insertnode(&head,NewElement(new));
    PrintList(&head);
    SDL_RenderClear(rend);
    Entity *en=Findnode(&head,0);;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"A:%i",(en->animationStates[0]));


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
/*        states=linkEntityToUserInput(&gameData.entityList[0],gameData);
        bindEntityToRect(&gameData.entityList[0],re);
        bindEntityToBoard(&gameData.entityList[0],gameData);
        moveEntity(&gameData.entityList[0]);*/

        states=linkEntityToUserInput(en,gameData);
        bindEntityToRect(en,re);
        bindEntityToBoard(en,gameData);
        moveEntity(en);

        //creating next frame
        rendermap(rend,&gameData);
        SDL_RenderDrawRect(rend,&re);
        SDL_RenderDrawRect(rend,&en->sprite);
       // renderEntityBox(gameData,rend);
       // SDL_RenderCopy(rend, gameData.entityList[0].spriteSheet,&gameData.entityList[0].cutter,&gameData.entityList[0].sprite);

        SDL_RenderCopy(rend, en->spriteSheet,&en->cutter,&en->sprite);

        //present to screeen
        SDL_RenderPresent(rend);
        animate(en,states);
    }
    return 0;
}
