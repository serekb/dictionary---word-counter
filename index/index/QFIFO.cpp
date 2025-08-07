#include "QFIFO.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

FQueue* FQCreate()
{
    FQueue* p = (FQueue*)malloc(sizeof(FQItem));
    if( !p ) return NULL;
    p->pHead = p->pTail = NULL;
    return p;
} 
    // queue initiating  (NULL - fail)
int FQEmpty( FQueue* q )
{ 
    return !q || !(q->pHead);
}
// if FIFO empty returned 1 else 0

int FQEnqueue( FQueue* q, int x )
{
    if( !q ) return 0;
    FQItem* p = (FQItem*)malloc( sizeof(FQItem) );
    if( !p ) return 0;
    p->LineNumber = x;
    p->pNext = NULL;
    if( !(q->pHead) )
        q->pHead = p;
    else
        q->pTail->pNext=p;
    q->pTail = p;
    return 1;
}
//zwraca 0 // insert new item at the end

int FQDequeue( FQueue* q )
{
    if( !FQEmpty(q) )
    {
        int val = q->pHead->LineNumber;
        FQDel(q);
        return val;
    }
    return NULL;
}
//zwraca int_min      // take out the first item

void FQClear( FQueue* q ) // sprawdzam czy freemem NULL
{
    if( !q )
    {
        printf("\nERROR: del: queue not exists!!\n");
        return;
    }
    while( !FQEmpty( q ) )
        FQDel( q );
    q->pHead = NULL;
}
// clears the queue

void FQRemove( FQueue** q , void(__cdecl* freeMem) (const void*) )
{
    if( !q || !*q )
    {
        printf("\nERROR: del: queue not exists!!\n");
        return;
    }
  //  FQClear( *q , freeMem );
    free( *q );
    *q = NULL;
}
// clears the queue  (=QFClear()) and removes

void FQDel( FQueue* q )
{
    if( FQEmpty(q) )
    {
        printf("\nERROR: del: queue is empty!!\n");
        return;
    }
    FQItem* p = q->pHead;
    q->pHead = p->pNext;
    if( !(q->pHead) )
        q->pTail = NULL;
    free( p );
}
// removes only first item

void FQPrint( FQueue* q, FILE* fout )//tu zmienialem parametr
{
    if( FQEmpty(q) )
    {
        printf("\nERROR: del: queue is empty!!\n");
        return;
    }
    FQItem* p = q->pHead;
    while( p )
    {
        fprintf( fout, "%d ", p->LineNumber );
        p = p->pNext;
    }
}
