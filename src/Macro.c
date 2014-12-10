#include <stdio.h>
#include <malloc.h>
#include "Macro.h"

/** Create new macro to store the macro name and content
 * input :
 *			*macroName is macro's name
 *			*macroContent is macro's content
 * output :
 *			return macro pointer that pointing to this structure
 **/
Macro *newMacro(char *macroName, char *macroContent, Argument *arguList)  {
  Macro *macro = malloc(sizeof(Macro));

  macro->name = stringNew(macroName);
  macro->content = stringNew(macroContent);
  macro->argument = arguList;

  return macro;
}

/** Create new macro argument to store argument
 * input :
 *        arguments size
 * output :
 *			    return Argument pointer that pointing to this structure
 **/
Argument *newMacroArgument(int size)  {
  int i = 0;
  Argument *argu = malloc(sizeof(Argument) + (sizeof(String*) * size));

  argu->size = size;
  argu->entries[size];
  for(i; i<size ; i++)
    argu->entries[i] = malloc(sizeof(List));
  return argu;
}

/** Free the malloc memory in MacroArgument
 * input :
 *			*argu is a pointer pointing macroArgument
 * output :
 *			free the malloc memory in macroArgument
 **/
void delMacroArgument(Argument *argu)  {
  int i = 0;

  if(argu != NULL)  {
    for(i ; i< argu->size ; i++)  {
      free(argu->entries[i]->name);
      free(argu->entries[i]->value);
      free(argu->entries[i]);
    }
    free(argu);
  }
}

/** Create new macroNode to store the Node structure
 * input :
 *			*macroInfo is a pointer contain macro information name and content
 * output :
 *			return node pointer that contain the node structure information
 **/
Node *macroNodeNew(Macro *macroInfo)
{
	Node *node = malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	node->color = 'b';
	node->dataPtr = macroInfo;

	return node;
}

/** Free the malloc memory in name/content->string
 * input :
 *			*string is a pointer pointing to name/content->string and argument
 * output :
 *			free the malloc memory
 **/
void delMacroNameAndContent(Macro *macro)
{
  if(macro)  {
    if(macro->name) {
      subStringDel(macro->name->string);
      free(macro->name);
    }
    if(macro->content)  {
      subStringDel(macro->content->string);
      free(macro->content);
    }
    delMacroArgument(macro->argument);
    free(macro);
  }
}

/** Free the malloc memory in newMacro()
 * input :
 *			*macro is a macro type pointer
 * output :
 *			free all the malloc memory in newMacro()
 **/
void delMacro(Macro *macro) {

  if(macro) {
    stringDel(macro->name);
    stringDel(macro->content);
    delMacroArgument(macro->argument);
    free(macro);
  }
}

/** Free the malloc memory in macroNodeNew()
 * input :
 *			*node is a node type pointer
 * output :
 *			free all the malloc memory in macroNodeNew() and newMacro()
 **/
void delMacroNode(Node *node)
{
	if(node)  {
    Macro *macro = (Macro*)node->dataPtr;
    delMacroNameAndContent(macro);
    free(node);
  }
}

/** Free all macroNode in tree
 * input :
 *			*root is a node type pointer pointing to root
 * output :
 *			free all the macroNode malloc memory in tree
 **/
void destroyAllMacroInTree(Node *root)
{
  if(root != NULL)  {
    destroyAllMacroInTree(root->left);
    destroyAllMacroInTree(root->right);
    delMacroNode(root);
    root = NULL;
  }
}