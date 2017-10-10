/**
 * @author: Alexander Mark Thompson
 * @title: Stack Library File
 * @description: Functions to structure a stack using a doubly linked list.
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "dll.h"

/**
 * Function to make a new Stack with a doubly linked list.
 */
stack *newStack(void (*d)(FILE *, void *))
{
	dll *newDLLStruct = newDLL(d);
	stack *newStackStruct = (stack *) malloc(sizeof(stack));
	newStackStruct->stackStruct = newDLLStruct;
	return newStackStruct;
}

/**
 * Function to push a node onto the stack
 * @param items [a stack]
 * @param value [value of node]
 */
void push(stack *items, void *value)
{
	insertDLL(items->stackStruct, 0, value);
}

/**
 * Function to pop a node off of a stack.
 * @param  items [a stack]
 * @return       [the popped node]
 */
void *pop(stack *items)
{
	return removeDLL(items->stackStruct, 0);
}

/**
 * Function to get the head value of the stack
 * @param  items [a stack]
 * @return       [description]
 */
void *peekStack(stack *items)
{
	return items->stackStruct->head->value;
}

/**
 * Function to get the size of a stack
 * @param  items [a stack]
 * @return       [the size of the stack]
 */
int sizeStack(stack *items)
{
	return items->stackStruct->size;
}

/**
 * Function to display a stack
 * @param fp    [where to display the data]
 * @param items [a stack]
 */
void displayStack(FILE *fp, stack *items)
{
	displayDLL(fp, items->stackStruct);
}