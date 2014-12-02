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
    stringDel(directive);
    return 1;
  }

  else  {
    subStringDel(tempString);
    stringDel(directive);
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

    // printf("FOUND Name %s\n", macroString);
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

/** *macroPositionInString(String *str, Node *root)
 * This function is use to search pre-defined macro in string
 *
 ** input :
 *          *str is a pointer pointing to the given string
 *          *root is a pointer pointing to the macro tree
 ** output :
 *          If found return foundMacro pointer contain macro information
 *          Else return NULL
 **/
String *macroPositionInString(String *str, Node *root) {
  char *token;
  String *subString;
  Macro *foundMacro;

  subString = stringRemoveWordContaining(str, alphaNumericSet);
  while(subString->length != 0)  {
    token = stringSubStringInChars(subString , subString->length); /**need free**/
    foundMacro = findMacroInTree(root, token);

    if(foundMacro != NULL)  {
      break;
    }
    // stringDel(subString);
    subStringDel(token);
    
    subString = stringRemoveWordContaining(str, alphaNumericSet);
  }
  return subString;
}

/** *replaceMacroInString(String *oriString, String *subString, Macro *macro, int size)
 * This function is use to replace macro found inside the string
 *
 ** input :
 *          *latestString is a pointer pointing to latest update string statement
 *          *subString is a pointer pointing to the macro subString
 *          *macro is a pointer contain macro information
 *          size is the size of string after replaced with macro content
 ** output :
 *          return the character string after replaced macro name with macro content
 **/
char *replaceMacroInString(char *latestString, String *subString, Macro *macro, int size) {
  int i = 0, j = 0, start = 0;
  char *replacedMacroInString = malloc(sizeof(char) * size + 1);

  printf("latestString %s\n", latestString);
  printf("subString start %d, length %d\n", subString->startindex, subString->length);
  if(macro != NULL)   {
    for(i; i< size ; i++) {

      replacedMacroInString[i] = latestString[start++];

      if(start == subString->startindex) {
        for(j; j< macro->content->length ; j++)  {
          i++;
          replacedMacroInString[i] = macro->content->string[j];
        }
        start += macro->name->length;
      }
      replacedMacroInString[i+1] = 0;
    }
  }

  else  {
    for(i; i< size ; i++) {
      replacedMacroInString[i] = latestString[start++];
      replacedMacroInString[i+1] = 0;
    }
  }
  puts(replacedMacroInString);
  return replacedMacroInString;
}


String *directiveDefine(String *str, char *directiveName) {
  int size, count = 0, Cyclic = 0;
  char *macroToken, *stringStatement, *replacedMacroString = NULL;
  String *macro, *latestString;
  Macro *foundMacro;
  LinkedList *head = NULL;

  Node *root = addAllMacroIntoTree(str, directiveName); //add all predefined macro into tree

  stringStatement = stringSubStringInChars(str, str->length); //extract string statement
  latestString = stringNew(stringStatement);
  
  printf("latestString start %d, length %d \n", latestString->startindex, latestString->length);

  macro = macroPositionInString(latestString, root); //detect predefined macro in string and return the macro location
  printf("macro start %d, length %d \n", macro->startindex, macro->length);

  /*--------------------------------------------------------------------------------------*/
  while(macro->length != 0) {
    
    macroToken = stringSubStringInChars(macro, macro->length); //extract the macro as a token
    // if(findList(&head, macroToken))  {
      // printf("subString->string %s\n", subString->string);
      // printf("Cyclic Happen\n");
      // break;
    // }
    foundMacro = findMacroInTree(root, macroToken); 

    // if(foundMacro != NULL)  {
      // if(findList(&head, foundMacro->name->string)) {
        // printf("Cyclic\n");
        // subString->length = 0;
        // Cyclic = 1;
      // }
      // else  {
        // LinkedList *newList = linkListNew(foundMacro->name->string);
        // addLinkedList(&head, newList);

        // char *stringChar = (char*)head->data;
        // printf("newList %s\n", stringChar);

        // if(head->next != NULL)
          // printf("head next not null\n");

      // }
    // }
    printf("macro start %d, length %d \n", macro->startindex, macro->length);
    if(foundMacro != NULL)  {
      size = strlen(latestString->string) - (foundMacro->name->length) + (foundMacro->content->length);
      LinkedList *newList = linkListNew(foundMacro->name->string);
      addLinkedList(&head, newList);

      printf("Created new list for %s\n", foundMacro->name->string);
    }
    else  size = strlen(latestString->string);

    printf("size %d \n", size);
    // printf("2nd subString start %d, length %d \n", subString->startindex, subString->length);

    // printf("stringStatement string %s \n", stringStatement->string);
    // printf("stringStatement start %d, length %d \n", stringStatement->startindex, stringStatement->length);
    // printf("foundMacro name %s, content %s \n", foundMacro->name->string, foundMacro->content->string);
    

    /* free malloc memory */
    subStringDel(replacedMacroString);
    replacedMacroString = replaceMacroInString(stringStatement, macro, foundMacro, size); /**need free**/

    /* free malloc memory */
    stringDel(latestString);
    latestString = stringNew(replacedMacroString); //Overwrite previous string with latest replaced macro string
    
    /* free malloc memory */
    subStringDel(stringStatement);
    stringStatement = stringSubStringInChars(latestString, latestString->length); //extract the latest string statement
    
    printf("latestString start %d, length %d \n", latestString->startindex, latestString->length);
    printf("stringStatement %s \n", stringStatement);
    // store the replacedMacroInstring for searching macro in string without modify original stringStatement
    // stringDel(latestString);
    // latestString = stringNew(replacedMacroString); /**need free**/

    // Overwrite stringStatement with new replaced macro string
    // stringDel(stringStatement);
    // stringStatement = stringSubString(latestString, latestString->startindex, latestString->length); /**need free**/

    
    /* free malloc memory */
    stringDel(macro);
    macro = macroPositionInString(latestString, root); //continue search macro in string
    
    printf("macro start %d, length %d \n", macro->startindex, macro->length);
    
    
    
    
    
    /* free malloc memory */
    subStringDel(macroToken);
  }

  //free tree memory before exit this function
  destroyAllMacroInTree(root);
  latestString->startindex = 0;
  latestString->length = strlen(latestString->string);
  return latestString;
}