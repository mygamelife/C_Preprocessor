#include <stdio.h>
#include <string.h>
#include "Preprocessor.h"



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
    Throw(ERROR_INVALID_FORMAT);
}

LinkList *searchMacro(String *str) {
  char *tempName, *tempValue;
  String *removedName, *removedValue; LinkList *link;
  
  removedName = stringRemoveWordContaining(str , alphaNumericSet);
  
  printf("removedName startindex %d\n", removedName->startindex);
  printf("removedName length %d\n", removedName->length);
  
  tempName = stringSubStringInChars(removedName, removedName->length);
  printf("subString %s\n", tempName);
  
  removedValue = stringRemoveWordContaining(str , numSet);
  tempValue = stringSubStringInChars(removedValue, removedValue->length);
  printf("subString %s\n", tempValue);
  
  link = linkListNew(tempName, tempValue);
  printf("link->name %s\n", link->name);
  return link;
}

