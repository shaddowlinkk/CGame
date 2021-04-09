#include "GameCore.h"
#include "Rendering.h"
#include "base_code.h"
int main(int argc, char **argv) {
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
    void *main=CreateThread(NULL,0,mainSystem,&data,0,&ids[0]);
    while (1){
        SetEvent(data.mainSystem);
        Sleep(50);
    }

}
