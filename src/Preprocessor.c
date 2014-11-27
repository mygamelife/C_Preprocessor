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
  // printf("directive startIndex %d, length %d\n", directive->startindex, directive->length);

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
  // printf("Identifier startindex %d, length %d\n", identifier->startindex, identifier->length);

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
  char *macroName, *macroContent, EOL = '\n';
  String *name, *content;
  Macro *macroInfo;
  
  name = stringRemoveWordContaining(string, alphaNumericSet);
  
  if(name->length == 0)
    Throw(ERR_EMPTY_MACRO_NAME);
    
  macroName = stringSubStringInChars(name , name->length);
    
  stringTrimUntilEOL(string);
  
  if(string->string[string->startindex] == EOL) {
    macroContent = malloc(sizeof(char));
    macroContent = "";
    return macroInfo = newMacro(macroName, macroContent); //" " this space indicate it is empty content
  }
    
  content = stringRemoveWordContaining(string, alphaNumericSetWithSymbol);
  printf("content start %d, length %d\n", content->startindex, content->length);
    
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

/** findMacroInTree(Node *root, char *targetMacro)
 * This function is use for finding the targetMacro name inside the tree
 *
 * input :
 *          *root is the pointer pointing to the tree root
 *          *targetMacro is a macro name that we are trying to search in tree
 * output :
 *          return the macro pointer contain macro information if found
 *          return NULL if cant find the macro name inside the tree
 **/
Macro *findMacroInTree(Node *root, char *targetMacro)  {
  Macro *macro;
  char *macroString;

  if(root != NULL)  {
    macro = (Macro*)root->dataPtr;
    macroString = macro->name->string;

    printf("FOUND Name %s\n", macroString);
    // printf("findMacroInTree()\n");

    if(strcmp(macroString, targetMacro) == 0) {
      // printf("FOUND Name %s\n", macroString);
      return macro;
    }

    else if(macro->name->string[0] >= targetMacro[0])
      findMacroInTree(root->left, targetMacro);

    else findMacroInTree(root->right, targetMacro);
  }
}

/** *searchMacroInString(String *str, Node *root)
 * This function is use to search pre-defined macro in string
 *
 ** input :
 *          *str is a pointer pointing to the given string
 *          *root is a pointer pointing to the macro tree
 ** output :
 *          If found return foundMacro pointer contain macro information
 *          Else return NULL
 **/
Macro *searchMacroInString(String *str, Node *root) {
  char *token;
  String *subString;
  Macro *foundMacro;
  
  subString = stringRemoveWordContaining(str, alphaSet);
  printf("subString start %d, subString length %d\n", subString->startindex, subString->length);
  while(subString->length != 0)  {
    printf("subString start %d, subString length %d\n", subString->startindex, subString->length);
    token = stringSubStringInChars(subString , subString->length); /**need free**/
    printf("token %s\n", token);
    foundMacro = findMacroInTree(root, token);
    if(foundMacro != NULL)  {
      printf("foundMacro->string \n");
      break;
    }    
    subString = stringRemoveWordContaining(str, alphaSet);
  }
  return foundMacro;
}

/** *replaceMacroInString(String *oriString, String *subString, Macro *macro, int size)
 * This function is use to replace macro found inside the string
 *
 ** input :
 *          *oriString is a pointer pointing to string statement  (Example : X = A + B)
 *          *subString is a pointer pointing to the macro subString
 *          *macro is a pointer contain macro information
 *          size is the size of string after replaced with macro content
 ** output :
 *          return the character string after replaced macro name with macro content
 **/
char *replaceMacroInString(String *oriString, String *subString, Macro *macro, int size) {
  int i = 0, j = 0, start = oriString->startindex;
  char *replacedMacroInString = malloc(sizeof(char) * size + 1);

  // printf("oriString start %d, length %d\n", oriString->startindex, oriString->length);
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

/** *searchAndReplaceMacroInString(String *str, String *oriString, Node *root)
 * This function is use to search all the macro name in the string and replace with macro content
 * this function will call replaceMacroInString()
 *
 ** input :
 *          *str is a pointer pointing to the given string
 *          *oriString is a pointer pointing to string statement  (Example : X = A + B)
 *          *root is a pointer pointing to the tree, tree contain all the macro information
 ** output :
 *          return String type pointer contain string information after replaced macro name with macro content
 **/
String *searchAndReplaceMacroInString(String *str, Node *root, int *found) {
  int size = 0;
  char *token, *replacedMacroString;
  String *subString, *macroString, *oriString, *tempMacro;
  Macro *foundMacro;
  
  oriString = stringSubString(str , str->startindex, str->length); /**need free**/
  
  subString = stringRemoveWordContaining(str, alphaSet);
  printf("oriString start %d, oriString length %d\n", oriString->startindex, oriString->length);

  while(subString->length != 0)  {
    printf("subString start %d, subString length %d\n", subString->startindex, subString->length);
    token = stringSubStringInChars(subString , subString->length); /**need free**/
    foundMacro = findMacroInTree(root, token);
    if(foundMacro != NULL)  {
      size = (oriString->length) - (foundMacro->name->length) + (foundMacro->content->length);
      break;
    }
    else  size = oriString->length;
    subString = stringRemoveWordContaining(str, alphaSet);
  }
  
  if(foundMacro != NULL)
    *found = 1;
    
  puts(token);
  printf("size %d\n", size);
  printf("subString start %d, subString length %d\n", subString->startindex, subString->length);

  //create a temp char array
  replacedMacroString = replaceMacroInString(oriString, subString, foundMacro, size); /**need free**/
  macroString = stringNew(replacedMacroString);
 
  // if(foundMacro != NULL)
    // tempMacro = searchAndReplaceMacroInString(macroString, root);
  //free tree memory before exit this function
  stringDel(oriString);
  subStringDel(token);
  // subStringDel(replacedMacroString);
  return macroString;
}







String *directiveDefine(String *string, char *directiveName) {
  int size;
  char *token, *replacedMacroString;
  String *subString, *macroString, *originalString;

  //add all available macro into tree
  Node *root = addAllMacroIntoTree(string, directiveName); /**need free**/

  printf("Before subString string start %d, length %d \n", string->startindex, string->length);

  // macroString = searchAndReplaceMacroInString(string, root, foundMacro);

  //free tree memory before exit this function
  destroyAllMacroInTree(root);
  
  return macroString;
}