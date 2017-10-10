/**
 * @author: Alexander Mark Thompson
 * @title: Stack Header File
 * @description: Sets up a structure for a Stack, as 
 * 				 well as public functions that will be used to edit
 * 				 a stack.
 */

#ifndef STACK_H_
#define STACK_H_

#include "dll.h"
#include <stdio.h>

/**
 * Structure for a stack.
 * Has pointers to a head node, tail node, stack's size, and
 * a display function. The head and tail nodes are doubly linked
 * list nodes.
 */
typedef struct stack
{
	dll *stackStruct;
} stack;

extern stack *newStack(void (*d)(FILE *, void *));
extern void push(stack *items, void *value);
extern void *pop(stack *items);
extern void *peekStack(stack *items);
extern int sizeStack(stack *items);
extern void displayStack(FILE *, stack *items);

#endif