#ifndef Macro_H
#define Macro_H

#include "StringObject.h"
#include "Node.h"

typedef struct Macro Macro;
typedef struct Argument Argument;
typedef struct List List;

struct Macro  {
	String *name;
	String *content;
  Argument *argument;
};

struct List  {
	String *name;
	String *value;
};

struct Argument  {
	int withArgument;
	int size;
	List *entries[0];
};

Macro *newMacro(char *macroName, char *macroContent, Argument *arguList);
Argument *newMacroArgument(int size);
void delMacroArgument(Argument *argu);
void delMacro(Macro *macro);
void delMacroNameAndContent(Macro *macro);
Node *macroNodeNew(Macro *macroInfo);
void delMacroNode(Node *node);
void destroyAllMacroInTree(Node *root);
void delTestMacro(Macro *macro);
#endif // Macro_H

