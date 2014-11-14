#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotations.h"
#include "RedBlackTree.h"
#include "CustomAssertions.h"
#include "StringObject.h"
#include "Macro.h"

Node *root, nodeA, nodeB, nodeC;

/* Run reset before test*/
void setUp(void)	{}

void tearDown(void) {}

/*
 * Root->  NULL                nodeA  <-Root
 *                add nodeA
 *                ---->
 */
void test_genericAddRedBlackTree(void)	{
	Macro *macro = newMacro("A", "1");
  resetGenericNode(&nodeA, macro);

  root = NULL;

	printf("Start test_resetGenericNode\n");
  genericAddRedBlackTree(&root, &nodeA);
	printf("-----------------------------");

  TEST_ASSERT_NOT_NULL(root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', root);
  TEST_ASSERT_NOT_NULL(root->dataPtr);
  Macro *m = (Macro*)root->dataPtr;
  TEST_ASSERT_EQUAL_STRING("A", m->name->string);
}

//left side
void test_genericAddRedBlackTree_given_macroName_and_macroContent_should_store_at_left_side_of_RedBlackTree(void)	{
	Macro *macro1 = newMacro("CD", "10");
	Macro *macro2 = newMacro("AB", "20");
  resetGenericNode(&nodeC, macro1);
  resetGenericNode(&nodeA, macro2);

  root = &nodeC;

	printf("Start test_genericAddRedBlackTree_given_macroName_and_macroContent_should_store_at_left_side_of_RedBlackTree\n");
  genericAddRedBlackTree(&root, &nodeA);
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