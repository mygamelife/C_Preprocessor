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
Macro *newMacro(char *macroName, char *macroContent)  {
  Macro *macro = malloc(sizeof(Macro));

  macro->name = stringNew(macroName);
  macro->content = stringNew(macroContent);

  return macro;
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

/** Free the malloc memory in newMacro()
 * input :
 *			*macro is a macro type pointer
 * output :
 *			free all the malloc memory in newMacro()
 **/
void delMacro(Macro *macro) {

  if(macro) {
    if(macro->name->string) {
      subStringDel(macro->name->string);
      stringDel(macro->name);
    }
    if(macro->content->string)  {
      subStringDel(macro->content->string);
      stringDel(macro->content);
    }    
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
    delMacro(macro);
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