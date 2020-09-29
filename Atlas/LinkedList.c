#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "KeyValuePair.h"



struct LinkedList {

    pNode head;
    copyFunction copyElement;
    freeFunction freeElement;
    equalFunction equalf;
    printFunction printf;

    int numOfElements;

};

struct Node{

    Element data;
    pNode next;

};

// function to create generel Linked list - acting as constructor
pLinkedList createLinkedList(copyFunction copyFuncElement , equalFunction equalFunc,printFunction printFunc, freeFunction freeFuncElement){

    pLinkedList newList = (pLinkedList)malloc(sizeof(struct LinkedList));
    if(!newList)
        return NULL;
    newList->copyElement = (Element)copyFuncElement;
    newList->freeElement = (Element)freeFuncElement;
    newList->equalf = (Element)equalFunc;
    newList->printf = (Element)printFunc;
    newList->numOfElements = 0;
    return newList;

}

// function to free Linked list using the free functions of the struct
void destroyList(pLinkedList linkedList){
    if(linkedList!=NULL){
        int numCurrElements = linkedList->numOfElements;
        if(numCurrElements == 1){
            linkedList->freeElement(linkedList->head->data);
            free(linkedList->head);
            linkedList->head = NULL;
        }
        else{
            pNode curr = linkedList->head;
            pNode prev =NULL;
            while(curr!=NULL){
                prev = curr;
                linkedList->freeElement(curr->data);
                curr = curr->next;
                free(prev);
            }
        }
        free(linkedList);
        linkedList=NULL;
    }
}

// function to add a new node to the linked list using new allocation in memory
status appendNode(pLinkedList linkedList,Element element){
    if(element==NULL || linkedList == NULL)
        return failure;
    if(linkedList->numOfElements == 0){
        linkedList->head = (pNode)malloc(sizeof(struct Node));
        if(!linkedList->head)
            return failure;
        linkedList->head->data = linkedList->copyElement(element);
		linkedList->freeElement(element);
        linkedList->head->next = NULL;
        linkedList->numOfElements++;

    }

    else{
        pNode current_node = linkedList->head;
        while( current_node->next != NULL){
            current_node = current_node->next;
        }

        current_node->next = (pNode)malloc(sizeof(struct Node));
        if(!current_node->next)
            return failure;

        current_node->next->data = linkedList->copyElement(element);
		linkedList->freeElement(element);
        current_node->next->next = NULL;
        linkedList->numOfElements++;
    }
    return success;
}


// function to delete one node from the linked list - updating the pointer of the precious and next node accordingly
// using the free function of the struct
status deleteNode(pLinkedList linkedList,Element element){

    if(element==NULL || linkedList==NULL)
        return failure;
    pNode curr = linkedList->head;
    pNode prev = NULL;
    while(curr!=NULL && linkedList->equalf(curr->data,element)==false){
        prev = curr;
        curr = curr->next;
    }
    if(curr==NULL)
        return failure;
    if(prev == NULL){
        if(linkedList->numOfElements == 1)
            linkedList->head = NULL;
        else
            linkedList->head = curr->next;
    }
    else
        prev->next = curr->next;
    linkedList->freeElement(curr->data);
    free(curr);
    linkedList->numOfElements = linkedList->numOfElements -1;
    curr=NULL;
    return success;
}


// function to print the list - using the print fucntion of the struct
status displayList(pLinkedList linkedList){
    if(linkedList==NULL)
        return failure;
    pNode curr = linkedList->head;
    while(curr!=NULL){
        linkedList->printf(curr->data);
        curr = curr->next;
    }
    return success;

}

// function to find an element in the linked list - using the equal function in the struct
Element searchInList(pLinkedList linkedList, Element element){

    if(element==NULL || linkedList==NULL)
        return NULL;
    pNode curr = linkedList->head;
    while(curr!=NULL && !linkedList->equalf(curr->data,element)){
        curr = curr->next;
    }
    if(curr==NULL)
        return NULL;
    return curr->data;
}



