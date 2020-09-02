
#include "GameCore.h"
#include "MapRenderer.h"
#include <direct.h>


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


int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);
    GameData gameData;
    SDL_Window *win = SDL_CreateWindow("CGame",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,640,640,SDL_WINDOW_OPENGL);
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
    surface = IMG_Load("bk.png");
    SDL_Texture *text = SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    if(!text){
        SDL_Log("error %s\n",SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 4;
    }


    int running=1;
    SDL_Event event;
    Entity player;
    player.spriteSheet=tex;
    player.sprite.h=32;
    player.sprite.w=16;
    player.sprite.x=0;
    player.sprite.y=0;
    player.animationStates[0]=7;
    player.animationStates[1]=11;
    player.animationStates[2]=11;
    player.animationStates[3]=8;
    player.animationStates[4]=9;
    player.animationStates[5]=16;
    player.cutter=player.sprite;
    SDL_RenderClear(rend);

    while(running) {
        int states=0;
        // Process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_UP]||state[SDL_SCANCODE_W]) {
            states=4;
            player.sprite.y -= 1;
        }
        else if(state[SDL_SCANCODE_DOWN]||state[SDL_SCANCODE_S]){
            states=3;
            player.sprite.y+=1;
        }
        else if(state[SDL_SCANCODE_LEFT]||state[SDL_SCANCODE_A]) {
            states=1;
            player.sprite.x -= 1;
        }
        else if(state[SDL_SCANCODE_RIGHT]||state[SDL_SCANCODE_D]) {
            states=2;
            player.sprite.x += 1;
        }

        SDL_RenderClear(rend);
        rendermap(rend,&gameData);
        SDL_RenderCopy(rend,player.spriteSheet,&player.cutter,&player.sprite);
        SDL_RenderPresent(rend);
        animate(&player,states);
    }
    return 0;
}
