#include <stdio.h>
#include "Rotations.h"

void rightRotate(Node **rootPtr)	{
  Node *node, *currentNode;

  currentNode = *rootPtr; //Current root
  *rootPtr = currentNode->left;
  node = *rootPtr; //temp node
  
  if(node->right != NULL) {
    currentNode->left = node->right;
    node->right = NULL;
  }
  
  else
    currentNode->left = NULL;
    
  node->right = currentNode;
}

void leftRotate(Node **rootPtr)  {
  Node *node, *currentNode;

  currentNode = *rootPtr; //Current root
  *rootPtr = currentNode->right; //Rotated root
  node = *rootPtr; //node = Rotated root
  
  if(node->left != NULL) {
    currentNode->right = node->left;
    node->left = NULL;
  }

  else
    currentNode->right = NULL;
    
  node->left = currentNode;
}

void leftRightRotate(Node **rootPtr)  {
  Node *node, *currentNode;
  
  currentNode = *rootPtr;
  node = currentNode->left;
  
  leftRotate(&node);
  
  currentNode->left = node;
  
  rightRotate(&(*rootPtr)); //Pass in *root pointer address
}

void rightLeftRotate(Node **rootPtr)  {
  Node *node, *currentNode;
  
  currentNode = *rootPtr;
  node = currentNode->right;
  
  rightRotate(&node); 
   
  currentNode->right = node;
  
  leftRotate(&(*rootPtr)); //Pass in *root pointer address

}