#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotations.h"
#include "RedBlackTree.h"
#include "CustomAssertions.h"
#include "StringObject.h"
#include "Macro.h"

Node node1, node4, node5, node6, node7, node8, node10, node13, node15,
     node20, node22, node30, node40, node60; //Share to all test

/* Run reset before test*/
void setUp(void)	{}

void tearDown(void) {}

void test_resetGenericNode(void)	{
	Macro *macro = newMacro("A", "1");
  Node *root, genericNode;
  root = &genericNode;
  
	printf("Start test_resetGenericNode\n");
  resetGenericNode(&genericNode, macro);
  Macro *m = (Macro*)root->dataPtr;
  printf("macro name %s\n", m->name->string);
	printf("-----------------------------");
  
  TEST_ASSERT_NOT_NULL(root);
  TEST_ASSERT_NULL(root->left);
  TEST_ASSERT_NULL(root->right);
  TEST_ASSERT_NOT_NULL(root->dataPtr);
}

//left side
void test_genericAddRedBlackTree_given_macroName_and_macroContent_should_store_at_left_side_of_RedBlackTree(void)	{
	Macro *macro1 = newMacro("CD", "10");
	Macro *macro2 = newMacro("AB", "20");
  Node *root, genericNode, genericNode2;
  resetGenericNode(&genericNode, macro1);
  resetGenericNode(&genericNode2, macro2);
  root = &genericNode;
  
	printf("Start test_genericAddRedBlackTree_given_macroName_and_macroContent_should_store_at_left_side_of_RedBlackTree\n");
  genericAddRedBlackTree(&root, &genericNode2);
	printf("-----------------------------");
  
  //root
  TEST_ASSERT_NOT_NULL(root);
  TEST_ASSERT_NOT_NULL(root->left);
  TEST_ASSERT_NULL(root->right);
  TEST_ASSERT_NOT_NULL(root->dataPtr);
  Macro *m1 = (Macro*)root->dataPtr;
  TEST_ASSERT_EQUAL_STRING("CD", m1->name->string);
  TEST_ASSERT_EQUAL_STRING("10", m1->content->string);
  
  //left child
  TEST_ASSERT_NOT_NULL(root->left);
  TEST_ASSERT_NULL(root->left->left);
  TEST_ASSERT_NULL(root->left->right);
  TEST_ASSERT_NOT_NULL(root->left->dataPtr);
  Macro *m2 = (Macro*)root->left->dataPtr;
  TEST_ASSERT_EQUAL_STRING("AB", m2->name->string);
  TEST_ASSERT_EQUAL_STRING("20", m2->content->string);
}