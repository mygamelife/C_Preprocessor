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

  if(stringCharAtInSet(identifier, identifier->startindex, alphaSet))
    return 1;

  else Throw(ERR_INVALID_IDENTIFIER);
}

/** Create *createMacroArguments(String *str)
 * input :
 *			*string is a given String
 * output :
 *			return macroArgument if bracket "()" is found
 *			else return NULL
 **/
Argument *createMacroArguments(String *str) {
  int size = 0, iden = 0;
  char *macroArgument;
  String *arguments, *argu;

  stringTrim(str);
  printf("str startindex %d, length %d\n", str->startindex, str->length);
  arguments = stringRemoveWordContaining(str, alphaNumericSetWithBracket);

  macroArgument = stringSubStringInChars(arguments, arguments->length);
  argu = stringNew(macroArgument);

  printf("argu string %s\n", argu->string);
  printf("argu startindex %d, length %d\n", argu->startindex, argu->length);

  if(argu->string[argu->startindex++] == '(')
    iden = isIdentifier(argu);

  arguments = stringRemoveWordContaining(argu, alphaNumericSet);
  printf("arguments startindex %d, length %d\n", arguments->startindex, arguments->length);
  printf("argu startindex %d, length %d\n", argu->startindex, argu->length);
  
  if(argu->string[argu->startindex++] == '(') {
    if(arguments->length)
      size++;
  }
  stringDel(arguments);
  return NULL;
}

/** Extract the MacroInfo out from the given string
 * input :
 *			*string is String type pointer
 * output :
 *			return macroInfo contain all the macro information
 *			return NULL if macro information is not found
 **/
Macro *createMacroInfo(String *str) {
  char *macroName, *macroContent, *macroContentPart, *macroArguments, EOL = '\n';
  String *name, *content;
  Macro *macroInfo;

  name = stringRemoveWordContaining(str, alphaNumericSetWithBracket);

  if(name->length == 0) //Throw error name is empty
    Throw(ERR_EMPTY_MACRO_NAME);

  macroName = stringSubStringInChars(name , name->length);
  // macroArguments = createMacroArguments(str);

  /*------------------------------------------------------------------------------*/
  stringTrimUntilEOL(str);

  if(str->string[str->startindex] == EOL || str->string[str->startindex] == '\0') {
    macroContent = malloc(sizeof(char) * 1);
    macroContent[0] = '\0';
    return macroInfo = newMacro(macroName, macroContent); //" " this space indicate it is empty content
  }
  content = stringRemoveWordContaining(str, alphaNumericSetWithSymbol);
  macroContent = stringSubStringInChars(content , content->length);
  // printf("macroContent %s\n", macroContent);

  if(str->string[str->startindex] == '\\')  {
    // printf("found backslash\n");
    content = stringRemoveWordContaining(str, alphaNumericSetWithSymbol);
    macroContentPart = stringSubStringInChars(content , content->length);
    // printf("macroContentPart %s\n", macroContentPart);
    strcat(macroContent, macroContentPart);
  }
  
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
  Macro *macro, *foundMacro;

  while(isHashTag(string)) {
    if(isDirective(string, directiveName))  {
      if(isIdentifier(string))  {
        macro = createMacroInfo(string);
        foundMacro = findMacroInTree(root, macro->name->string);
        if(foundMacro != NULL)  { //check redefined macro
          printf("Warning %s redefined\n", macro->name->string);
          Throw(ERR_MACRO_REDEFINED);
        }
        macroNode = macroNodeNew(macro); //need to free malloc
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
    token = stringSubStringInChars(subString , subString->length);
    foundMacro = findMacroInTree(root, token);

    if(foundMacro != NULL)  {
      break;
    }
    stringDel(subString);
    subStringDel(token);
    // printf("subString start %d, length %d\n", subString->startindex, subString->length);
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
char *replaceMacroInString(char *latestString, String *subString, Macro *foundMacro, int size) {
  int i = 0, j = 0, start = 0;
  char *replacedMacroInString = malloc(sizeof(char) * size + 1);

  // printf("latestString %s\n", latestString);
  // printf("subString start %d, length %d\n", subString->startindex, subString->length);

  if(foundMacro != NULL)   {
    for(i; i< size ; i++) {

      if(start == subString->startindex) {
        for(j; j< strlen(foundMacro->content->string) ; j++)  {
          replacedMacroInString[i] = foundMacro->content->string[j];
          i++;
        }
        start += foundMacro->name->length;
      }
      replacedMacroInString[i] = latestString[start++];
    }
    replacedMacroInString[i] = '\0';
  }

  else  {
    for(i; i< size ; i++) {
      replacedMacroInString[i] = latestString[start++];
    }
    replacedMacroInString[i] = '\0';
  }
  puts(replacedMacroInString);
  return replacedMacroInString;
}

/** String *directiveDefine(String *str, char *directiveName)
 * This function is
 *
 ** input :
 ** output :
 **/
String *directiveDefine(String *str, char *directiveName) {
  int size, count = 0, Cyclic = 0, nextToCyclic = 0;
  char *macroToken, *stringStatement, *replacedMacroString = NULL;
  String *macro, *latestString;
  Macro *foundMacro;
  LinkedList *head = NULL;

  Node *root = addAllMacroIntoTree(str, directiveName); //add all predefined macro into tree

  stringStatement = stringSubStringInChars(str, str->length); //extract string statement
  latestString = stringNew(stringStatement);

  // printf("latestString %s \n", latestString->string);
  // printf("latestString start %d, length %d \n", latestString->startindex, latestString->length);

  macro = macroPositionInString(latestString, root); //detect predefined macro in string and return the macro location
  // printf("macro start %d, length %d \n", macro->startindex, macro->length);

  /*--------------------------------------------------------------------------------------*/
  while(macro->length != 0) {

    macroToken = stringSubStringInChars(macro, macro->length); //extract the macro as a token
    foundMacro = findMacroInTree(root, macroToken);

    // printf("macro start %d, length %d \n", macro->startindex, macro->length);
    if(foundMacro != NULL)  {
      size = strlen(latestString->string) - (foundMacro->name->length) + (foundMacro->content->length);

      Cyclic = findList(&head, foundMacro->name->string);

      if(Cyclic)  { //if Cyclic happen destroy previous list and store location after cyclic problem
        // printf("Cyclic Happen at %s\n", macroToken);
        // printf("latestString start %d, length %d \n", latestString->startindex, latestString->length);
        nextToCyclic = latestString->startindex;
        destroyAllLinkedLists(head); //free the old list
        head = NULL;
      }

      else  {
        LinkedList *newList = linkListNew(foundMacro->name->string); //Create new list
        addLinkedList(&head, newList);
        // if(head != NULL)
          // printf("Created new list for %s\n", foundMacro->name->string);
      }
    }
    else  size = strlen(latestString->string);

    // printf("size %d\n", size);
    // printf("Strlen %d\n", strlen(latestString->string));


    if(!Cyclic) {
      /* free malloc memory */
      subStringDel(replacedMacroString);
      // printf("foundMacro->name->string %s\n", foundMacro->name->string);
      // printf("foundMacro->content->string %s\n", foundMacro->content->string);
      replacedMacroString = replaceMacroInString(stringStatement, macro, foundMacro, size); /**need free**/

      /* free malloc memory */
      stringDel(latestString);
      latestString = stringNew(replacedMacroString); //Overwrite previous string with latest replaced macro string

      /* free malloc memory */
      subStringDel(stringStatement);
      stringStatement = stringSubStringInChars(latestString, latestString->length); //extract the latest string statement
    }

    // printf("latestString start %d, length %d \n", latestString->startindex, latestString->length);
    // printf("stringStatement %s \n", stringStatement);

    if(nextToCyclic)  //always start at next to cyclic happen
      latestString->startindex = nextToCyclic;
    /* free malloc memory */
    stringDel(macro);
    macro = macroPositionInString(latestString, root); //continue search macro in string

    // printf("macro start %d, length %d \n", macro->startindex, macro->length);
    // printf("latestString->string %c\n", latestString->string[latestString->startindex]);
    // printf("nextToCyclic start %d, length %d \n", latestString->startindex, latestString->length);
    /* free malloc memory */
    subStringDel(macroToken);
  }

  /* free tree memory before exit this function */
  stringDel(macro);
  subStringDel(stringStatement);
  destroyAllLinkedLists(head);
  destroyAllMacroInTree(root);

  latestString->startindex = 0;
  latestString->length = strlen(latestString->string);
  return latestString;
}