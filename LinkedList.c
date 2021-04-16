//
// Created by nathan on 9/7/2020.
//
#include <stdio.h>
#include "LinkedList.h"
#define TRUE 1
#define FALSE 0
typedef int BOOL;
/**
 * creates new node for the list
 * @param entity The entity that you want to add to the list
 * @return
 */
node *NewElement(Entity entity)
{
    node *newp;
    newp = (node *) malloc (sizeof(node));
    newp -> item = entity;
    newp -> next = NULL;
    return newp;
}



/**
 * adds a new node to the linked list
 * @param head a pointer to the start of the linked list
 * @param newp the new node that you want to add
 */
void Insertnode(node **head, node *newp)
{
    node **tracer = head;

    while((*tracer)&&((*tracer)->item.ID)<newp->item.ID)
    {
        tracer = &(*tracer)->next;
    }

    newp -> next = *tracer;
    *tracer = newp;
}

/**
 * removes a node from the linked list
 * @param head a pointer to the start of the linked list
 * @param ID the ID of the entity that you want to remove
 */
void Removenode(node **head, int ID)
{
    BOOL present = FALSE;
    node *old;
    node **tracer = head;

    while((*tracer) && !(present = (*tracer)->item.ID==ID))
        tracer = &(*tracer)->next;

    if(present)
    {
        old = *tracer;
        *tracer = (*tracer)->next;
        free(old); // free up remainder of list element
    }
}
/**
 * finds a node based on id
 * @param head list to search through
 * @param ID the id that you want to fine
 * @return pointer to the found node
 */
Entity *Findnode(node **head, int ID)
{
    BOOL present = FALSE;
    node *old;
    node **tracer = head;

    while((*tracer) && !(present = (*tracer)->item.ID==ID))
        tracer = &(*tracer)->next;

    if(present)
    {
        //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"FOUND:%i",(*tracer)->item.ID);
        Entity *out = &(*tracer)->item;
        return out;
    }
}

/**
 * prints linked list nodes id (should do this SDL doesnt print to stdout)
 * @param head
 */
void PrintList(node **head)
{
    //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"test");
    node **tracer = head;
    while (*tracer) {
        //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"%i",(*tracer)->item.ID);
        tracer = &(*tracer)->next;
    }
}