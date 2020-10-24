//
// Created by nathan on 10/6/2020.
//

#ifndef CGAME_CLIENT_H
#define CGAME_CLIENT_H
#include "GameCore.h"
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

typedef struct _packet{
    uint32_t state,x,y,ID;
}EntityPacket;

#endif //CGAME_CLIENT_H
