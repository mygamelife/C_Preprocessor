#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Preprocessor.h"

Node *root = NULL, *macroNode;

/** Find character hashTag at the first position of the string
 * input :
 *			*string is String type pointer
 * output :
 *			return 1 if hashTag found
 *			return 0 if hashTag not found
 **/
int isHashTag(String *string) {

  if(string->string[string->startindex] == '#')
    return 1;

  else return 0;
}

/** Find directive inside the string
 * input :
 *			*string is String type pointer
 *      *directiveName is directive name
 * output :
 *			return 1 if directive name found
 *			return 0 if directive name not found
 **/
int isDirective(String *string, char *directiveName) {
  char *tempString;
  String *directive;

  //remove spaces
  stringTrim(string);

  // if(!isHashTag(string))  {
    // printf("str->string %c", string->string[string->startindex]);
    // Throw(ERR_INVALID_FORMAT);
  // }

  //search for directive
  directive = stringRemoveWordContaining(string, directiveName);
  printf("directive startIndex %d, length %d\n", directive->startindex, directive->length);

  tempString = stringSubStringInChars(directive, directive->length);

  printf("tempString %s\n", tempString);

  if(strcmp(directiveName, tempString) == 0)  {
    subStringDel(tempString);
    return 1;
  }

  else  {
    subStringDel(tempString);
    return 0;
  }
}

/** Looking for identifier
 *
 **Identifier valid format  :
 * -nondigit
 * -identifier nondigit
 * -identifier digit
 *
 * input :
 *			*string is String type pointer
 * output :
 *			return 1 if identifier found
 *			return 0 if identifier not found
 **/
int isIdentifier(String *string)  {
  String *identifier = string;

  stringTrim(identifier);
  printf("Identifier startindex %d, length %d\n", identifier->startindex, identifier->length);

  if(!stringCharAtInSet(identifier, identifier->startindex, numSet))
    return 1;

  else return 0;
}

/** Extract the MacroInfo out from the given string
 * input :
 *			*string is String type pointer
 * output :
 *			return macroInfo contain all the macro information
 *			return NULL if macro information is not found
 **/
Macro *getMacroInfo(String *string) {
  char *macroName, *macroContent;
  String *name, *content;
  Macro *macroInfo;

  name = stringRemoveWordContaining(string, alphaNumericSet);
  macroName = stringSubStringInChars(name , name->length);
  printf("macroName %s\n", macroName);

  content = stringRemoveWordContaining(string, numSet);
  macroContent = stringSubStringInChars(content , content->length);
  printf("macroContent %s\n", macroContent);

  printf("string startindex %d, length %d\n", string->startindex, string->length);
  return macroInfo = newMacro(macroName, macroContent);
}

/** Replace all the words if it is a macro
 * input :
 *			*string is String type pointer
 *      *directiveName is C directive name
 * output :
 *      replace all the predefine words
 **/
void directiveDefine(String *string, char *directiveName) {

  printf("str->startindex %d, str->length %d\n", string->startindex, string->length);

  while(isDirective(string, directiveName)) {
    if(isIdentifier(string))  {
      macroNode = macroNodeNew(getMacroInfo(string));
      addMacro(&root, macroNode);
    }
  }

  // printf("str->startindex %d, str->length %d\n", string->startindex, string->length);
  // setMacroNode(&macroNode, getMacroInfo(string));
  // addMacro(&root, &macroNode);

  Macro *m = (Macro*)root->dataPtr;

  printf("root name %s, content %s\n", m->name->string, m->content->string);

  if(root->left != NULL) {
    Macro *mLeft = (Macro*)root->left->dataPtr;
    printf("left name %s, content %s\n", mLeft->name->string, mLeft->content->string);
  }
  if(root->right != NULL) {
    Macro *mRight = (Macro*)root->right->dataPtr;
    printf("right name %s, content %s\n", mRight->name->string, mRight->content->string);
  }
}
