#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "QFIFO.h"
#include <string.h>

#define PARAMNO 3
int ReadData( char* sFile , TreeItem** pRoot );
int SaveToFile( char* sFile, TreeItem* pRoot );
int isIdentifier( char c );
int isLetter( char c );

int main( int argc, char* argv[] )
{
    if( argc != PARAMNO )
    {
        printf( "WRONG NUMBER OF INPUT PARAMETERS\n" );
        return 1;
    }
    TreeItem* pRoot = NULL;
    if( !ReadData( argv[1], &pRoot ) )
    {
        printf( "Reading data ERROR\n" );
        return 2;
    }
    if( !SaveToFile( argv[2], pRoot ) ) {
        printf( "Writing data ERROR\n" );
        return 3;
    }
    FreeTree3( pRoot );
    return 0;
}

int ReadData( char* sFile , TreeItem** pRoot )
{
    FILE* fin = NULL;
    if( ( fin = fopen( sFile, "r" ) ) == NULL )
    {
        printf( "Error open input file %s\n", sFile );
        return 0;
    }
    char* word = (char*)calloc( 41, sizeof(char) );// allokacja w pêtli
    char c;
    int lineNumber = 1;
    while( (c = fgetc(fin)) != EOF ) 
    {
        int i = 0;
        if( isIdentifier( c ) )
        {
            while( isLetter(c) && i<40 )//pomijanie
            {
                word[i] = c;
                c = fgetc( fin );
                i++;
            }
            word[i]=0;
            char* wordcpy = (char*)calloc( 41, sizeof(char) );
            strcpy( wordcpy, word );
            *pRoot = FindInsert2( *pRoot, wordcpy , lineNumber );
            if( !*pRoot )
            {
                printf( "FindInsert ERROR\n" );
                return 0;
            }
        }
        if( c == '\n' ) lineNumber++;
    }
    fclose( fin );
    return 1;
}
int SaveToFile( char* sFile, TreeItem* pRoot ) 
{
    FILE* fout = NULL;
    if( (fout = fopen(sFile, "w")) == NULL)
    {
        printf( "Result file ERROR\n" );
        return 0;
    }

    if( !pRoot )
    {
        printf( "Tree is empty\n" );
        fclose( fout );
        return 0;
    }
    inOrder( pRoot, fout );
    fclose( fout );
    return 1;
}
//nalezy napisac wlasna funkcje porownujaca
//int compStr(char* s1, char* s2); nie zwraca uwagi na wielkosc liter
//lancuchy znakowe bo ma byc niezalezne od duzych i malych liter

int isIdentifier( char c )
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_') );
}

int isLetter( char c )
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_') || (c >= '0' && c<= '9') );
}