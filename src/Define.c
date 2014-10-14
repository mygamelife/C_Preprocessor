#include <stdio.h>
#include <string.h>
#include "Define.h"

int searchDefine(String *str) {
  int hashTag = 0 , found = 1;
  char *strDefine, *define = "define";
  String *stringCheck;
  
  stringTrim(str);
  hashTag = stringCharAtInSet(str , str->startindex, "#");
  
  if(hashTag == found) {
    stringCheck = stringRemoveWordContaining(str, "define");
    strDefine = stringSubStringInChars(stringCheck, stringCheck->length);
    
    if(strcmp(strDefine, define) == 0)  {
      subStringDel(strDefine);
      return 1;
    }
    
    else  {
      subStringDel(strDefine);
      return -1;
    }
  }
    
  else
    Throw(ERROR_INVALID_FORMAT);
}
