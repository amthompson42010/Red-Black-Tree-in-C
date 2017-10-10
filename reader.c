/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 - Assignment 1 - Reader File
 * @description: File with functions to read a file based of
 *               the types in the file.
 */

#include "reader.h"
#include "scanner.h"
#include "integer.h"
#include "real.h"
#include "string.h"

/**
 * Function to read Integers.
 * @param fp [file that is passed in]
 * @param q  [queue that is passed in]
 */
void intReader(queue *q, FILE *fp) {
     // readInt() is in scanner.c
     int x = readInt(fp);
     while(!feof(fp)) {
          enqueue(q, newInteger(x));
          x = readInt(fp);
     }
}

/**
 * Function to read Real numbers
 * @param fp [file that is passed in]
 * @param q  [queue that is passed in]
 */
void realReader(queue  *q, FILE *fp) {
     // readReal() is in scanner.c
     double x = readReal(fp);
     while(!feof(fp)) {
          enqueue(q, newReal(x));
          x = readReal(fp);
     }
}

/**
 * Function to read strings
 * @param fp [file that is passed in]
 * @param q  [queue that is passed in]
 */
void stringReader(queue *q, FILE *fp) {
     // readString() is in scanner.c
     char *x = readString(fp);
     while(!feof(fp)) {
          enqueue(q, newString(x));
          x = readString(fp);
     }
}
