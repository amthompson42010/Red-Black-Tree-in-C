/**
 * @author: Alexander Mark Thompson
 * @title: Doubly Linked List Header File
 * @description: Sets up a structure for a Doubly Linked List, as 
 * 				 well as public functions that will be used to edit
 * 				 a doubly linked list.
 */
#ifndef DLL_H_
#define DLL_H_

#include <stdio.h>

/**
 * A structure for a doubly linked list node.
 * Has pointers to a node's value, the next node in the list,
 * and a pointer to the previous node in the list.
 */
typedef struct dllNode
{
	void *value;
	struct dllNode *next;
	struct dllNode *previous;
} dllNode;

/**
 * A structure for a doubly linked list.
 * Has pointers to a list's head node, tail node, list size,
 * and a display function.
 */
typedef struct dll
{
	dllNode *head;
	dllNode *tail;
	int size;
	void (*display)(FILE *, void *);
} dll;

extern dll *newDLL(void (*d)(FILE *, void *));
extern void insertDLL(dll *items, int index, void *value);
void *removeDLL(dll *items, int index);
void unionDLL(dll *recipient, dll *donor);
void *getDLL(dll *items, int index);
int sizeDLL(dll *items);
void displayDLL(FILE *, dll *items);

#endif