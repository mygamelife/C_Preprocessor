#include <stdio.h>
#include "RedBlackTree.h"

void _addRedBlackTree(Node **rootPtr, Node *newNode);
Node *_delRedBlackTreex(Node **rootPtr, Node *removeNode);

char parentColor; //store parent color

void addRedBlackTree(Node **rootPtr, Node *newNode)	{
	_addRedBlackTree(rootPtr, newNode);

  Node *root = *rootPtr;
  root->color = 'b';
}

void _addRedBlackTree(Node **rootPtr, Node *newNode)	{
	Node *root = *rootPtr;

	if(root == NULL)	{
		*rootPtr = newNode;
		return;
	}

	else if(root->data >= newNode->data)	{
		_addRedBlackTree(&root->left, newNode);

    if(root->left != NULL)  {
      if(root->right != NULL)
        childColorViolatation(rootPtr);  //handle 4-node

      else if(root->left->left != NULL)
        checkLeftLeft(rootPtr); // handle 3-node

      else if(root->left->right != NULL)
        checkLeftRight(rootPtr); // handle 3-node
    }
  }

	else if(root->data <= newNode->data)	{
		_addRedBlackTree(&root->right, newNode);

    if(root->right != NULL)  {
      if(root->left != NULL)
        childColorViolatation(rootPtr);

      if(root->right->right != NULL)
        checkRightRight(rootPtr);

      else if(root->right->left != NULL)
        checkRightLeft(rootPtr);
    }
   }
}

/* Check currentNode left-right node
 * input : Root node
 * ouput : LeftRightRotate if left-right node is not NULL and flip right node color to 'r'
 */
void checkLeftRight(Node **rootPtr) {
  Node *root = *rootPtr;

  if(root->left->right->color == 'r' && root->left->color == 'r')  {
    leftRightRotate(&(*rootPtr));
    (*rootPtr)->right->color = 'r';
  }
}

/* Check currentNode left-left node
 * input : Root node
 * ouput : rightRotate if left-left node is not NULL and flip right node color to 'r'
 */
void checkLeftLeft(Node **rootPtr)  {
  Node *root = *rootPtr;

  if(root->left->left->color == 'r' && root->left->color == 'r')  {
    rightRotate(&(*rootPtr));
    (*rootPtr)->right->color = 'r';
  }
}

/* Check currentNode right-right node
 * input : Root node
 * ouput : leftRotate if right-right node is not NULL and flip left node color to 'r'
 */
void checkRightRight(Node **rootPtr)  {
  Node *root = *rootPtr;

  if(root->right->right->color == 'r' && root->right->color == 'r') {
    leftRotate(&(*rootPtr));
    (*rootPtr)->left->color = 'r';
  }
}

/* Check currentNode right-left node
 * input : Root node
 * ouput : rightRotate if left-left node is not NULL and flip right node color to 'r'
 */
void checkRightLeft(Node **rootPtr) {
  Node *root = *rootPtr;

  if(root->right->left->color == 'r' && root->right->color == 'r')  {
    rightLeftRotate(&(*rootPtr));
    (*rootPtr)->left->color = 'r';
	}
}

/* Verify the child color
 * input : Root node
 * ouput : flip left and right node color if 3 nodes are red color
 */
void childColorViolatation(Node **rootPtr)  {
  Node *root = *rootPtr;

  if(root->left->color == 'r' && root->right->color == 'r') {
    if(root->left->left != NULL && root->left->left->color == 'r')	{
      root->left->color = 'b';
      root->right->color = 'b';
      root->color = 'r';
    }

    else if(root->left->right != NULL && root->left->right->color == 'r')	{
      root->left->color = 'b';
      root->right->color = 'b';
      root->color = 'r';
    }

    else if(root->right->left != NULL && root->right->left->color == 'r')	{
      root->left->color = 'b';
      root->right->color = 'b';
      root->color = 'r';
    }

    else if(root->right->right != NULL && root->right->right->color == 'r')	{
      root->left->color = 'b';
      root->right->color = 'b';
      root->color = 'r';
    }
  }
}

/*---------------------Old-----------------------------------*/
void handleViolatation(Node **rootPtr)  {
  Node *root = *rootPtr;

  if(root->left == NULL && root->right != NULL) {
    if(root->right->left !=NULL && root->right->right != NULL)
      leftRotate(&(*rootPtr));
  }

  else if(root->left != NULL && root->right == NULL) {
    if(root->left->left !=NULL && root->left->right != NULL)
      rightRotate(&(*rootPtr));
  }
}

void colorFlipping(Node **rootPtr, Node *removedNode)  {
  Node *root = *rootPtr;

  if(root->left == NULL && root->right != NULL) {
    if(root->right->color == 'b') {
      root->color = 'b';
      root->right->color = 'r';
    }
    return;
  }

  else if(root->left != NULL && root->right == NULL)  {
    if(root->left->color == 'b')  {
      root->color = 'b';
      root->left->color = 'r';
    }
    return;
  }

  else if(root->data > removedNode->data)
    colorFlipping(&root->left, removedNode);

  else if(root->data < removedNode->data)
    colorFlipping(&root->right, removedNode);
}

Node *delRedBlackTreex(Node **rootPtr, Node *removeNode)  {
  Node *root, *node;

  node = _delRedBlackTreex(rootPtr, removeNode);
  root = *rootPtr;

  if(root != NULL)
    root->color = 'b';

  return node;
}

Node *_delRedBlackTreex(Node **rootPtr, Node *removeNode) {
  Node *root, *node = *rootPtr;

  if(node == NULL)
    Throw(ERR_NODE_UNAVAILABLE);

  else if(node->data == removeNode->data)  {
    *rootPtr = NULL;
    return node;
  }

  else if(node->data > removeNode->data)  {
    node = _delRedBlackTreex(&node->left, removeNode);

    if(node->color == 'b')  {
      handleViolatation(rootPtr);
      colorFlipping(rootPtr, node);
    }
    return node;
  }

  else if(node->data < removeNode->data)  {
    node = _delRedBlackTreex(&node->right, removeNode);

    if(node->color == 'b')  {
      handleViolatation(rootPtr);
      colorFlipping(rootPtr, node);
    }
    return node;
  }
}
/*--------------------------New-------------------------------*/
int isDoubleBlack(Node *rootPtr)  {
  if(rootPtr == NULL || rootPtr->color == 'd')
    return 1;

  else  return 0;
}

//pass in nephew and check if there is grandchild
int checkGrandchild(Node *rootPtr)  {

  if(rootPtr != NULL) {
    if(rootPtr->left != NULL || rootPtr->right != NULL)
      return 1;
  }

  else  return 0;
}

int caseSelect(Node *rootPtr) {

  if(rootPtr == NULL)
    return;

  Node* rootLeftPtr = rootPtr->left;
  Node* rootRightPtr = rootPtr->right;

  if(rootRightPtr != NULL)
    printf("rootRightPtr %d\n", rootRightPtr->data);
  else if(rootLeftPtr != NULL)
    printf("rootLeftPtr %d\n", rootLeftPtr->data);
  // case1 sibling is black and has a red nephew
  if(rootPtr->color == 'b') {
    if(rootRightPtr != NULL && rootRightPtr->color == 'r' ||  rootLeftPtr != NULL && rootLeftPtr->color == 'r')
      return 1;
    // case2 sibling is black and both nephew are black
    else if((rootRightPtr == NULL || rootRightPtr->color == 'b') && (rootLeftPtr == NULL || rootLeftPtr->color == 'b'))
      return 2;
  }

  else if(rootPtr->color == 'r' && (rootPtr->left  ||  rootPtr->right))
    return 3;

  else  return -1;
}

void handleCaseViolation(Node **rootPtr, int caseNum)  {
  if(caseNum == 1)
    handleCaseOne(rootPtr);
  else if(caseNum == 2)
    handleCaseTwo(rootPtr);
  else if(caseNum == 3)
    handleCaseThree(rootPtr);
  else return;
}

//handle Case 1
void handleCaseOne(Node **rootPtr) {
  Node *root = *rootPtr;
  parentColor = root->color;
  printf("parentColor %c\n", parentColor);

  //Rotation (Right side)
  if(root->right != NULL) {
    if(root->right->left == NULL && root->right->right != NULL) {
      leftRotate(&(*rootPtr));
      printf("(*rootPtr)->data %d\n", (*rootPtr)->data);
    }

    else if(root->right->left != NULL && root->right->right == NULL) {
      rightLeftRotate(&(*rootPtr));
      printf("(*rootPtr)->data %d\n", (*rootPtr)->data);
    }
  }

  //Rotation (left side)
  else if(root->left != NULL) {
    if(root->left->left != NULL && root->left->right == NULL) {
      rightRotate(&(*rootPtr));
      printf("(*rootPtr)->data %d\n", (*rootPtr)->data);
    }
    else if(root->left->left == NULL && root->left->right != NULL) {
      leftRightRotate(&(*rootPtr));
      printf("(*rootPtr)->data %d\n", (*rootPtr)->data);
    }
  }

  //color flipping
  (*rootPtr)->color = parentColor;
  (*rootPtr)->left->color = 'b';
  (*rootPtr)->right->color = 'b';
}

//handle Case2
void handleCaseTwo(Node **rootPtr)  {
  Node *root = *rootPtr;
  printf("rootPtr data %d\n", root->data);
  //flip root color
  if(root->color == 'b')
    root->color = 'd';
  else if(root->color == 'r')
    root->color = 'b';

  if(root->left != NULL)
    root->left->color = 'r';
  else if(root->right != NULL)
    root->right->color = 'r';
  else if(root->left != NULL && root->right != NULL)  {
    root->left->color = 'b';
  }
}

//handle Case3
void handleCaseThree(Node **rootPtr)  {
  Node *root = *rootPtr;

  //Rotation (Right side)
  if(root->right != NULL && root->right->color == 'r') {
    leftRotate(&(*rootPtr));
    printf("*rootPtr->data %d\n", (*rootPtr)->data);

    (*rootPtr)->color = 'b';
    (*rootPtr)->left->color = 'r';
  }

  //Rotation (left side)
  else if(root->left != NULL && root->left->color == 'r') {
    rightRotate(&(*rootPtr));
    printf("*rootPtr->data %d\n", (*rootPtr)->data);

    (*rootPtr)->color = 'b';
    (*rootPtr)->right->color = 'r';
  }

  Node *rootLeftPtr = (*rootPtr)->left; //left sibling
  Node *rootRightPtr = (*rootPtr)->right; //right sibling

  //check isDoubleBlack at left side(case2)
  if(isDoubleBlack(rootLeftPtr->left)  &&  rootLeftPtr->color == 'r'  &&  !checkGrandchild(rootLeftPtr->right))  {
    // if((*rootPtr)->left->right != NULL && (*rootPtr)->left->right->color == 'b')
      handleCaseTwo(&(*rootPtr)->left); //call case2
  }
  //check isDoubleBlack at right side(case2)
  else if(isDoubleBlack(rootRightPtr->right)  &&  rootRightPtr->color == 'r'  &&  !checkGrandchild(rootRightPtr->left))  {
    // if((*rootPtr)->right->left != NULL && (*rootPtr)->right->left->color == 'b')
      handleCaseTwo(&(*rootPtr)->right); //call case2
  }
  //check isDoubleBlack at left side(case1)
  else if(isDoubleBlack(rootLeftPtr->left)  &&  rootLeftPtr->color == 'r'  &&  checkGrandchild(rootLeftPtr->right))  {
    // if((*rootPtr)->left->right != NULL && (*rootPtr)->left->right->color == 'b')
      handleCaseOne(&(*rootPtr)->left); //call case1
  }
  //check isDoubleBlack at right side(case1)
  else if(isDoubleBlack(rootLeftPtr->right)  &&  rootRightPtr->color == 'r'  &&  checkGrandchild(rootRightPtr->left))  {
  // if((*rootPtr)->left->right != NULL && (*rootPtr)->left->right->color == 'b')
      handleCaseOne(&(*rootPtr)->right); //call case1
  }
}

Node *delRedBlackTree(Node **rootPtr, Node *removeNode)  {
  Node *root, *node;

  node = _delRedBlackTree(rootPtr, removeNode);

  if(*rootPtr != NULL)
    (*rootPtr)->color = 'b';

  return node;
}

Node *_delRedBlackTree(Node **rootPtr, Node *removeNode) {
  Node *root, *node = *rootPtr;
  int _case;

  if(node == NULL)
    Throw(ERR_NODE_UNAVAILABLE);

  //find removeNode
  else if(node->data == removeNode->data)  {
    *rootPtr = NULL;
    return node;
  }

  //left side
  else if(node->data > removeNode->data)  {
    node = _delRedBlackTree(&node->left, removeNode);

    if(isDoubleBlack((*rootPtr)->left)) {
      if((*rootPtr) != NULL)
        printf("data %d\n", (*rootPtr)->data);
      _case = caseSelect((*rootPtr)->right);
      printf("_case %d\n", _case);
      handleCaseViolation(&(*rootPtr), _case);
    }
    return node;
  }

  //right side
  else if(node->data < removeNode->data)  {
    node = _delRedBlackTree(&node->right, removeNode);

    if(isDoubleBlack((*rootPtr)->right)) {
      _case = caseSelect((*rootPtr)->left);
      printf("_case %d\n", _case);
      handleCaseViolation(&(*rootPtr), _case);
    }
    return node;
  }
}

/******************************************************************
 *                Generic AddRedBlackTree                         *
 *    input:  rootPtr and any type of data                        *
 *    output: add the data into redBlackTree                      *
 ******************************************************************/
int compare(Node **rootPtr, Node *newNode)  {
  Node *root = *rootPtr;
  Macro *m1 = (Macro*)root->dataPtr;
  Macro *m2 = (Macro*)newNode->dataPtr;

  if(m1->name->string[0] > m1->name->string[0])
    return 1;
  else if(m1->name->string[0] < m1->name->string[0])
    return 0;
  else return -1;
}

void genericAddRedBlackTree(Node **rootPtr, Node *newNode)	{
  _genericAddRedBlackTree(rootPtr, newNode);

  // Node *root = *rootPtr;
  // root->color = 'b';
}

void _genericAddRedBlackTree(Node **rootPtr, Node *newNode)	{
	Node *root = *rootPtr;
 
	if(*rootPtr == NULL)	{
		(*rootPtr) = newNode;
		return;
	}

	else if(compare(&(*rootPtr), newNode))	{
		_genericAddRedBlackTree(&root->left, newNode);

    if(root->left != NULL)  {
      if(root->right != NULL)
        childColorViolatation(rootPtr);  //handle 4-node

      else if(root->left->left != NULL)
        checkLeftLeft(rootPtr); // handle 3-node

      else if(root->left->right != NULL)
        checkLeftRight(rootPtr); // handle 3-node
    }
  }

	// else if(root->data <= newNode->data)	{
		// _genericAddRedBlackTree(&root->right, newNode);

    // if(root->right != NULL)  {
      // if(root->left != NULL)
        // childColorViolatation(rootPtr);

      // if(root->right->right != NULL)
        // checkRightRight(rootPtr);

      // else if(root->right->left != NULL)
        // checkRightLeft(rootPtr);
    // }
   // }
}