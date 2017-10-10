/**
 * @author: Alexander Mark Thompson
 * @title: Doubly Linked List Library File
 * @description: Functions to structure a doubly linked list.
 */

#include <stdio.h>
#include <stdlib.h>
#include "dll.h"



dllNode *newNode, *current, *temp;

/**
 * Function to create a new Doubly Linked List.
 * Sets the initial values of the list to 0.
 */
dll *newDLL(void (*d)(FILE * , void *))
{
	dll *items = (dll *) malloc(sizeof(dll));

	if(items == 0)
	{
		fprintf(stderr, "out of memory");
		exit(-1);
	}

	// Initializing parameters
	items->head = 0;
	items->size = 0;
	items->display = d;

	return items;
}

/** 
 * Function to insert into the doubly linked list.
 * This function checks to see if the passed in list is empty, and then if not,
 * checks to see if the insertion needs to be in the front of the list, the back 
 * of the list, or a given index that is not the front or tail.
 */
void insertDLL(dll *items, int index, void *value)
{
    
    // In the case that the list is empty (items->size == 0):
     if((items->size == 0) && (index == 0)) {
          // Allocate memory for the node to be inserted into the list,
          // and point the list's head and tail node pointers to the newly
          // constructed node.
          items->head = malloc(sizeof(dllNode));
          items->tail = items->head;
          // Since this is a DLL, we need to ensure that the previous and
          // next pointers wrap back around to the same node:
          items->head->next = items->head;
          items->head->previous = items->head;
          // Set the node's value.
          items->head->value = value;
          // Finally, increment the size of the dll.
          ++items->size;
     // In the case that the list is non-empty:
     } else if(items->size > 0) {
          // If the data is to be inserted at the head of the list:
          if(index == 0) {
               // Allocate memory for a new node and set its member's data.
               dllNode *newnode = malloc(sizeof(dllNode));
               newnode->value = value;
               // Set the new node's next pointer to the current head,
               // and set the head's previous pointer to the new node.
               newnode->next = items->head;
               items->head->previous = newnode;
               // Set the new node as the new head.
               items->head = newnode;
               // Set the new head's previous pointer to the tail, and the
               // tail's pointer to the new head.
               items->head->previous = items->tail;
               items->tail->next = items->head;
               // Incremtn the size.
               ++items->size;
          // If inserting data at the tail of the list:
          } else if(index == items->size) {
               // Allocate memory for a new node and set its member's data.
               dllNode *newnode = malloc(sizeof(dllNode));
               newnode->value = value;
               // Set the new node's next pointer to the current head,
               // and set the head's previous pointer to the new node.
               newnode->next = items->head;
               items->head->previous = newnode;
               // Set the current tail's next pointer to the new node,
               // and set the new node's previous pointer to the current tail.
               items->tail->next = newnode;
               newnode->previous = items->tail;
               // Set the new node as the new tail.
               items->tail = newnode;
               // Increment the size.
               ++items->size;
          // If data is to be inserted someplace in the middle of the list:
          } else {
               // If index is closer to head than tail:
               if(index <= (items->size / 2)) {
                    // Allocate memory for a new node and set its member's data.
                    dllNode *newnode = malloc(sizeof(dllNode));
                    newnode->value = value;
                    // Create a tracking node pointer and counter.
                    dllNode *spot = items->head;
                    int counter = 0;
                    // Loop to the node just before the insert index.
                    while(counter < index - 1) {
                         spot = spot->next;
                         ++counter;
                    }
                    // Set the new node's previous pointer to the spot, and
                    // set the new node's next pointer to the spot's next pointer.
                    newnode->previous = spot;
                    newnode->next = spot->next;
                    // Set the spot's next pointer to the new node.
                    spot->next = newnode;
                    // Set the new node's next previous pointer to the new node.
                    newnode->next->previous = newnode;
                    // Increment the size.
                    ++items->size;
               // If index is closer to the tail than head:
               } else {
                    // Allocate memory for a new node and set its member's data.
                    dllNode *newnode = malloc(sizeof(dllNode));
                    newnode->value = value;
                    // Create a tracking node pointer and counter.
                    dllNode *spot = items->tail;
                    int counter = 0;
                    // Loop to the node just before the insert index.
                    while(counter < (items->size - index)) {
                         spot = spot->previous;
                         ++counter;
                    }
                    // Set the new node's previous pointer to the spot, and
                    // set the new node's next pointer to the spot's next pointer.
                    newnode->previous = spot;
                    newnode->next = spot->next;
                    // Set the spot's next pointer to the new node.
                    spot->next = newnode;
                    // Set the new node's next previous pointer to the new node.
                    newnode->next->previous = newnode;
                    // Increment the size.
                    ++items->size;
               }
          }
     }
}

/**
 * Function to remove a node from a doubly linked list.
 * @param  items [doubly linked list]
 * @param  index [index value to delete]
 * @return       [deleted value]
 */
void *removeDLL(dll *items, int index)
{
	if(index == 0) {
          // Go ahead and save the return value.
          void *value = items->head->value;
          // Create a temporary node pointer to point at the current head,
          // and move the head pointer to the pointer's next pointer.
          dllNode *temp = items->head;
          items->head = items->head->next;
          // Set the new head's previous point to the tail, and set the tail's
          // next pointer to the new head.
          items->head->previous = items->tail;
          items->tail->next = items->head;
          // Free the old head.
          free(temp);
          // Decrement the size and return the extracted value.
          --items->size;
          return value;
     // If removing form the back (tail) of the list:
     } else if(index == items->size - 1) {
          // Go ahead and save the return value.
          void *value = items->tail->value;
          // Create a temporary node pointer to point at the current tail,
          // and move the tail pointer to the pointer's previous pointer.
          dllNode *temp = items->tail;
          items->tail = items->tail->previous;
          // Set the new tail's next pointer to the head, and set the head's
          // previous pointer to the new tail.
          items->tail->next = items->head;
          items->head->previous = items->tail;
          // Free the old tail.
          free(temp);
          // Decrement the size and return the extracted value.
          --items->size;
          return value;
     // If removing from someplace in the middle of the list:
     } else {
          // If index is closer to head than tail:
          if(index <= (items->size / 2)) {
               // Create a placeholder node pointer and associated counter.
               dllNode *spot = items->head;
               int counter = 0;
               // Advance to the node before the current index node.
               while(counter < index - 1) {
                    spot = spot->next;
                    ++counter;
               }
               // Save the value.
               void *value = spot->next->value;
               // Create a temporary node pointer to keep a reference to the
               // next node.
               dllNode *temp = spot->next;
               // Set the placeholder node pointer's next pointer to the
               // next, next node.
               spot->next = spot->next->next;
               // Set the spot's next, next node's previous pointer back to spot.
               spot->next->previous = spot;
               // Free the old node.
               free(temp);
               // Decrement the size and return the value.
               --items->size;
               return value;
          // If the index is closer to tail than head:
          } else {
               // Create a placeholder node pointer and associated counter.
               dllNode *spot = items->tail;
               int counter = 0;
               // Advance to the node before the current index node.
               while(counter < (items->size - index)) {
                    spot = spot->previous;
                    ++counter;
               }
               // Save the value.
               void *value = spot->next->value;
               // Create a temporary node pointer to keep a reference to the
               // next node.
               dllNode *temp = spot->next;
               // Set the placeholder node pointer's next pointer to the
               // next, next node.
               spot->next = spot->next->next;
               // Set the spot's next, next node's previous pointer back to spot.
               spot->next->previous = spot;
               // Free the old node.
               free(temp);
               // Decrement the size and return the value.
               --items->size;
               return value;
          }
     }
}

/**
 * Function to join two lists.
 * @param recipient [doubly linked list]
 * @param donor     [doubly linked list]
 */
void unionDLL(dll *recipient, dll *donor)
{
    // If the donor list is empty
    if(donor->size == 0)
    {
        return;
    }
    // if the recipient list is empty
    else if(recipient->size == 0)
    {
        recipient->head = donor->head;
        recipient->tail = donor->tail;
        recipient->size = donor->size;
        donor->head = donor->tail = 0;
        donor->size = 0;
        return;
    }
    // If both lists are not empty
    else
    {
        recipient->tail->next = donor->head;
        donor->head->previous = recipient->tail;
        recipient->head->previous = donor->tail;
        donor->tail->next = recipient->head;
        recipient->tail = donor->tail;

        // Grows the recipient list so that the donor
        // list can fit
        recipient->size += donor->size;

        // Clears the donor list
        donor->head = donor->tail = 0;
        donor->size = 0;
    }
}

/**
 * Function to get a node in the doubly linked list based of an index.
 * @param  items [doubly linked list]
 * @param  index [index to be found]
 * @return       [node that was being searched for]
 */
void *getDLL(dll *items, int index)
{
	current = items->head;
	int count = 0;

	// This is needed to keep this function in linear time.
	float middle = (int) (items->size / 2);

	if(index == 0)
	{
		return current->value;
	}
	else if(index == items->size)
	{
		return current->previous;
	}
	else
	{
		// Starting at end of list.
		if(index > middle)
		{
			count = items->size;

			while(count > index)
			{
				// Walking through list starting at the end.
				current = current->previous;
				count--;
			}
			return current->value;
		}
		// Starting at the beginning of list.
		else
		{
			count = 0;

			while(count < index)
			{
				// Walking through list starting at the beginning.
				current = current->next;
				count++;
			}

			return current->next->value;
		}
	}
}

/**
 * Function to get the size of a doubly linked list.
 * @param  items [doubly linked list]
 * @return       [int]
 */
int sizeDLL(dll *items)
{
	return items->size;
}

/**
 * Function to display the doubly linked list.
 * @param fp    [where to display the data]
 * @param items [doubly linked list]
 */
void displayDLL(FILE *fp, dll *items)
{
	int count = 0;

	current = items->head;
	fprintf(fp, "[");
	while(count < items->size)
	{
		items->display(fp, current->value);
		count++;
		if(count != items->size)
		{
			fprintf(fp, ",");
		}
		current = current->next;
	}
	fprintf(fp, "]");
}