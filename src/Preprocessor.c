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

  tempString = stringSubStringInChars(directive, directive->length);

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
Macro *createMacroInfo(String *str) {
  char *macroName, *macroContent, EOL = '\n';
  String *name, *content;
  Macro *macroInfo;

  name = stringRemoveWordContaining(str, alphaNumericSet);

  if(name->length == 0)
    Throw(ERR_EMPTY_MACRO_NAME);

  macroName = stringSubStringInChars(name , name->length);

  stringTrimUntilEOL(str);

  if(str->string[str->startindex] == EOL || str->string[str->startindex] == '\0') {
    macroContent = malloc(sizeof(char) * 1);
    macroContent[0] = '\0';
    return macroInfo = newMacro(macroName, macroContent); //" " this space indicate it is empty content
  }

  content = stringRemoveWordContaining(str, alphaNumericSetWithSymbol);

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
        macroNode = macroNodeNew(createMacroInfo(string)); //need to free malloc
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

/** *subStringMacroInString(String *str, Node *root)
 * This function is use to search pre-defined macro in string
 *
 ** input :
 *          *str is a pointer pointing to the given string
 *          *root is a pointer pointing to the macro tree
 ** output :
 *          If found return foundMacro pointer contain macro information
 *          Else return NULL
 **/
String *subStringMacroInString(String *str, Node *root) {
  char *token;
  String *subString;
  Macro *foundMacro;

  subString = stringRemoveWordContaining(str, alphaNumericSet);
  while(subString->length != 0)  {
    token = stringSubStringInChars(subString , subString->length); /**need free**/
    puts(token);
    foundMacro = findMacroInTree(root, token);
    subStringDel(token);
    if(foundMacro != NULL)  {
      break;
    }
    subString = stringRemoveWordContaining(str, alphaNumericSet);
  }
  return subString;
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


String *directiveDefine(String *str, char *directiveName) {
  int size;
  char *macroToken, *replacedMacroString = NULL;
  String *subString, *tempString, *stringStatement;
  Macro *foundMacro;

  //add all available macro into tree
  Node *root = addAllMacroIntoTree(str, directiveName); /**need free**/
  printf("String Statement start %d, length %d \n", str->startindex, str->length);
  stringStatement = stringSubString(str, str->startindex, str->length); /**need free**/
  subString = subStringMacroInString(str, root);
  printf("subString start %d, length %d \n", subString->startindex, subString->length);

  /*--------------------------------------------------------------------------------------*/
  while(subString->length != 0) {
    macroToken = stringSubStringInChars(subString , subString->length); /**need free**/
    foundMacro = findMacroInTree(root, macroToken);

    if(foundMacro != NULL)
      size = (stringStatement->length) - (foundMacro->name->length) + (foundMacro->content->length);
    else  size = stringStatement->length;

    printf("subString start %d, length %d \n", subString->startindex, subString->length);
    replacedMacroString = replaceMacroInString(stringStatement, subString, foundMacro, size); /**need free**/
    
    /*free memory after replaced Macro*/
    stringDel(stringStatement);
    subStringDel(macroToken);
    
    //store the replacedMacroInstring for searching macro in string without modify original stringStatement
    tempString = stringNew(replacedMacroString); /**need free**/

    //Overwrite stringStatement with new replaced macro string
    stringStatement = stringSubString(tempString, tempString->startindex, tempString->length); /**need free**/

    //Overwrite subString with the latest replacedMacroString
    subString = subStringMacroInString(tempString, root);
    // printf("stringStatement start %d, length %d \n", stringStatement->startindex, stringStatement->length);
    // printf("tempString %s\n", tempString->string);
    // printf("tempString start %d, length %d \n", tempString->startindex, tempString->length);
    // printf("subString start %d, length %d \n", subString->startindex, subString->length);
    /*free memory*/
    stringDel(tempString);
  }

  //free tree memory before exit this function
  destroyAllMacroInTree(root);
  return stringStatement;
}