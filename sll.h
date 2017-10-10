/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 -- Assignment 2 -- Red Black Trees
 */

#ifndef __SLL_INCLUDED__
#define __SLL_INCLUDED__

typedef struct sllnode
	{
		void *value;
		struct sllnode *next;
	}sllnode;

typedef struct sll
	{
		sllnode *head;
		sllnode *tail;
		int size;
		void (*display)(FILE *, void *);
	}sll;

extern sll *newSLL(void (*d)(FILE *, void *));				
extern void insertSLL(sll *items, int index, void *value);	
extern void *removeSLL(sll *items, int index);				
extern void unionSLL(sll *recipient, sll *donor);			
extern void *getSLL(sll *items, int index);					
extern int sizeSLL(sll *items);
extern void displaySLL(FILE *, sll *items);

#endif