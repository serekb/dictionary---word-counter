#ifndef TREE_H
#define TREE_H
#include "QFIFO.h"

typedef struct tagTreeItem
{
    char* pWord;
    int Counter;
    FQueue* pFifo;
    tagTreeItem* pLeft;
    tagTreeItem* pRight;
} TreeItem, * LP_TreeItem;

//typedef TreeItem* LP_TreeItem;

void inOrder( TreeItem* pRoot, FILE* fout );

TreeItem* FreeTree3( TreeItem* pRoot );//nulluje wskaznik do drzewa

//BST - binary search tree
//dla ka¿dego wêz³a drzewa na lewo sa mniejsze a na prawo wiêksze
//w inorder lista rosnaca
TreeItem* FindInsert2( TreeItem* pRoot, char* x , int lineNumber );

#endif