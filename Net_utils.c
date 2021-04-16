//
// Created by nathan on 10/24/2020.
//


#include "Net_utils.h"
/**
 * gets the massage code from the netcode packet
 * @param msg the packet that you want to get code from
 * @return the massge code
 */
int extract_msg_code(char** msg) {
    return atoi(strtok(*msg, " "));
}
/**
 * sends a message to a socket
 * @param msg the message that you want to sent
 * @param sock the socket definition that you want to send to
 */
void sendPrepMsg(char* msg, int sock){
    if (send(sock, msg, MAXLINE, 0) == -1) {
        printf("error sending msg\n");
    }

}
/**
 * sends a mssage code to the a socket
 * @param code the code that you want to send
 * @param server_sock the socket definition that you want to send to
 */
void sendCode(int code,int server_sock){
    char msg[MAXLINE];
    sprintf(msg,"%d",code);
    sendPrepMsg(msg,server_sock);
}
/**
 * sends a packet to a socket
 * @param msgCode massage code that you want to send with packet
 * @param packet the packet of entity data that you want to sent
 * @param sock the socket definition that you want to send to
 */
void sendPacket(int msgCode,EntityPacket *packet,int sock){
    char msg[MAXLINE];
    sprintf(msg,"%d %d %d %d %d\n",msgCode,packet->x,packet->y,packet->state,packet->ID);
    sendPrepMsg(msg,sock);
}

int getRegInfo(){
    return atoi(strtok(NULL, " "));
}
/**
 * gets the player count
 * @return the player count
 */
int getpcount(){
    return atoi(strtok(NULL, " "));
}
/**
 * receves a message from the server
 * @param sockdef the socket definition that you want to revive from
 * @param msg whare you want to save the massage to
 */
void recevMsg(int sockdef,char *msg){

    int bytesrecv=0;
    if ((bytesrecv=recv(sockdef,msg,MAXLINE,0))==-1){
        printf("error on receve");
    }
}
/**
 * this decodes the packet data
 * @param packet the packet entity that you want to save to
 */
void decodePacket(EntityPacket *packet){
    packet->x=atoi(strtok(NULL, " "));
    packet->y=atoi(strtok(NULL, " "));
    packet->state=atoi(strtok(NULL, " "));
    packet->ID=atoi(strtok(NULL, " "));

}
