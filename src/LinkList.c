#include <malloc.h>
#include "LinkList.h"

LinkList *head = NULL;

LinkList *linkListNew(char *macroName, char *macroValue)  {
  LinkList *newNode;
  
  newNode = malloc(sizeof(LinkList));
  newNode->name = macroName;
  newNode->value = macroValue;
  newNode->next = NULL;
  
  if(head == NULL)
    head = newNode;
    
  else
    head->next = newNode;
    
  return head;
}

void linkListDel(LinkList *linkList)
{
  if(linkList)
    free(linkList);
}