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
  if(stringCharAtInSet(identifier, identifier->startindex, alphaSet))
    return 1;

  else Throw(ERR_INVALID_IDENTIFIER);
}

/** getSizeOfArgu(String *str, char *containSet)
 *  This function is used to determine how many argument that macro content had
 * input :
 *			*str is the macro arugment list in string form
 *      *containSet only take identifier as arguments
 * output :
 *			return sizeOfArgu if found
 *      else return 0
 **/
int getSizeOfArgu(String *str, char *containSet) {
  int sizeOfMacro = 0;
  String *arguments;

  if(str->string[str->startindex] == ')')
    return sizeOfMacro;

  do  {
    arguments = stringRemoveWordContaining(str, containSet); /**need free**/
    // printf("argument start %d, length %d\n", arguments->startindex, arguments->length);
    // printf("str start %d, length %d\n", str->startindex, str->length);
    if(arguments->length == 0)  {
      stringDel(arguments);
      break;
    }
    else if(isIdentifier(arguments)) {
      // printf("valid argument\n");
      sizeOfMacro++;
    }
    stringTrim(str);
    stringDel(arguments);
  }while(str->string[str->startindex] == ',');

  return sizeOfMacro;
}

/** getSizeOfArguInString(String *str, char *containSet)
 *  This function is used to determine how many argument in string statement
 * input :
 *			*str is the macro arugment list in string form
 *      *containSet only take identifier as arguments
 * output :
 *			return sizeOfArgu if found
 *      else return 0
 **/
int getSizeOfArguInString(String *str, char *containSet) {
  int sizeOfMacro = 0;
  String *arguments;

  do  {
    stringTrim(str);
    arguments = stringRemoveWordContaining(str, containSet);
    // printf("argument start %d, length %d\n", arguments->startindex, arguments->length);
    // printf("str start %d, length %d\n", str->startindex, str->length);
    if(arguments->length == 0)  {
      stringDel(arguments);
      break;
    }
    sizeOfMacro++;

    /* free before re-use */
    stringTrim(str);
    stringDel(arguments);
  }while(str->string[str->startindex] == ',');

  return sizeOfMacro;
}

/** *createMacroArguments(String *str)
 * input :
 *			*string is a given String
 * output :
 *			return macroArgument if bracket "()" is found
 *			else return NULL
 **/
Argument *createMacroArguments(String *str, char *containSet) {
  int sizeOfArgu = 0, i = 0, start = 0, end = 0;
  char *macroArgument;
  String *arguments;
  Argument *argu;

  printf("str->string[str->startindex] %c\n", str->string[str->startindex]);
  if(str->string[str->startindex] == '(') {
    printf("Open bracket found\n");
    str->startindex++;
    start = str->startindex;
    // printf("argument start %d, length %d\n", arguments->startindex, arguments->length);
    printf("str start %d, length %d\n", str->startindex, str->length);

    sizeOfArgu = getSizeOfArgu(str, containSet);
    // printf("sizeOfArgu %d\n", sizeOfArgu);
    // printf("str start %d, length %d\n", str->startindex, str->length);

    if(str->string[str->startindex] == ')') {
      printf("Closed bracket found\n");
      /* reset string position to initial */
      end = str->startindex;
      str->startindex = start;
      str->length = strlen(str->string);

      argu = newMacroArgument(sizeOfArgu);
      if(sizeOfArgu == 0) {
        if(str->string[end] == ')')
          str->startindex++;
        argu->withArgument = 1;
        return argu;
      }

      for(i ; i < sizeOfArgu ; i++) {
        // printf("enter\n");
        arguments = stringRemoveWordContaining(str, containSet); /**need free**/
        macroArgument = stringSubStringInChars(arguments , arguments->length);
        argu->entries[i] = stringNew(macroArgument);
        stringDel(arguments);
      }

      /* string position after done with the argument */
      str->startindex = end + 1;
      str->length = strlen(str->string) - str->startindex;
    }

    else if(str->string[str->startindex] == ',')
      Throw(ERR_EXPECT_IDENTIFIER);

    else Throw(ERR_EXPECT_CLOSED_BRACKET);

    return argu;
  }
  else return NULL;
}

/** *createNonIdentifierArgumentsInString(String *str, char *containSet)
 *  This function is used to create macro argument in stringStatement this diff from createMacroArguments is that this
 *  function can create non-identifier arguments
 * input :
 *			*string is a given String
 * output :
 *			return macroArgument if bracket "()" is found
 *			else return NULL
 **/
Argument *createNonIdentifierArgumentsInString(String *str, char *containSet) {
  int sizeOfArgu = 0, i = 0, start = 0, end = 0;
  char *macroArgument;
  String *arguments;
  Argument *argu;

  if(str->string[str->startindex] == '(') {
    printf("Open bracket found\n");
    str->startindex++;
    start = str->startindex;
    // printf("argument start %d, length %d\n", arguments->startindex, arguments->length);
    // printf("str start %d, length %d\n", str->startindex, str->length);

    sizeOfArgu = getSizeOfArguInString(str, containSet);
    // printf("sizeOfArgu %d\n", sizeOfArgu);

    if(str->string[str->startindex] == ')') {
      printf("Closed bracket found\n");
      /* reset string position to initial */
      end = str->startindex;
      str->startindex = start;
      str->length = strlen(str->string);

      if(sizeOfArgu == 0) {
        if(str->string[end] == ')')
          str->startindex++;
        return argu;
      }

      argu = newMacroArgument(sizeOfArgu);

      for(i ; i < sizeOfArgu ; i++) {
        // printf("enter\n");
        stringTrim(str);
        arguments = stringRemoveWordContaining(str, containSet); /**need free**/
        macroArgument = stringSubStringInChars(arguments , arguments->length);
        argu->entries[i] = stringNew(macroArgument);
        stringDel(arguments);
      }
      /* string position after done with the argument */
      str->startindex = end + 1;
      str->length = strlen(str->string) - str->startindex;
    }
    else if(str->string[str->startindex] == ',')
      Throw(ERR_EXPECT_IDENTIFIER);

    else  Throw(ERR_EXPECT_CLOSED_BRACKET);

    return argu;
  }
  else return NULL;
}

/** Extract the MacroInfo out from the given string
 * input :
 *			*string is String type pointer
 * output :
 *			return macroInfo contain all the macro information
 *			return NULL if macro information is not found
 **/
Macro *createMacroInfo(String *str) {
  char *macroName, *macroContent, *macroContentPart, EOL = '\n';
  String *name, *content;
  Macro *macroInfo;
  Argument *macroArguments = NULL;

  name = stringRemoveWordContaining(str, alphaNumericSet);

  if(name->length == 0) //Throw error name is empty
    Throw(ERR_EMPTY_MACRO_NAME);

  macroName = stringSubStringInChars(name , name->length);
  printf("str after removed name, start %d, length %d\n", str->startindex, str->length);
  macroArguments = createMacroArguments(str, alphaNumericSet);

  /*------------------------------------------------------------------------------*/
  stringTrimUntilEOL(str);

  if(str->string[str->startindex] == EOL || str->string[str->startindex] == '\0') {
    macroContent = malloc(sizeof(char) * 1);
    macroContent[0] = '\0';
    return macroInfo = newMacro(macroName, macroContent, macroArguments); //" " this space indicate it is empty content
  }
  content = stringRemoveWordContaining(str, alphaNumericSetWithSymbol);
  macroContent = stringSubStringInChars(content , content->length);

  if(str->string[str->startindex] == '\\')  {
    content = stringRemoveWordContaining(str, alphaNumericSetWithSymbol);
    macroContentPart = stringSubStringInChars(content , content->length);
    strcat(macroContent, macroContentPart);
  }
  return macroInfo = newMacro(macroName, macroContent, macroArguments); //need to free malloc
}

/** verifyRedifineArguments(Macro *macro)
 * This function is to verify redifined arguments in macro
 * input :
 *			*macro contain macroName, macroContent, macroArguments
 * output :
 *      return 1 if redifined arguments is found
 *      return 0 if redifined arguments is not found
 **/
int verifyRedifineArguments(Macro *macro) {
  int i = 0, j = 0;

  if(macro->argument != NULL) {
    if(macro->argument->size != 0)  {
      for(i ; i < macro->argument->size ; i++)  {
        for(j ; j < (macro->argument->size - i - 1); j++)  {
          if(!strcmp(macro->argument->entries[i]->string, macro->argument->entries[j+i+1]->string))  {
            printf("Warning redefine argument %s\n", macro->argument->entries[j]->string);
            return 1;
          }
        }
        j = 0;
      }
    }
  }
  return 0;
}

/** Replace all the words if it is a macro
 * input :
 *			*string is String type pointer
 *      *directiveName is C directive name
 * output :
 *      return the address of root pointer
 **/
Node *addAllMacroIntoTree(String *string, char *directiveName) {
  int i = 0, j = 0;
  Node *macroNode, *root = NULL;
  Macro *macro, *foundMacro;

  while(isHashTag(string)) {
    if(isDirective(string, directiveName))  {
      if(isIdentifier(string))  {
        macro = createMacroInfo(string);
        foundMacro = findMacroInTree(root, macro->name->string);

        if(verifyRedifineArguments(macro))
          Throw(ERR_MACRO_ARGUMENTS_REDEFINED);

        else if(foundMacro != NULL)  { //check redefined macro
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

    if(strcmp(macroString, targetMacro) == 0) {
      return macro;
    }

    else if(macro->name->string[0] >= targetMacro[0])
      findMacroInTree(root->left, targetMacro);

    else findMacroInTree(root->right, targetMacro);
  }
  else  return NULL;
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
  String *subString = NULL, *arguList = NULL;
  Macro *foundMacro = NULL;

  subString = stringRemoveWordContaining(str, alphaNumericSet);
  printf("subString start %d, length %d\n", subString->startindex, subString->length);
  while(subString->length != 0)  {

    token = stringSubStringInChars(subString, subString->length); /**need free**/
    foundMacro = findMacroInTree(root, token);
    free(token);
    if(foundMacro != NULL)  {
      if(foundMacro->argument != NULL) {
        if(foundMacro->argument->withArgument == 1 && str->string[str->startindex] != '(')
          Throw(ERR_EXPECT_ARGUMENT);
        else if(foundMacro->argument->size != 0 && str->string[str->startindex] == '(') {
          arguList = stringRemoveWordContaining(str, alphaNumericSetWithSymbol);
          subString->length = subString->length + arguList->length;
          stringDel(arguList);
        }
      }
      break;
    }
    free(subString);
    subString = stringRemoveWordContaining(str, alphaNumericSet);
  }
  return subString;
}

/** *replaceMacroInString(String *oriString, String *subString, Macro *macro, int size)
 * This function is use to replace macro found inside the string
 *
 ** input :
 *          *latestString is a pointer pointing to latest update string statement
 *          *macroSubString is the position of macro inside string
 *          *macro is a pointer contain macro information
 *          size is the size of string after replaced with macro content
 ** output :
 *          return the character string after replaced macro name with macro content
 **/
char *replaceMacroInString(String *latestString, String *macroSubString, Macro *foundMacro, int size) {
  int i = 0, j = 0, start = 0;
  char *replacedMacroInString = malloc(sizeof(char) * size + 1);

  if(foundMacro != NULL)   {
    for(i; i< size ; i++) {
      if(start == macroSubString->startindex) {
        for(j; j< strlen(foundMacro->content->string) ; j++)  {
          replacedMacroInString[i++] = foundMacro->content->string[j];
        }
        start += foundMacro->name->length;
      }
      if(latestString->string[start] == '\0')
        break;
      replacedMacroInString[i] = latestString->string[start++];
    }
    replacedMacroInString[i] = '\0';
  }

  else  {

    for(i; i< size ; i++) {
      replacedMacroInString[i] = latestString->string[start++];
    }
    replacedMacroInString[i] = '\0';
  }
  printf("replacedMacroInString %s\n", replacedMacroInString);
  return replacedMacroInString;
}

/** String *directiveDefine(String *str, char *directiveName)
 * This function is
 *
 ** input :
 ** output :
 **/
String *directiveDefine(String *str, char *directiveName) {
  int size, count = 0, cyclic = 0, nextToCyclic = 0;
  char *macroToken, *stringStatement, *replacedMacroString = NULL;
  String *macroSubString, *latestString;
  Macro *foundMacro;
  LinkedList *head = NULL, *newList = NULL;

  Node *root = addAllMacroIntoTree(str, directiveName); //add all predefined macro into tree
  // printf("str startindex %d, length %d\n", str->startindex, str->length);
  stringStatement = stringSubStringInChars(str, str->length);
  // printf("stringStatement %p\n", stringStatement);
  // printf("stringStatement %s\n", stringStatement);
  latestString = stringNew(stringStatement);
  // printf("latestString %p\n", latestString);
  // printf("latestString string %s, start %d, length %d\n", latestString->string, latestString->startindex, latestString->length);
  // printf("latestString %p\n", latestString);
  macroSubString = macroPositionInString(latestString, root);
  // printf("macroSubString start %d, length %d\n", macroSubString->startindex, macroSubString->length);
  /*******************************************************************************************/
  while(macroSubString->length != 0) {
    macroToken = stringSubStringInChars(macroSubString, macroSubString->length);
    // printf("macroToken %p\n", macroToken);
    foundMacro = findMacroInTree(root, macroToken);
    // printf("foundMacro %p\n", foundMacro);
    // printf("foundMacro name %s, content %s\n", foundMacro->name->string, foundMacro->content->string);
    if(foundMacro != NULL)  {//get size of replace macro string
      size = strlen(latestString->string) - (foundMacro->name->length) + (foundMacro->content->length);

      cyclic = findList(&head, foundMacro->name->string);
      // printf("cyclic %d\n", cyclic);
      if(cyclic)  {
        // printf("cyclic happen at %s\n", foundMacro->name->string);
        nextToCyclic = latestString->startindex;
        destroyAllLinkedLists(head);
        head = NULL;
      }
      else  {
        newList = linkListNew(foundMacro->name->string); //Create new list
        addLinkedList(&head, newList);
        // printf("create new list for %s\n", foundMacro->name->string);
      }
    }
    else  size = strlen(latestString->string);

   // printf("size %d\n", size);
   // printf("latestString string %s, start %d, length %d\n", latestString->string, latestString->startindex, latestString->length);
   // printf("macroSubString start %d, length %d\n", macroSubString->startindex, macroSubString->length);
   if(!cyclic)  {
      replacedMacroString = replaceMacroInString(latestString, macroSubString, foundMacro, size);
      /* free before re-use latestString */
      subStringDel(latestString->string);
      stringDel(latestString);

      latestString = stringNew(replacedMacroString);
   }
       // return NULL;
    if(nextToCyclic)  //always start at next to cyclic happen
      latestString->startindex = nextToCyclic;

    stringDel(macroSubString);
    macroSubString = macroPositionInString(latestString, root);
    // printf("macroSubString %p\n", macroSubString);
    // printf("macroString start %d, length %d\n", macroString->startindex, macroString->length);
      // return NULL;
    subStringDel(macroToken);
  }
  stringDel(macroSubString);
  destroyAllMacroInTree(root);
  destroyAllLinkedLists(head);

  latestString->startindex = 0;
  latestString->length = strlen(latestString->string);
  return latestString;
}