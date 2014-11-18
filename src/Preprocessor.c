#include <stdio.h>
#include <string.h>
#include "Preprocessor.h"

Node *root = NULL;

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

  if(!isHashTag(string))
    Throw(ERR_INVALID_FORMAT);

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

Macro *getMacroInfo(String *string, char *directiveName) {
  char *macroName, *macroContent;
  String *name, *content;
  Macro *macroInfo;

  if(isDirective(string, directiveName))  {
    if(isIdentifier(string))  {
      name = stringRemoveWordContaining(string, alphaNumericSet);
      macroName = stringSubStringInChars(name , name->length);
      printf("macroName %s\n", macroName);

      content = stringRemoveWordContaining(string, numSet);
      macroContent = stringSubStringInChars(content , content->length);
      printf("macroContent %s\n", macroContent);

      printf("string startindex %d, length %d\n", string->startindex, string->length);
      return macroInfo = newMacro(macroName, macroContent);
    }
  }

  else
    return NULL;
}

