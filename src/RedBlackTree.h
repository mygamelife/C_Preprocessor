#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "Node.h"
#include "Rotations.h"
#include "ErrorCode.h"
#include "Macro.h"

void addRedBlackTree(Node **rootPtr, Node *newNode);
Node *delRedBlackTree(Node **rootPtr, Node *removeNode);
void checkLeftRight(Node **rootPtr);
void checkLeftLeft(Node **rootPtr);
void checkRightRight(Node **rootPtr);
void checkRightLeft(Node **rootPtr);
void childColorViolatation(Node **rootPtr);
void handleViolatation(Node **rootPtr);
void colorFlipping(Node **rootPtr, Node *removedNode);

#endif // RedBlackTree_H
