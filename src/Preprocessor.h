#ifndef Preprocessor_H
#define Preprocessor_H

#include "StringObject.h"
#include "ErrorCode.h"
#include "CException.h"
#include "LinkList.h"
#include "Macro.h"
#include "RedBlackTree.h"
#include "Node.h"
#include "Rotations.h"
#include "InitNode.h"

int searchDirective(String *str, char *directiveName);
Node *searchMacro(String *str);
void testDefine();
#endif // Preprocessor_H
