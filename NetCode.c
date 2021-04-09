//
// Created by nathan on 2/1/2021.
//
#include "net_utils.h"
#include "NetCode.h"
#include "LinkedList.h"

#include "FileIO.h"
DWORD runNetCode(void *data) {
    SystemData *system = (SystemData *)data;

    WSADATA wsa;
    SOCKET server_sock, client_sock;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "failed to init win socket\n");
    } else {
    }

    struct sockaddr_in servaddr, cli;

    // socket create and varification
    server_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sock == -1) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "socket creation failed...\n");
        exit(0);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.50.2");
    servaddr.sin_port = htons(8080);
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(server_sock, (struct sockaddr *) &servaddr, sizeof(servaddr));

    EntityPacket tmp;
    char msgfromserver[MAXLINE];
    char *msg =msgfromserver;
    sendCode(REG,server_sock);

    Entity other=readEntityFromFile("play.ent",*system->render);
    other.ID=1;
    Entity *entity=Findnode(&system->gameData->start,0);
    Entity *player2;
    tmp.x = entity->sprite.x;
    tmp.y = entity->sprite.y;
    tmp.state = entity->state;
    tmp.ID = 100;
    int flag=0;
    int l=1;
    while (l) {
        sendPacket(SUPPLY_UPDATE, &tmp, server_sock);
        if (flag == 0) {
            sendCode(REQUEST_PCOUNT, server_sock);
            recevMsg(server_sock, msgfromserver);
            if (extract_msg_code(&msg) == 12) {
                if (getpcount() >= 2) {
                    Insertnode(&system->gameData->start, NewElement(other));
                    player2 = Findnode(&system->gameData->start, 1);
                    sendCode(REQUEST_UPDATE, server_sock);
                    recevMsg(server_sock, msgfromserver);
                    extract_msg_code(&msg);
                    decodePacket(&tmp);
                    player2->sprite.x = tmp.x;
                    player2->sprite.y = tmp.y;
                    player2->state = tmp.state;
                    player2->ID = 1;
                    flag = 1;
                }
            }
        } else {
            sendCode(REQUEST_UPDATE, server_sock);
            recevMsg(server_sock, msgfromserver);
            extract_msg_code(&msg);
            decodePacket(&tmp);
            player2->sprite.x = tmp.x;
            player2->sprite.y = tmp.y;
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "x:%i\n",tmp.x);
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "y:%i\n",tmp.y);
            player2->state = tmp.state;
            player2->ID = 1;
            flag = 1;
        }

    }
}