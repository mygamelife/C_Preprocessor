#ifndef Preprocessor_H
#define Preprocessor_H

#include "StringObject.h"
#include "ErrorCode.h"
#include "CException.h"
#include "Macro.h"
#include "RedBlackTree.h"
#include "Node.h"
#include "Rotations.h"
#include "InitNode.h"

int isDirective(String *string, char *directiveName);
int isHashTag(String *string);
int isIdentifier(String *string);
Macro *getMacroInfo(String *string);
Node *addAllMacroIntoTree(String *string, char *directiveName);
void directiveDefine(String *string, char *directiveName);
Macro *findMacro(Node *root, char *targetMacro);
void replaceMacroInString(char stringArry[], String *originalString, int originalStringStart, int size, int macroAt, Macro *macro);
#endif // Preprocessor_H
