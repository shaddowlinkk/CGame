#include "GameCore.h"
#include "Rendering.h"
#include "Base_code.h"
#include "NetCode.h"
int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);
    unsigned long ids[3];
    SystemData data;
    data.render=NULL;
    data.gameData=(GameData *)malloc(sizeof(GameData));
    data.mainSystem = CreateEvent(NULL, TRUE, FALSE, TEXT("MainSystem"));
    data.rendering = CreateEvent(NULL, TRUE, FALSE, TEXT("Rendering"));
    data.systemIO = CreateEvent(NULL, TRUE, FALSE, TEXT("SyStemIO"));
    data.lockEntityies = CreateMutex(NULL, FALSE, NULL);
    data.LockGameData = CreateMutex(NULL, FALSE, NULL);
    void *rendering=CreateThread(NULL,0,renderingSystem,&data,0,&ids[0]);
    //not right
    WaitForSingleObject(data.mainSystem,INFINITE);
    ResetEvent(data.mainSystem);
    void *main=CreateThread(NULL,0,mainSystem,&data,0,&ids[1]);
    CreateThread(NULL,0,runNetCode,&data,0,&ids[2]);
    SetEvent(data.systemIO);
    while (1){
        SetEvent(data.mainSystem);
        Sleep(100);
        //Sleep(50);
    }

}
