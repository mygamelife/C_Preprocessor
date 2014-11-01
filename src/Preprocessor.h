#ifndef Preprocessor_H
#define Preprocessor_H

#include "StringObject.h"
#include "ErrorCode.h"
#include "CException.h"
#include "LinkList.h"
#include "Macro.h"

int searchDirective(String *str, char *directiveName);
LinkList *searchMacro(String *str);
void testDefine();
#endif // Preprocessor_H
