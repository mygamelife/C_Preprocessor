#ifndef Macro_H
#define Macro_H

#include "StringObject.h"
#include "Node.h"

typedef struct Macro Macro;

struct Macro  {
	String *name;
	String *content;
};

Macro *newMacro(char *macroName, char *macroContent);
void delMacro(Macro *macro);
void delMacroNameAndContent(Macro *macro);
Node *macroNodeNew(Macro *macroInfo);
void delMacroNode(Node *node);
void destroyAllMacroInTree(Node *root);
void delTestMacro(Macro *macro);
#endif // Macro_H