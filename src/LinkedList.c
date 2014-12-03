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

  if(firstList == NULL)
    return;

  else if(firstList->next != NULL)
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

  tail = head;

  while(tail->next != NULL)
    tail = tail->next;

    tail->next = newList;
}

/** compareChar 2 String type character
 * input :
 *			**rootPtr is a void pointer pointing to the root
 *      *newNode is a void pointer pointing to the newNode
 * output :
 *			return 1 if root == newNode
 *			return 0 root != newNode
 **/
int compareChar(void *dataInCollection, void *targetData)  {
  //type cast void pointer to Node type
  char *data1 = (char*)dataInCollection;
  char *data2 = (char*)targetData;

  puts(data1);
  //data1 is equal with data2
  if(strcmp(data1, data2) == 0)
    return 1;

  else return 0;
}

/** addLinkedList add newList into LinkedList
 *  input :
 *          **listPtr is the pointer pointing to head pointer address
 *          *newList is the pointer pointing to the new created list
 *  output  :
 *            newList should contain in the LinkList->next;
 **/
int findLinkedList(LinkedList **listPtr, void *data, int(*compareChar)(void *dataInCollection, void *data))  {
  LinkedList *head = *listPtr;
  int result;

  while(head != NULL) {
    if(compareChar(head->data, data))
      return 1;

    else
      head = head->next;
  }

  return 0;
}