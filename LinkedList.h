//
// Created by nathan on 9/7/2020.
//

#ifndef CGAME_LINKEDLIST_H
#define CGAME_LINKEDLIST_H
#include "GameCore.h"


void Removenode(node **head, int ID);
void Insertnode(node **head, node *newp);
node *NewElement(Entity new);
Entity *Findnode(node **head, int ID);
void PrintList(node **head);

#endif //CGAME_LINKEDLIST_H
