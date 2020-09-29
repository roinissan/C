#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "Defs.h"

typedef struct LinkedList *pLinkedList;
typedef struct Node *pNode;

pLinkedList createLinkedList(copyFunction copyFuncElement , equalFunction equalFunc,printFunction printFunc, freeFunction freeFuncElement);
void destroyList(pLinkedList linkedList);
status appendNode(pLinkedList linkedList, Element element);
status deleteNode(pLinkedList linkedList,Element element);
status displayList(pLinkedList linkedList);
Element searchInList(pLinkedList linkedList, Element element);



#endif /* LINKEDLIST_H_ */
