#ifndef Macro_H
#define Macro_H

#include "StringObject.h"

typedef struct Macro Macro;

struct Macro  {
	String *name;
	String *content;
};

Macro *newMacro(char *macroName, char *macroContent);
void macroDel(Macro *macro);
#endif // Macro_H