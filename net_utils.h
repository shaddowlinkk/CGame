//
// Created by nathan on 10/24/2020.
//

#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"
#define PORT     8080
#define MAXLINE 84
#ifdef __WIN64
#include <winsock2.h>
#include <stdint.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#endif

typedef struct _packet{
    uint32_t state,x,y,ID;
}EntityPacket;


int extract_msg_code(char** msg);
void sendPrepMsg(char* msg, int sock);
void sendCode(int code,int server_sock);
void recevMsg(int sockdef,char *msg);
void sendPacket(int msgCode,EntityPacket *packet,int sock);
void decodePacket(EntityPacket *packet);
int getRegInfo();
int getpcount();