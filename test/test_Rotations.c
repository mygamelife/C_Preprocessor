#include <stdio.h>
#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotations.h"

Node node1, node5, node6, node7, node8, node10, node15, node20, node30; //Share to all test

/* Run reset before test*/
void setUp(void)	{
	resetNode(&node1, 1);
	resetNode(&node5, 5);
	resetNode(&node6, 6);
	resetNode(&node7, 7);
	resetNode(&node8, 8);
	resetNode(&node10, 10);
	resetNode(&node15, 15);
	resetNode(&node20, 20);
	resetNode(&node30, 30);
}

void tearDown(void)	{}

/*
 * Root->  10               5  <-Root            
 *		    /               /  \
 *       5       --->    1   10
 *      /                  
 *     1                         
 *                                 
 */
void test_rightRotate_3_elements(void)	{
	setNode(&node1, NULL, NULL, 'b');
	setNode(&node5, &node1, NULL, 'b');
	setNode(&node10, &node5, NULL, 'b');
	Node *root = &node10;
	rightRotate(&root);
	printf("-----------------------------");
  
	TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
	TEST_ASSERT_EQUAL_PTR(node5.right, &node10);
	TEST_ASSERT_EQUAL_PTR(&node5, root);
}

/*
 * Root->  10                 5  <-Root            
 *		    /  \              /   \
 *       5   20    --->    1     10
 *      /                         \
 *     1                           20
 *                                 
 */
void test_rightRotate_4_elements(void)	{
	setNode(&node1, NULL, NULL, 'b');
	setNode(&node5, &node1, NULL, 'b');
	setNode(&node10, &node5, &node20, 'b');
	setNode(&node20, NULL, NULL, 'b');
	Node *root = &node10;
	
  printf("test_rightRotate_4_elements\n");
	rightRotate(&root);
	printf("-----------------------------");
  
	TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node20.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right, &node20);
	TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
	TEST_ASSERT_EQUAL_PTR(node5.right, &node10);
	TEST_ASSERT_EQUAL_PTR(root, &node5);
}

/*
 * Root->  10                 5  <-Root            
 *		    /  \              /  \
 *       5   20    --->    1    10
 *      / \                    /  \
 *     1   8                  8   20
 *                                 
 */
void test_rightRotate_5_elements(void)	{
	setNode(&node1, NULL, NULL, 'b');
	setNode(&node5, &node1, &node8, 'b');
	setNode(&node8, NULL, NULL, 'b');
	setNode(&node10, &node5, &node20, 'b');
	setNode(&node20, NULL, NULL, 'b');
	Node *root = &node10;
	
  printf("test_rightRotate_5_elements\n");
	rightRotate(&root);
	printf("-----------------------------");
  
	TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node8.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node8.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node20.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, &node8);
	TEST_ASSERT_EQUAL_PTR(node10.right, &node20);
	TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
	TEST_ASSERT_EQUAL_PTR(node5.right, &node10);
	TEST_ASSERT_EQUAL_PTR(root, &node5);
}

/*
 * Root->  1                   5    <-Root
 *          \                /  \
 *           5    -->       1    10
 *            \
 *             10                    
 */
void test_leftRotate_3_elements(void)	{
	setNode(&node10, NULL, NULL, 'b');
	setNode(&node5, NULL, &node10, 'b');
	setNode(&node1, NULL, &node5, 'b');
	Node *root = &node1;
	
  printf("test_leftRotate_3_elements\n");
	leftRotate(&root);
	printf("-----------------------------");
  
	TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
	TEST_ASSERT_EQUAL_PTR(node5.right, &node10);
	TEST_ASSERT_EQUAL_PTR(root, &node5);
}

/*
 * Root->   5                    10    <-Root
 *        /  \                 /   \
 *       1    10    --->     5      20
 *             \            / 
 *              20         1           
 */
void test_leftRotate_4_elements(void)	{
	setNode(&node1, NULL, NULL, 'b');
	setNode(&node20, NULL, NULL, 'b');
	setNode(&node10, NULL, &node20, 'b');
	setNode(&node5, &node1, &node10, 'b');
	Node *root = &node5;
	
  printf("test_leftRotate_4_elements\n");
	leftRotate(&root);
	printf("-----------------------------");
  
	TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
	TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node20.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, &node5);
	TEST_ASSERT_EQUAL_PTR(node10.right, &node20);
	TEST_ASSERT_EQUAL_PTR(root, &node10);
}

/*
 * Root->   5                     10    <-Root
 *        /  \                  /   \
 *       1    10    --->      5      20
 *           /  \            / \
 *         8     20         1   8        
 */
void test_leftRotate_5_elements(void)	{
	setNode(&node1, NULL, NULL, 'b');
	setNode(&node8, NULL, NULL, 'b');
	setNode(&node20, NULL, NULL, 'b');
	setNode(&node10, &node8, &node20, 'b');
	setNode(&node5, &node1, &node10, 'b');
	Node *root = &node5;
	
  printf("test_leftRotate_5_elements\n");
	leftRotate(&root);
	printf("-----------------------------");
  
	TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node8.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node8.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
	TEST_ASSERT_EQUAL_PTR(node5.right, &node8);
	TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node20.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, &node5);
	TEST_ASSERT_EQUAL_PTR(node10.right, &node20);
	TEST_ASSERT_EQUAL_PTR(root, &node10);
}

/*
 * Root->  10        Root->   10          Root->   7
 *        /                  /                   /  \ 
 *       5       -->        7      -->         5     10
 *     / \                 /
 *    -   7               5
 */
void test_leftRightRotate_3_elements(void)	{
	setNode(&node7, NULL, NULL, 'b');
	setNode(&node5, NULL, &node7, 'b');
	setNode(&node10, &node5, NULL, 'b');
	Node *root = &node10;
	
  printf("test_leftRightRotate_3_elements\n");
  leftRightRotate(&root);
	printf("-----------------------------");
  
	TEST_ASSERT_EQUAL_PTR(node5.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
	TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
	TEST_ASSERT_EQUAL_PTR(root, &node7);  
}

/*
 * Root->  10        Root->   10          Root->   7
 *        /                  /                   /  \ 
 *       5       -->        7      -->         5     10
 *     / \                 /                  /
 *    1   7               5                  1
 *                       /
 *                      1
 */
void test_leftRightRotate_4_elements(void)	{
	setNode(&node1, NULL, NULL, 'b');
	setNode(&node7, NULL, NULL, 'b');
	setNode(&node5, &node1, &node7, 'b');
	setNode(&node10, &node5, NULL, 'b');
	Node *root = &node10;
	
  printf("test_leftRightRotate_4_elements\n");
  leftRightRotate(&root);
	printf("-----------------------------");
  
	TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
	TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
	TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
	TEST_ASSERT_EQUAL_PTR(root, &node7);  
}

/*
 * Root->  10            Root->   10             Root->   7
 *        /  \                   / \                    /  \ 
 *       5    15   -->         7    15    -->         5     10
 *     /  \                   / \                   /      /  \
 *    1    7                5    8                1       8    15
 *          \              /
 *           8           1
 */
void test_leftRightRotate_6_elements_with_right_child(void)	{
	setNode(&node1, NULL, NULL, 'b');
	setNode(&node8, NULL, NULL, 'b');
	setNode(&node7, NULL, &node8, 'b');
	setNode(&node5, &node1, &node7, 'b');
	setNode(&node15, NULL, NULL, 'b');
	setNode(&node10, &node5, &node15, 'b');
	Node *root = &node10;
	
  printf("test_leftRightRotate_6_elements_with_right_child\n");
  leftRightRotate(&root);
	printf("-----------------------------");
  
	TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
	TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node8.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node8.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node15.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node15.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, &node8);
	TEST_ASSERT_EQUAL_PTR(node10.right, &node15);
  TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
	TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
	TEST_ASSERT_EQUAL_PTR(root, &node7);  
}

/*
 * Root->  10            Root->   10             Root->   7
 *        /  \                   / \                    /  \ 
 *       5    15   -->         7    15    -->         5     10
 *     /  \                   /                     /  \      \
 *    1    7                 5                    1     6      15
 *        /                /  \
 *       6               1     6
 */
void test_leftRightRotate_6_elements_with_left_child(void)	{
	setNode(&node1, NULL, NULL, 'b');
	setNode(&node6, NULL, NULL, 'b');
	setNode(&node7, &node6, NULL, 'b');
	setNode(&node5, &node1, &node7, 'b');
	setNode(&node15, NULL, NULL, 'b');
	setNode(&node10, &node5, &node15, 'b');
	Node *root = &node10;
	
  printf("test_leftRightRotate_6_elements_with_left_child\n");
  leftRightRotate(&root);
	printf("-----------------------------");
  
	TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node6.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node6.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
	TEST_ASSERT_EQUAL_PTR(node5.right, &node6);
  TEST_ASSERT_EQUAL_PTR(node15.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node15.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right, &node15);
  TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
	TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
	TEST_ASSERT_EQUAL_PTR(root, &node7);  
}

/*
 * Root->   5        Root->   5          Root->    7
 *           \                 \                 /  \ 
 *            10                7               5    10
 *           /                   \
 *          7                     10
 */
void test_rightLeftRotate_3_elements(void)	{
	setNode(&node7, NULL, NULL, 'b');
 	setNode(&node10, &node7, NULL, 'b');
	setNode(&node5, NULL, &node10, 'b');

	Node *root = &node5;
	
  printf("test_rightLeftRotate_3_elements\n");
  rightLeftRotate(&root);
	printf("-----------------------------");
  
	TEST_ASSERT_EQUAL_PTR(node5.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
	TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
	TEST_ASSERT_EQUAL_PTR(root, &node7);  
}

/*
 * Root->   5        Root->    5          Root->    7
 *         / \               /  \                 /  \ 
 *        1   20            1    7               5    20
 *           /  \                 \             /    /  \
 *          7    30                20          1    10  30
 *           \                    /  \
 *            10                10    30
 */
void test_rightLeftRotate_6_elements(void)	{
	setNode(&node1, NULL, NULL, 'b');
 	setNode(&node10, NULL, NULL, 'b');
	setNode(&node7, NULL, &node10, 'b');
	setNode(&node30, NULL, NULL, 'b');
	setNode(&node20, &node7, &node30, 'b');
	setNode(&node5, &node1, &node20, 'b');

	Node *root = &node5;
	
  printf("test_rightLeftRotate_3_elements\n");
  rightLeftRotate(&root);
	printf("-----------------------------");
  
	TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);  
	TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
	TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node30.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node30.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node20.left, &node10);
	TEST_ASSERT_EQUAL_PTR(node20.right, &node30);
	TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
	TEST_ASSERT_EQUAL_PTR(node7.right, &node20);  
	TEST_ASSERT_EQUAL_PTR(root, &node7);  
}