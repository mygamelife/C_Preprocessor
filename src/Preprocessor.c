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

  content = stringRemoveWordContaining(string, alphaNumericSet);
  macroContent = stringSubStringInChars(content , content->length);

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

  while(isHashTag(string)) {
    if(isDirective(string, directiveName))  {
      if(isIdentifier(string))  {
        macroNode = macroNodeNew(getMacroInfo(string)); //need to free malloc
        addMacro(&root, macroNode);
      }
    }
  }
  return root;
}

/** findMacro(Node *root, char *targetMacro)
 * This function is use for finding the targetMacro name inside the tree
 *
 ** input :
 *          *root is the pointer pointing to the tree root
 *          *targetMacro is a macro name that we are trying to search in tree
 ** output :
 *          return the macro pointer contain macro information
 *          return NULL if cant the macro name inside the tree
 **/
Macro *findMacro(Node *root, char *targetMacro)  {
  Macro *macro;
  char *macroString;

  if(root != NULL)  {
    macro = (Macro*)root->dataPtr;
    macroString = macro->name->string;

    // printf("findMacro()\n");

    if(strcmp(macroString, targetMacro) == 0) {
      // printf("FOUND Name %s\n", macroString);
      return macro;
    }

    else if(macro->name->string[0] >= targetMacro[0])
      findMacro(root->left, targetMacro);

    else findMacro(root->right, targetMacro);
  }
}

char *replaceMacroInString(String *oriString, String *subString, Macro *macro, int size) {
  int i = 0, j = 0, start = oriString->startindex;
  char *replacedMacroInString = malloc(sizeof(char) * size + 1);

  if(macro != NULL)   {
    for(i; i< size ; i++) {

      replacedMacroInString[i] = oriString->string[start++];

      if(start == subString->startindex) {
        for(j; j< macro->content->length ; j++)  {
          i++;
          replacedMacroInString[i] = macro->content->string[j];
        }
        start += macro->name->length;
      }
      replacedMacroInString[i+1] = '\0';
    }
  }

  else  {
    for(i; i< size ; i++) {
      replacedMacroInString[i] = oriString->string[start++];
      replacedMacroInString[i+1] = '\0';
    }
  }
  puts(replacedMacroInString);
  return replacedMacroInString;
}

void directiveDefine(String *string, char *directiveName) {
  int size;
  char *token, *replacedMacroString;
  String *subString;
  Macro *foundMacro;

  //add all available macro into tree
  Node *root = addAllMacroIntoTree(string, directiveName); /**need free**/

  printf("Before subString string start %d, length %d \n", string->startindex, string->length);

  //store the original string
  String *originalString = stringSubString(string , string->startindex, string->length); /**need free**/
  printf("originalString start %d, length %d \n", originalString->startindex, originalString->length);

  //extract subString for checking macro purpose
  subString = stringRemoveWordContaining(string, alphaSet);

  while(subString->length != 0)  {
    token = stringSubStringInChars(subString , subString->length); /**need free**/
    foundMacro = findMacro(root, token);
    if(foundMacro != NULL)  {
      size = (originalString->length) - (foundMacro->name->length) + (foundMacro->content->length);
      break;
    }
    else  size = originalString->length;
    subString = stringRemoveWordContaining(string, alphaSet);
  }
  puts(token);
  printf("size %d\n", size);
  printf("subString start %d, subString length %d\n", subString->startindex, subString->length);

  //create a temp char array
  //-----------------------------------------------------------------//

  replacedMacroString = replaceMacroInString(originalString, subString, foundMacro, size); /**need free**/

  //-----------------------------------------------------------------//
  printf("After subString string start %d, length %d \n", string->startindex, string->length);

  //free tree memory before exit this function
  destroyAllMacroInTree(root);
}