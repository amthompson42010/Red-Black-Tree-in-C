/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 -- Assignment 2 -- Red Black Trees
 */

#include "sll.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef __QUEUE_INCLUDED__
#define __QUEUE_INCLUDED__

typedef struct queue
{
	sll *list;
}queue; 


extern queue *newQueue(void (*d)(FILE *,void *));  
extern void enqueue(queue *items,void *value);      
extern void *dequeue(queue *items);                 
extern void *peekQueue(queue *items);              
extern int sizeQueue(queue *items);
extern void displayQueue(FILE *fp,queue *items);

#endif