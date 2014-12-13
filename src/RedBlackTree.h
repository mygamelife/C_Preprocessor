#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "Node.h"
#include "Rotations.h"
#include "ErrorCode.h"
#include "StringObject.h"
#include "Macro.h"

#define addMacro(rootPtr, newNode)  genericAddRedBlackTree(rootPtr, newNode, compare)

void addRedBlackTree(Node **rootPtr, Node *newNode);
Node *delRedBlackTreex(Node **rootPtr, Node *removeNode);
void checkLeftRight(Node **rootPtr);
void checkLeftLeft(Node **rootPtr);
void checkRightRight(Node **rootPtr);
void checkRightLeft(Node **rootPtr);
void childColorViolatation(Node **rootPtr);
void handleViolatation(Node **rootPtr);
void colorFlipping(Node **rootPtr, Node *removedNode);

//generic redBlackTree
// void genericAddRedBlackTree(Node **rootPtr, Node *newNode, int (*compare)(void **rootPtr, void *newNode));
void _genericAddRedBlackTree(Node **rootPtr, Node *newNode, int (*comparePtr)(void **rootPtr, void *newNode));
int compare(void **rootPtr, void *newNode);

//new implement
Node *delRedBlackTree(Node **rootPtr, Node *removeNode);
Node *_delRedBlackTree(Node **rootPtr, Node *removeNode);
int isDoubleBlack(Node *rootPtr);
int caseSelect(Node *rootPtr);
int checkGrandchild(Node *rootPtr);
void handleCaseViolation(Node **rootPtr, int caseNum);
void handleCaseOne(Node **rootPtr);
void handleCaseTwo(Node **rootPtr);
void handleCaseThree(Node **rootPtr);
#endif // RedBlackTree_H

