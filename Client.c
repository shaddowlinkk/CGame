//
// Created by nathan on 10/6/2020.
//

#include "Client.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#ifdef __WIN32
#include <winsock2.h>
#include <stdint.h>

#else
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define INVALID_SOCKET -1
#endif
int msleep(long tms)
{
    struct timespec ts;
    int ret;

    if (tms < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = tms / 1000;
    ts.tv_nsec = (tms % 1000) * 1000000;

    do {
        ret = nanosleep(&ts, &ts);
    } while (ret && errno == EINTR);

    return ret;
}
EntityPacket *updateEntity(EntityPacket data) {
#ifdef __WIN32
    WSADATA wsa;
    SOCKET server_sock, client_sock;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"failed to init win socket\n");
    } else {
    }
#else
    int server_sock, client_sock;
#endif
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    server_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sock == -1) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"socket creation failed...\n");
        exit(0);
    } else

        // assign IP, PORT
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("192.168.50.2");
        servaddr.sin_port = htons(8080);
    EntityPacket  *updatedData =malloc(sizeof(EntityPacket));

    uint32_t msg = htonl(1);
    uint32_t ou;
    int len = sizeof(servaddr);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"%i:%i:%i:\n",data.x,data.y,data.state);
    sendto(server_sock, (char *)&msg, sizeof(uint32_t), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"%i:%i:%i:\n",data.x,data.y,data.state);
    msg = htonl(data.x);
    sendto(server_sock, &msg, sizeof(uint32_t), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));

    msg = htonl(data.y);
    sendto(server_sock, &msg, sizeof(uint32_t), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));

    msg = htonl(data.state);
    sendto(server_sock, &msg, sizeof(uint32_t), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));

    recvfrom(server_sock, &ou, sizeof(uint32_t), 0, (struct sockaddr *) &servaddr, &len);
    updatedData->x=ntohl(ou);

    recvfrom(server_sock, &ou, sizeof(uint32_t), 0, (struct sockaddr *) &servaddr, &len);
    updatedData->y=ntohl(ou);

    recvfrom(server_sock, &ou, sizeof(uint32_t), 0, (struct sockaddr *) &servaddr, &len);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"%x:\n",ou);
    updatedData->state=ntohl(ou);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"%i:%i:%i:\n",updatedData->x,updatedData->y,updatedData->state);
    return updatedData;
}
