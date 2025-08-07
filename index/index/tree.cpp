#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "QFIFO.h"
#include <string.h>

int compStr( char* s1, char* s2 );

void Visit( TreeItem* pRoot, int lineNumber )
{
    if( !pRoot || !pRoot->pFifo || !pRoot->pWord )
    {
        printf( "Visit function ERROR\n" );
        return;
    }
    pRoot->Counter++;
    if( FQEmpty( pRoot->pFifo ) || pRoot->pFifo->pTail->LineNumber!= lineNumber )
        FQEnqueue( pRoot->pFifo, lineNumber );
}

void inOrder( TreeItem* pRoot , FILE* fout )
{
    if( !pRoot ) return;
    inOrder( pRoot->pLeft, fout );
    fprintf( fout, "Slowo = %20s; Licznik = %2d; Linie: ", pRoot->pWord, pRoot->Counter );
    printf( "Slowo = %20s; Licznik = %2d; Linie: ", pRoot->pWord, pRoot->Counter );
    FQPrint( pRoot->pFifo, fout );
    FQPrint( pRoot->pFifo, stdout );
    printf( "\n" );
    fprintf( fout, "\n" );
    inOrder( pRoot->pRight, fout );
}

TreeItem* FreeTree3( TreeItem* pRoot ) //nulluje wskaznik do drzewa
{
    if( pRoot )
    {
        FreeTree3( pRoot->pLeft );
        FreeTree3( pRoot->pRight );
        free( pRoot );
    }
    return NULL;
}

TreeItem* FindInsert2( TreeItem* pRoot, char* x , int lineNumber )
{
    if( !pRoot )
    {
        TreeItem* v = (TreeItem*)calloc( 1, sizeof(TreeItem) );
        if( !v )
        {
            printf( "Allocation ERROR\n" );
            return NULL;
        }
        v->pFifo = FQCreate();
        if( !(v->pFifo) )
        {
            free( v );
            printf( "Fifo creation ERROR\n" );
            return NULL;
        }
        FQEnqueue( v->pFifo, lineNumber );
        v->pWord = x;
        v->Counter = 1;
        //  (*pRoot)->pLeft = (*pRoot)->pRight = NULL; mamy calloca wiêc nie trzeba
        return v;
    }
    if( compStr( x, pRoot->pWord ) == INT_MIN )
    {
        printf("Memory allocation ERROR in CompStr\n");
        return NULL;
    }
    if( compStr( x,  pRoot->pWord ) < 0 )
        pRoot->pLeft = FindInsert2( pRoot->pLeft, x , lineNumber );
    else if( compStr( x, pRoot->pWord ) > 0 )
        pRoot->pRight = FindInsert2( pRoot->pRight, x , lineNumber );
    else Visit( pRoot, lineNumber );
    return pRoot;
}

int compStr( char* s1, char* s2 )
{
    if( !s1 || !s2 )
        return 1;
    char* str1 = (char*)calloc( strlen( s1 ) + 1, sizeof(char) );
    char* str2 = (char*)calloc( strlen( s2 ) + 1, sizeof(char) );
    if( !str1 )
    {
        free( str2 );
        return INT_MIN;
    }
    if( !str2 )
    {
        free( str1 );
        return INT_MIN;
    }
    strcpy( str1, s1 );
    strcpy( str2, s2 );
    str1 = _strlwr( str1 );
    str2 = _strlwr( str2 );
    int res = strcmp( str1, str2 );
    free( str1 );
    free( str2 );
    return res;
}