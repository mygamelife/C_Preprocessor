#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Preprocessor.h"

/** Find character hashTag at the first position of the string
 * input :
 *			*string is String type pointer
 * output :
 *			return 1 if hashTag found
 *			return 0 if hashTag not found
 **/
int isHashTag(String *string) {

  stringTrim(string);

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
 *			throw ERR_INVALID_DIRECTIVE if directive name not found
 **/
int isDirective(String *string, char *directiveName) {
  char *tempString;
  String *directive;

  //remove spaces
  stringTrim(string);

  //search for directive
  directive = stringRemoveWordContaining(string, directiveName);
  printf("directive startIndex %d, length %d\n", directive->startindex, directive->length);

  tempString = stringSubStringInChars(directive, directive->length);

  if(directive->startindex != 0)
    printf("tempString %s\n", tempString);

  if(strcmp(directiveName, tempString) == 0)  {
    subStringDel(tempString);
    return 1;
  }

  else  {
    subStringDel(tempString);
    Throw(ERR_INVALID_DIRECTIVE);
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
 *			throw ERR_INVALID_IDENTIFIER if identifier not found
 **/
int isIdentifier(String *string)  {
  String *identifier = string;

  stringTrim(identifier);
  printf("Identifier startindex %d, length %d\n", identifier->startindex, identifier->length);

  if(!stringCharAtInSet(identifier, identifier->startindex, numSet))
    return 1;

  else Throw(ERR_INVALID_IDENTIFIER);
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

  content = stringRemoveWordContaining(string, alphaNumericSet);
  macroContent = stringSubStringInChars(content , content->length);
  printf("macroContent %s\n", macroContent);

  printf("string startindex %d, length %d\n", string->startindex, string->length);
  return macroInfo = newMacro(macroName, macroContent); //need to free malloc
}

/** Replace all the words if it is a macro
 * input :
 *			*string is String type pointer
 *      *directiveName is C directive name
 * output :
 *      return the address of root pointer
 **/
Node *addAllMacroIntoTree(String *string, char *directiveName) {
  Node *macroNode, *root = NULL;

  printf("str->startindex %d, str->length %d\n", string->startindex, string->length);

  while(isHashTag(string)) {
    if(isDirective(string, directiveName))  {
      if(isIdentifier(string))  {
        macroNode = macroNodeNew(getMacroInfo(string)); //need to free malloc
        addMacro(&root, macroNode);
      }
    }
  }

  //Debug purpose
  // Macro *m = (Macro*)root->dataPtr;
  // printf("root name %s, content %s\n", m->name->string, m->content->string);

  // if(root->left != NULL) {
    // Macro *mLeft = (Macro*)root->left->dataPtr;
    // printf("left name %s, content %s\n", mLeft->name->string, mLeft->content->string);
  // }
  // else if(root->right != NULL) {
    // Macro *mRight = (Macro*)root->right->dataPtr;
    // printf("right name %s, content %s\n", mRight->name->string, mRight->content->string);
  // }
  //Debug purpose

  return root;
}

Macro *findMacro(Node *root, char *targetMacro)  {
  Macro *macro;
  char *macroString;

  if(root != NULL)  {
    macro = (Macro*)root->dataPtr;
    macroString = macro->name->string;

    printf("findMacro()\n");

    if(strcmp(macroString, targetMacro) == 0) {
      printf("FOUND Name %s\n", macroString);
      return macro;
    }

    else if(macro->name->string[0] >= targetMacro[0])
      findMacro(root->left, targetMacro);

    else findMacro(root->right, targetMacro);
  }
}

void directiveDefine(String *string, char *directiveName) {
  char stringStateMent[50];
  Macro *content;
  
  Node *root = addAllMacroIntoTree(string, directiveName);

  Macro *m = (Macro*)root->dataPtr;
  printf("macro name %s\n", m->name->string);

  stringTrim(string);

  printf("Before subString string start %d, length %d \n", string->startindex, string->length);
  subStringToArray(stringStateMent, string);
  puts(stringStateMent);
  
  
  String *token = stringRemoveWordContaining(string, alphaNumericSet);
  
  while(token->length != 0)  {
    printf("1st token start %d, length %d \n", token->startindex, token->length);
    char *targetToken = stringSubStringInChars(token , token->length);
    printf("targetToken %s\n", targetToken);
    content = findMacro(root, targetToken);
    printf("content String %s\n", content->content->string);
    token = stringRemoveWordContaining(string, alphaNumericSet);
  }
  
  printf("After subString string start %d, length %d \n", string->startindex, string->length);
  // printf("1st token start %d, length %d \n", token->startindex, token->length);
  // targetToken = stringSubStringInChars(token , token->length);
  // printf("targetToken %s\n", targetToken);

  // printf("String %c\n", string->string[string->startindex]);
}