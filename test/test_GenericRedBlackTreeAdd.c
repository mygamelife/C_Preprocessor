#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotations.h"
#include "RedBlackTree.h"
#include "CustomAssertions.h"
#include "StringObject.h"
#include "Macro.h"

Node nodeA, nodeB, nodeC; //Share to all test

/* Run reset before test*/
void setUp(void)	{}

void tearDown(void) {}

/**Test compare() given
 *  macro1 = "Apple","50"
 *  macro2 = "Orange","100"
 *
 *  compare "Apple" and "Orange" should return 0
 **/
void test_compare_given_Apple_Orange_should_return_0(void)  {
  Macro *macro1 = newMacro("Apple", "50");
	Macro *macro2 = newMacro("Orange", "100");
  resetGenericNode(&nodeA, macro1);
  resetGenericNode(&nodeB, macro2);
  Node *root = &nodeA;
  int result = 0;
  result = compare((void*)&root, &nodeB);

  TEST_ASSERT_EQUAL(0, result);

  delMacro(macro1);
  delMacro(macro2);
}

/**Test compare() given
 *  macro1 = "Girl","75"
 *  macro2 = "Boy","999"
 *
 *  compare "Girl" and "Boy" should return 1
 **/
void test_compare_given_Girl_and_Boy_should_return_1(void)  {
  Macro *macro1 = newMacro("Girl", "75");
	Macro *macro2 = newMacro("Boy", "999");
  resetGenericNode(&nodeA, macro1);
  resetGenericNode(&nodeB, macro2);
  Node *root = &nodeA;

  int result = compare((void*)&root, &nodeB);

  TEST_ASSERT_EQUAL(1, result);

  delMacro(macro1);
  delMacro(macro2);
}

// #define addMacro(rootPtr, newNode)  genericAddRedBlackTree(rootPtr, newNode, compare)
/**store macro2 to left-side of macro1 given macro1 and macro2 info:
 ** nodeA = macro1 = contain "Cat", "10"
 ** nodeB = macro2 = contain "Bird", "20"
 *
 *  result  :
 *                  root
 *                   |
 *                   V
 *                  nodeA
 *                /      \
 *          nodeB        -
 *        /      \
 *       -        -
**/
void test_genericAddRedBlackTree_given_macroName_and_macroContent_should_store_at_left_side_of_RedBlackTree(void)	{
	Macro *macro1 = newMacro("Cat", "10");
	Macro *macro2 = newMacro("Bird", "20");
  resetGenericNode(&nodeA, macro1);
  resetGenericNode(&nodeB, macro2);
  Node *root = &nodeA;

	printf("Start test_genericAddRedBlackTree_given_macroName_and_macroContent_should_store_at_left_side_of_RedBlackTree\n");
  addMacro(&root, &nodeB);
	printf("-----------------------------\n");

  //root
  TEST_ASSERT_NOT_NULL(root);
  TEST_ASSERT_NOT_NULL(root->left);
  TEST_ASSERT_NULL(root->right);
  TEST_ASSERT_NOT_NULL(root->dataPtr);
  Macro *m1 = (Macro*)root->dataPtr;
  TEST_ASSERT_EQUAL_STRING("Cat", m1->name->string);
  TEST_ASSERT_EQUAL_STRING("10", m1->content->string);

  //left child
  TEST_ASSERT_NOT_NULL(root->left);
  TEST_ASSERT_NULL(root->left->left);
  TEST_ASSERT_NULL(root->left->right);
  TEST_ASSERT_NOT_NULL(root->left->dataPtr);
  Macro *m2 = (Macro*)root->left->dataPtr;
  TEST_ASSERT_EQUAL_STRING("Bird", m2->name->string);
  TEST_ASSERT_EQUAL_STRING("20", m2->content->string);

  TEST_ASSERT_EQUAL_NODE(&nodeB, NULL, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &nodeB);

  delMacro(macro1);
  delMacro(macro2);
}

/**store macro3 to right-side of macro1 given macro1, macro2 and macro3 info:
 ** nodeA = macro1 = contain "Dragon", "200"
 ** nodeB = macro2 = contain "Bear", "300"
 ** nodeB = macro3 = contain "Mouse", "400"
 *
 *  result  :
 *                  root
 *                   |
 *                   V
 *                  nodeA
 *                /      \
 *          nodeB         nodeC
 *        /      \      /     \
 *       -        -    -      -
**/
void test_genericAddRedBlackTree_given_macroName_and_macroContent_should_store_at_right_side_of_RedBlackTree(void)	{
  Macro *macro1 = newMacro("Dragon", "200");
	Macro *macro2 = newMacro("Bear", "300");
	Macro *macro3 = newMacro("Mouse", "400");
  resetGenericNode(&nodeA, macro1);
  resetGenericNode(&nodeB, macro2);
  resetGenericNode(&nodeC, macro3);
  Node *root = NULL;

	printf("Start test_genericAddRedBlackTree_given_macroName_and_macroContent_should_store_at_right_side_of_RedBlackTree\n");
  addMacro(&root, &nodeA);
	printf("-----------------------------\n");

  //root
  TEST_ASSERT_NOT_NULL(root);
  TEST_ASSERT_NOT_NULL(root->dataPtr);
  Macro *m1 = (Macro*)root->dataPtr;
  TEST_ASSERT_EQUAL_STRING("Dragon", m1->name->string);
  TEST_ASSERT_EQUAL_STRING("200", m1->content->string);

  addMacro(&root, &nodeB);
  // left child
  TEST_ASSERT_NOT_NULL(root->left);
  TEST_ASSERT_NOT_NULL(root->left->dataPtr);
  Macro *m2 = (Macro*)root->left->dataPtr;
  TEST_ASSERT_EQUAL_STRING("Bear", m2->name->string);
  TEST_ASSERT_EQUAL_STRING("300", m2->content->string);

  addMacro(&root, &nodeC);
  // Right child
  TEST_ASSERT_NOT_NULL(root->right);
  TEST_ASSERT_NOT_NULL(root->right->dataPtr);
  Macro *m3 = (Macro*)root->right->dataPtr;
  TEST_ASSERT_EQUAL_STRING("Mouse", m3->name->string);
  TEST_ASSERT_EQUAL_STRING("400", m3->content->string);

  TEST_ASSERT_EQUAL_NODE(&nodeB, &nodeC, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &nodeB);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &nodeC);
}