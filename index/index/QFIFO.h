#ifndef QFIFO_H
#define QFIFO_H
#include <stdio.h>
#include <stdlib.h>

typedef struct tagFQItem
{
    int LineNumber;
    tagFQItem* pNext;
} FQItem;   //FIFO Queue Item

typedef struct
{
    FQItem* pHead;  // ptr to the first queue item
    FQItem* pTail;  // ptr to the last queue item
} FQueue;  /// typ kolejkowy

FQueue* FQCreate();                  // queue initiating  (NULL - fail)
int     FQEmpty( FQueue* q );          // if FIFO empty returned 1 else 0
int     FQEnqueue( FQueue* q, int x ); // insert new item at the end //zwraca 0
int     FQDequeue( FQueue* q );        // take out the first item    //zwraca int_min  
//void    FQClear( FQueue* q, void (__cdecl* freeMem) (const void*) );          // clears the queue
void    FQRemove( FQueue** q, void (__cdecl* freeMem) (const void*) );        // clears the queue  (=QFClear()) and removes
void    FQDel( FQueue* q );            // removes only first item

void FQPrint( FQueue* q, FILE* fout );//drukuje cala kolejke

#endif 