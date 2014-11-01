#include <stdio.h>
#include <malloc.h>
#include "Macro.h"

Macro *newMacro(char *macroName, char *macroContent)  {
  Macro *macro = malloc(sizeof(Macro));
  
  macro->name = stringNew(macroName);
  macro->content = stringNew(macroContent);
  
  return macro;
}

void macroDel(Macro *macro) {
  if(macro) {
    stringDel(macro->name);
    stringDel(macro->content);
    free(macro);
  }
}