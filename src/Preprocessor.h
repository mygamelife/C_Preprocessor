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
#include "LinkedList.h"

int isDirective(String *string, char *directiveName);
int isHashTag(String *string);
int isIdentifier(String *string);
Macro *createMacroInfo(String *str);
Node *addAllMacroIntoTree(String *string, char *directiveName);
Macro *findMacroInTree(Node *root, char *targetMacro);
char *replaceMacroInString(String *latestString, String *macroSubString, Macro *foundMacro, int size);
String *macroPositionInString(String *str, Node *root);
String *directiveDefine(String *str, char *directiveName);
int getSizeOfArgu(String *str, char *containSet);
int getSizeOfArguInString(String *str, char *containSet);
Argument *createMacroArguments(String *str, char *containSet);
Argument *createNonIdentifierArgumentsInString(String *str, char *containSet);
#endif // Preprocessor_H
