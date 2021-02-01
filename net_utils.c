//
// Created by nathan on 10/24/2020.
//


#include "net_utils.h"

int extract_msg_code(char** msg) {
    return atoi(strtok(*msg, " "));
}

void sendPrepMsg(char* msg, int sock){
    if (send(sock, msg, MAXLINE, 0) == -1) {
        printf("error sending msg\n");
    }

}
void sendCode(int code,int server_sock){
    char msg[MAXLINE];
    sprintf(msg,"%d",code);
    sendPrepMsg(msg,server_sock);
}
void sendPacket(int msgCode,EntityPacket *packet,int sock){
    char msg[MAXLINE];
    sprintf(msg,"%d %d %d %d %d\n",msgCode,packet->x,packet->y,packet->state,packet->ID);
    sendPrepMsg(msg,sock);
}

int getRegInfo(){
    return atoi(strtok(NULL, " "));
}
int getpcount(){
    return atoi(strtok(NULL, " "));
}

void recevMsg(int sockdef,char *msg){

    int bytesrecv=0;
    if ((bytesrecv=recv(sockdef,msg,MAXLINE,0))==-1){
        printf("error on receve");
    }
}

void decodePacket(EntityPacket *packet){
    packet->x=atoi(strtok(NULL, " "));
    packet->y=atoi(strtok(NULL, " "));
    packet->state=atoi(strtok(NULL, " "));
    packet->ID=atoi(strtok(NULL, " "));

}
