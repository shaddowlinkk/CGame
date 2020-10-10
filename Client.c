//
// Created by nathan on 10/6/2020.
//

#include "Client.h"

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
int regClient(SOCKET server_sock, SOCKADDR_IN servaddr){
/*    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(server_sock, (struct sockaddr*)&servaddr, sizeof(servaddr));*/


    uint32_t msg = htonl(0);
    uint32_t ou;
    send(server_sock, (char *)&msg, sizeof(uint32_t), 0);
    int len = sizeof(servaddr);
    recv(server_sock, &ou, sizeof(uint32_t), 0);
    int out = ntohl(ou);


/*    ou = htonl(-1);
    send(server_sock, &ou, sizeof(uint32_t), 0);
    shutdown(server_sock,SD_BOTH);*/
    return out;
}
void updateEntity(EntityPacket data,SOCKET server_sock, SOCKADDR_IN servaddr,int id) {
/*    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(server_sock, (struct sockaddr*)&servaddr, sizeof(servaddr));*/

    uint32_t msg = htonl(1);
    send(server_sock, (char *)&msg, sizeof(uint32_t), 0);
    msg = htonl(id);
    send(server_sock, (char *)&msg, sizeof(uint32_t), 0);
    msg = htonl(data.x);
    send(server_sock, &msg, sizeof(uint32_t), 0);

    msg = htonl(data.y);
    send(server_sock, &msg, sizeof(uint32_t), 0);

    msg = htonl(data.state);
    send(server_sock, &msg, sizeof(uint32_t), 0);


/*    uint32_t ou = htonl(-1);
    send(server_sock, &ou, sizeof(uint32_t), 0);
    shutdown(server_sock,SD_BOTH);*/

}

EntityPacket *getUpdate(SOCKET server_sock, SOCKADDR_IN servaddr,int id) {
/*    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(server_sock, (struct sockaddr*)&servaddr, sizeof(servaddr));*/

    EntityPacket *updatedData = malloc(sizeof(EntityPacket));

    uint32_t msg = htonl(2);
    uint32_t ou;
    int len = sizeof(servaddr);
    int playerNum;
    send(server_sock, (char *) &msg, sizeof(uint32_t), 0);
    msg = htonl(id);
    send(server_sock, (char *) &msg, sizeof(uint32_t), 0);

    recv(server_sock, &ou, sizeof(uint32_t), 0);
    playerNum = ntohl(ou);
    if (playerNum >= 2) {
        recv(server_sock, &ou, sizeof(uint32_t), 0);
        updatedData->x = ntohl(ou);

        recv(server_sock, &ou, sizeof(uint32_t), 0);
        updatedData->y = ntohl(ou);

        recv(server_sock, &ou, sizeof(uint32_t), 0);
        updatedData->state = ntohl(ou);
        return updatedData;
    }


/*    ou = htonl(-1);
    send(server_sock, &ou, sizeof(uint32_t), 0);
    shutdown(server_sock,SD_BOTH);*/
    return NULL;
}
