//
// Created by nathan on 10/24/2020.
//
/// MESSAGE CODES FOR NET CODE
//MESSAGE CODES
//common
#define DISCONNECT 0

//client -> server 1-9
#define REG 1
#define SUPPLY_UPDATE 2
#define REQUEST_UPDATE 3
#define REQUEST_PCOUNT 4

//server -> client 10-19

#define MSG_TYPE_PACKAGE 10
#define MSG_TYPE_REG_INFO 11
#define MSG_TYPE_PCOUNT_INFO 12