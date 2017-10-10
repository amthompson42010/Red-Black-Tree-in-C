/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 - Assignment 1 - Reader Header File
 * @description: File that sets up functions for a reader which is defined
 * 				 in reader.c
 */

#ifndef __READER_H__
#define __READER_H__

#include "queue.h"

typedef void (*Reader)(queue*,FILE*);

extern void intReader(queue*,FILE*);
extern void realReader(queue*,FILE *);
extern void stringReader(queue*,FILE*);


#endif
