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
Macro *createMacroInfo(String *str);
Node *addAllMacroIntoTree(String *string, char *directiveName);
String *directiveDefine(String *string, char *directiveName);
Macro *findMacroInTree(Node *root, char *targetMacro);
char *replaceMacroInString(String *oriString, String *subString, Macro *macro, int size);
String *subStringMacroInString(String *str, Node *root);
String *searchAndReplaceMacroInString(String *str, Node *root, int *found);
#endif // Preprocessor_H
