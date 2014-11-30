#include <stdio.h>
#include <malloc.h>
#include "LinkedList.h"

/** Create new list for linkList
 *  input :
 *          *data is a void data type
 *  output  :
 *            return linkList pointer and contain new list
 **/
LinkedList *linkListNew(void *data) {
  LinkedList *link = malloc(sizeof(LinkedList));

  link->next = NULL;
  link->data = data;

  return link;
}

/** Destroy(free) all list in LinkedList
 *  input :
 *          *firstList is the pointer pointing to the first list in LinkedList
 *  output  :
 *            free all malloc memory in LinkedList
 **/
void destroyAllLinkedLists(LinkedList *firstList)  {

  if(firstList->next != NULL)
    destroyAllLinkedLists(firstList->next);

  free(firstList);
}

/** addLinkedList add newList into LinkedList
 *  input :
 *          **listPtr is the pointer pointing to head pointer address
 *          *newList is the pointer pointing to the new created list
 *  output  :
 *            newList should contain in the LinkList->next;
 **/
void addLinkedList(LinkedList **listPtr, LinkedList *newList) {
  LinkedList *head = *listPtr, *tail;

  if(head == NULL)  {
    *listPtr  = newList;
    return;
  }

  if(head->next == NULL)
    printf("head->next NULL\n");
    
  tail = head;
  
  while(tail->next != NULL) {
    printf("hihi\n");
    tail = tail->next;
  }
    
    tail->next = newList;
  
  

  // tail = newList;
  // char *charPtr = (char*)head->data;
  // puts(charPtr);
}