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
int isIdentifier(String *str);
Macro *createMacroInfo(String *str);
Node *addAllMacroIntoTree(String *string, char *directiveName);
Macro *findMacroInTree(Node *root, char *targetMacro);
char *replaceMacroInString(String *latestString, String *macroSubString, Macro *foundMacro, int size);
char *replaceArgumentsInString(String *str, String *argumentSubString, char *argumentValue, int size);
String *getMacroPositionInString(String *str, Node *root);
String *getArgumentPositionInString(String *str, char *argumentName);
String *directiveDefine(String *str, char *directiveName);
int getSizeOfArgu(String *str, char *containSet);
int getSizeOfArguInString(String *str, char *containSet);
int verifyRedifineArguments(Macro *macro);
Argument *createMacroArguments(String *str, char *containSet);
void storeArgumentsInString(String *str, Macro *macro);
void modifyMacroPositionWithArguments(String *macroSubString, Macro *foundMacro);
char *searchAndReplaceArgumentsInString(char *replacedMacroString, Macro *foundMacro);
#endif // Preprocessor_H

