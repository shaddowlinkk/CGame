//
// Created by nathan on 9/7/2020.
//

#ifndef CGAME_LINKEDLIST_H
#define CGAME_LINKEDLIST_H
#include "GameCore.h"
typedef struct _node
{
    Entity item;
    struct _node *next;
} node;

void Removenode(node **head, int ID);
void Insertnode(node **head, node *newp);
node *NewElement(Entity new);

#endif //CGAME_LINKEDLIST_H
