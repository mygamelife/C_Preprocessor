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
String *directiveDefine(String *string, char *directiveName);
Macro *findMacroInTree(Node *root, char *targetMacro);
char *replaceMacroInString(String *oriString, String *subString, Macro *macro, int size);
String *searchAndReplaceMacroInString(String *str, String *oriString, Node *root);
#endif // Preprocessor_H
