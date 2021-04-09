//
// Created by nathan on 9/6/2020.
//

#include "Rendering.h"
#include "LinkedList.h"
#include "MapRenderer.h"
#include "BoundingboxUtil.h"
#include <stdio.h>
/**
 * renderd the SDL RECT that defines how an entity is renders
 * @param data the game state
 * @param rend an SDL renderer
 */
void renderTriggerBox(GameData *data, SDL_Renderer *rend){

    for (int i = 0; i < data->triggerCount; i++) {
          SDL_RenderDrawRect(rend, &data->triggerList[i].Rect);
    }
}
void renderEntityBoxList(GameData *data, SDL_Renderer *rend){
    node **tracer = &data->start;
    if(!*tracer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"no list data in entity linked list 1");
    }else {
        while (*tracer) {
            SDL_RenderDrawRect(rend, &(*tracer)->item.sprite);
            tracer = &(*tracer)->next;
        }
    }
}

void renderEntitys(GameData *data, SDL_Renderer *rend){
    node **tracer = &data->start;
    if(!*tracer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"no list data in entity linked list 2");
    }else {
        while (*tracer) {
            SDL_RenderCopy(rend, (*tracer)->item.spriteSheet,&(*tracer)->item.cutter,&(*tracer)->item.sprite);
            tracer = &(*tracer)->next;
        }
    }
}
void renderRoomCode(GameData *data, SDL_Renderer *rend,TTF_Font *font, SDL_Color color){
    char buffer[100];
    SDL_Surface * surface;
    SDL_Texture * texture;
    sprintf(buffer, "room: %p", data->currentRoom);
    surface = TTF_RenderText_Solid(font, buffer, color);
    texture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);


    SDL_Rect dstrect = { 0, 0, 256,32 };
    SDL_RenderCopy(rend,texture,NULL,&dstrect);
    SDL_DestroyTexture(texture);
}

void renderInventory(GameData *gameData,SDL_Renderer *rend){
    Entity *player = Findnode(&gameData->start,0);
    if (gameData->inventory.state!=0){
        gameData->inventory.sprite.x=player->sprite.x-(172/2)+(player->cutter.w/2);
        gameData->inventory.sprite.y=player->sprite.y-(60);
        SDL_RenderCopy(rend,gameData->inventory.spriteSheet,&gameData->inventory.cutter,&gameData->inventory.sprite);
    }
}

void renderBoundingBox(BoundingBox *box , SDL_Renderer *rend){
    SDL_Point rect[5];
    rect[0]=box->coords[0];
    rect[1]=box->coords[1];
    rect[2]=box->coords[2];
    rect[3]=box->coords[3];
    rect[4]=box->coords[0];
    SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLines(rend,rect,5);
    SDL_SetRenderDrawColor(rend, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawPoint(rend,box->center.x,box->center.y);
    SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
}
void renderWallBox(GameData *data, SDL_Renderer *rend){
    node **trace = &data->currentRoom->staticBlocks;
    while (*trace){
        renderBoundingBox(&(*trace)->item.box,rend);
        trace = &(*trace)->next;
    }
}
/**
 * This function moves the cutting SDL_Rect to the next frame of the animation
 * @param entity what ever entity you are trying to animate.
 * @param state the animation state that corresponds to the action you are trying to animate
 */
void animate(Entity *entity, int state){
    // todo need to remove that and make it native to the rendering loop
    entity->cutter.y = (entity->cutter.h*state);
    entity->cutter.x = (entity->cutter.w * (((entity->cutter.x / entity->cutter.w)+1)% (entity->animationStates[state]-1)));

}

void animateEntitys(SystemData *data){
    //count slows the animation todo need to remove that and make it native to the rendering loop
    static int count =0;
        DWORD wait = WaitForSingleObject(data->LockGameData, 2);
        if (wait==WAIT_OBJECT_0) {
            node **tracer = &data->gameData->start;
            if (!*tracer) {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                               "no list data in entity linked list 6");
            } else {
                if (count == 3) {
                    count = 0;
                    while (*tracer) {
                        animate(&(*tracer)->item, (*tracer)->item.state);
                        tracer = &(*tracer)->next;
                    }

                }
                count++;
            }
            ReleaseMutex(data->LockGameData);
        }else{
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"failed animate");
        }
}

DWORD WINAPI renderingSystem(void *vararg){
    SystemData *system=(SystemData *)vararg;

    TTF_Init();
    SDL_Window *win = SDL_CreateWindow("CGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (mapsize * 32),
                                       mapsize * 32, SDL_WINDOW_OPENGL);
    SDL_GetWindowSize(win, &system->gameData->window_w, &system->gameData->window_h);
    if (!win) {
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    if (!rend) {
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 2;
    }
    DWORD wait = WaitForSingleObject(system->LockGameData, 2);
    if (wait==WAIT_OBJECT_0) {
        system->render=&rend;
        SDL_Surface *s = IMG_Load(".\\Textures\\Floor.png");
        system->gameData->GroundSheet = SDL_CreateTextureFromSurface(rend, s);
        SDL_FreeSurface(s);
        ReleaseMutex(system->LockGameData);
    }
    TTF_Font * font = TTF_OpenFont("arial.ttf", 25);
    SDL_Color color = { 255, 255, 255 };
    SDL_Event event;
    SetEvent(system->mainSystem);
    int lvc;
    while (lvc == 0) {
        if(WaitForSingleObject(system->rendering,0)==WAIT_OBJECT_0) {
           while (SDL_PollEvent(&event)) {
               if (event.type == SDL_KEYDOWN) {
                   if (event.key.keysym.scancode == SDL_SCANCODE_F2) {
                       system->gameData->inventory.state = ((system->gameData->inventory.state + 1) % 2);
                   }
               }
           }
/*                if (event.type == SDL_QUIT) {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "key detected");
                }*/
            SDL_RenderClear(rend);
            renderMapFromFile(rend,system->gameData);
            renderRoomCode(system->gameData, rend, font, color);
            //renderTriggerBox(system->gameData,rend);
            //renderEntityBoxList(system->gameData,rend);
            //renderWallBox(system->gameData, rend);
            //renderBoundingBox(player->box,rend);
            renderEntitys(system->gameData, rend);
            renderInventory(system->gameData, rend);

            //present to screee
            SDL_RenderPresent(rend);
            animateEntitys(system);
            //ResetEvent(system->rendering);
        }

    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}