#include <stdio.h>
#include <string.h>
#include "Preprocessor.h"

Node *root = NULL;

int searchDirective(String *str, char *directiveName) {
  int hashTag = 0 , found = 1;
  char *tempString;
  String *directiveCheck;

  stringTrim(str);
  hashTag = stringCharAtInSet(str , str->startindex, "#");

  if(hashTag == found) {
    directiveCheck = stringRemoveWordContaining(str, directiveName);

    tempString = stringSubStringInChars(directiveCheck, directiveCheck->length);

    if(strcmp(tempString, directiveName) == 0)  {
      subStringDel(tempString);
      return 1;
    }

    else  {
      subStringDel(tempString);
      return -1;
    }
  }

  else
    Throw(ERR_INVALID_FORMAT);
}

Node *searchMacro(String *str) {
  Macro *macro;
  void *ptr;
  char *tempName, *tempValue;
  String *removedName, *removedValue; LinkList *link;

  removedName = stringRemoveWordContaining(str , alphaNumericSet);
  tempName = stringSubStringInChars(removedName, removedName->length);
  printf("subString %s\n", tempName);

  removedValue = stringRemoveWordContaining(str , numSet);
  tempValue = stringSubStringInChars(removedValue, removedValue->length);
  printf("subString %s\n", tempValue);

  ptr = newMacro(tempName, tempValue);
  printf("&ptr %p\n", &ptr);
  printf("&macro %p\n", &macro); 
  
  printf("Before &root %p\n", root);
  // if(ptr == NULL)
    // printf("hi\n");
  // macro = (Macro*)root;
  // printf("macro->name %s\n", macro->name->string);
  if(root == NULL)  {
    addRedBlackTree(&root, (Node*)ptr);
    printf("After &root %p\n", root);
    setNode(root, NULL, NULL, 'b');
  }
  else
    addRedBlackTree(&root, (Node*)ptr);
  
  
  // macro = (Macro*)root;
  // printf("macro->name %s\n", macro->name->string);
  
  return root;
}

