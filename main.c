#include <stdio.h>
#include "GameCore.h"
#include <SDL2/SDL.h>
#include <direct.h>
#include <SDL2/SDL_image.h>

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("CGame",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,800,800,SDL_WINDOW_OPENGL);
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
    Entity player;
    player.spriteSheet=tex;
    player.sprite.h=32;
    player.sprite.w=16;
    player.sprite.x=0;
    player.sprite.y=0;
    player.cutter=player.sprite;
    SDL_RenderClear(rend);
    while(running) {
        // Process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if(event.type == SDL_KEYUP){
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_UP:
                        player.cutter.y=(32*4);
                        player.sprite.y-=10;
                        break;
                    case SDL_SCANCODE_DOWN:
                        player.cutter.y=0;
                        player.sprite.y+=10;
                        break;
                    case SDL_SCANCODE_LEFT:
                        player.cutter.y=(32*1);
                        player.sprite.x-=10;
                        break;
                    case SDL_SCANCODE_RIGHT:
                        player.cutter.y=(32*2);
                        player.sprite.x+=10;
                        break;
                    case SDL_SCANCODE_F1:
                        SDL_RenderPresent(rend);
                        break;
                    case SDL_SCANCODE_F3:
                        SDL_RenderClear(rend);
                        break;
                    case SDL_SCANCODE_F2:
                        player.cutter.x=0;
                        player.cutter.y=(32*4);

                        break;
                }
            }
        }
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend,player.spriteSheet,&player.cutter,&player.sprite);
        SDL_RenderPresent(rend);
    }
    return 0;
}
