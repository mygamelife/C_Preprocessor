#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotations.h"
#include "RedBlackTree.h"
#include "CustomAssertions.h"

Node node1, node4, node5, node6, node7, node8, node10, node13, node15,
     node20, node22, node30, node40, node60; //Share to all test

/* Run reset before test*/
void setUp(void)	{
	resetNode(&node1, 1);
	resetNode(&node4, 4);
	resetNode(&node5, 5);
	resetNode(&node6, 6);
	resetNode(&node7, 7);
	resetNode(&node8, 8);
	resetNode(&node10, 10);
	resetNode(&node13, 13);
	resetNode(&node15, 15);
	resetNode(&node20, 20);
	resetNode(&node22, 22);
	resetNode(&node30, 30);
	resetNode(&node40, 40);
	resetNode(&node60, 60);
}

void tearDown(void) {}

/*
 * Root->  NULL                10  <-Root
 *                add 10
 *                ---->
 */
void test_addRedBlackTree_add_10_to_empty_tree(void)	{
	setNode(&node10, NULL, NULL, 'r');
	Node *root = NULL;

	printf("Start test_addRedBlacTree_add_10_to_empty_tree\n");
	addRedBlackTree(&root, &node10);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node10);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
}

/*
 * Root->  	10(b)              		10(b)  <-Root
 *                  add 5        /
 *                  ---->     5(r)
 */
void test_addRedBlackTree_add_5_to_tree_with_root_10(void)	{
	setNode(&node10, NULL, NULL, 'b');
	setNode(&node5, NULL, NULL, 'r');
	Node *root = &node10;

	printf("Start test_addRedBlacTree_add_5_to_tree_with_root_10\n");
	addRedBlackTree(&root, &node5);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node10);

	TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node10);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
}

/*
 * Root->  	10(b)                 10(b)  <-Root
 *                  add 13            \
 *                  ---->               13(r)
 */
void test_addRedBlackTree_add_13_to_tree_with_root_10(void)	{
	setNode(&node10, NULL, NULL, 'b');
	setNode(&node13, NULL, NULL, 'r');
	Node *root = &node10;

	printf("Start test_addRedBlacTree_add_13_to_tree_with_root_10\n");
	addRedBlackTree(&root, &node13);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node10);

	TEST_ASSERT_EQUAL_NODE(NULL, &node13, 'b', &node10);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node13);
}

/*
 * Root->  	10(b)                     10(b)  <-Root                     10(b)  <-Root                             13(b) <-Root
 *              \         add 13          \             rotate right        \               rotate left         /     \
 *                15(r)   ---->	           15(r)          ---->               13(r)             ---->        10(r)    15(r)
 *                                        /                                       \          flip color
 *                                    13(r)                                         15(r)
 */
void test_addRedBlackTree_add_13_to_tree_with_root_10_and_right_child_15(void)	{
	setNode(&node13, NULL, NULL, 'r');
	setNode(&node15, NULL, NULL, 'r');
	setNode(&node10, NULL, &node15, 'b');
	Node *root = &node10;

	printf("Start test_addRedBlackTree_add_13_to_tree_with_root_10_and_right_child_15\n");
	addRedBlackTree(&root, &node13);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node13);

	TEST_ASSERT_EQUAL_NODE(&node10, &node15, 'b', &node13);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}

/*
 * Root->  	10(b)              		    10(b)  <-Root                   10(b)  <-Root                       8(b) <-Root
 *         /	         add 8     	   /							 rotate left		 /               rotate left        /   \
 *       5(r)      		 ---->	     5(r)        	       ---->       8(r)                ---->         5(r)    10(r)
 *                                  \    													/		               flip color
 *                                   8(r)												5(r)
 */
void test_addRedBlackTree_add_8_to_tree_with_root_10_and_left_child_5(void)	{
	setNode(&node8, NULL, NULL, 'r');
	setNode(&node5, NULL, NULL, 'r');
	setNode(&node10, &node5, NULL, 'b');
	Node *root = &node10;

	printf("Start test_addRedBlackTree_add_8_to_tree_with_root_10_and_left_child_5\n");
	addRedBlackTree(&root, &node8);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node8);

	TEST_ASSERT_EQUAL_NODE(&node5, &node10, 'b', &node8);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
}

/*
 * Root->  	8(b)              		  8(b)  <-Root                           10(b) <-Root
 *         	 \         add 20        \							 rotate left		     /   \
 *            10(r)		 ---->	        10(r)    	       ---->          8(r)    20(r)
 *                                  	\    					 flip color
 *                                     20(r)
 */
void test_addRedBlackTree_add_20_to_tree_with_root_8_and_right_child_10(void)	{
	setNode(&node20, NULL, NULL, 'r');
	setNode(&node10, NULL, NULL, 'r');
	setNode(&node8, NULL, &node10, 'b');
	Node *root = &node8;

	printf("Start test_addRedBlackTree_add_20_to_tree_with_root_8_and_right_child_10\n");
	addRedBlackTree(&root, &node20);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node10);

	TEST_ASSERT_EQUAL_NODE(&node8, &node20, 'b', &node10);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node8);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node20);
}

/*
 * Root->  	10(b)              		  10(b)  <-Root
 *         	/         add 20       /	\
 *       8(r)         ---->	     8(r)  20(r)
 *                   flip color
 *
 */
void test_addRedBlackTree_add_20_to_tree_with_root_10_and_left_child_8(void)	{
	setNode(&node8, NULL, NULL, 'r');
	setNode(&node20, NULL, NULL, 'r');
	setNode(&node10, &node8, NULL, 'b');
	Node *root = &node10;

	printf("Start test_addRedBlackTree_add_20_to_tree_with_root_10_and_left_child_8\n");
	addRedBlackTree(&root, &node20);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node10);

	TEST_ASSERT_EQUAL_NODE(&node8, &node20, 'b', &node10);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node8);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node20);
}

/*
 * Root->  	15(b)              		   10(b)  <-Root                          13(b)
 *         	/         add 5         /						      right rotate         /  \
 *       13(r)        ---->	      13(r)                  ---->           5(r)  15(r)
 *                               /   	  					    flip color
 *                              5(r)
 */
void test_addRedBlackTree_add_5_to_tree_with_root_15_and_left_child_13(void)	{
	setNode(&node13, NULL, NULL, 'r');
	setNode(&node5, NULL, NULL, 'r');
	setNode(&node15, &node13, NULL, 'b');
	Node *root = &node15;

	printf("Start test_addRedBlackTree_add_5_to_tree_with_root_15_and_left_child_13\n");
	addRedBlackTree(&root, &node5);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node13);

	TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node13);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}

/*
 * Root->  	13(b)              		   13(b)  <-Root
 *         	  \        add 5        /	 \
 *             15(r)   ---->	    5(r)  15(r)
 *
 */
void test_addRedBlackTree_add_5_to_tree_with_root_13_and_right_child_15(void)	{
	setNode(&node5, NULL, NULL, 'r');
	setNode(&node15, NULL, NULL, 'r');
	setNode(&node13, NULL, &node15, 'b');
	Node *root = &node13;

	printf("Start test_addRedBlackTree_add_5_to_tree_with_root_13_and_right_child_15\n");
	addRedBlackTree(&root, &node5);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node13);

	TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node13);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}

/* 4-node case
 *
 * Root->  	10(b)              		   10(b)  <-Root                          10(r)
 *         /	\        add 5        /	 \					     flip color          /  \
 *       8(r)  15(r)   ---->	    8(r)  15(r)            ---->          8(b)  15(b)
 *                               /                                     /
 *                             5(r)     													   5(r)
 */
void test_addRedBlackTree_add_5_to_tree_with_root_10_and_left_child_8_right_child_15(void)	{
	setNode(&node5, NULL, NULL, 'r');
	setNode(&node8, NULL, NULL, 'r');
	setNode(&node15, NULL, NULL, 'r');
	setNode(&node10, &node8, &node15, 'b');
	Node *root = &node10;

	printf("Start test_addRedBlackTree_add_5_to_tree_with_root_10_and_left_child_8_right_child_15\n");
	_addRedBlackTree(&root, &node5);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node10);

	TEST_ASSERT_EQUAL_NODE(&node8, &node15, 'r', &node10);
	TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node8);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
}

/* 4-node case
 *
 * Root->  	10(b)              		   10(b)  <-Root                          10(r)
 *         /	\        add 8        /	 \					     flip color          /  \
 *       5(r)  15(r)   ---->	    5(r)  15(r)            ---->          5(b)  15(b)
 *                                  \                                    \
 *                                  8(r)     													    8(r)
 */
void test_addRedBlackTree_add_8_to_tree_with_root_10_and_left_child_5_right_child_15(void)	{
	setNode(&node5, NULL, NULL, 'r');
	setNode(&node15, NULL, NULL, 'r');
	setNode(&node8, NULL, NULL, 'r');
	setNode(&node10, &node5, &node15, 'b');
	Node *root = &node10;

	printf("Start test_addRedBlackTree_add_8_to_tree_with_root_10_and_left_child_5_right_child_15\n");
	_addRedBlackTree(&root, &node8);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node10);

	TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'r', &node10);
	TEST_ASSERT_EQUAL_NODE(NULL, &node8, 'b', &node5);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node8);
}

/* 4-node case
 *
 * Root->  	8(b)              		     8(b)  <-Root                           8(r)
 *         /	\        add 10        /	 \					     flip color         /   \
 *       5(r)  20(r)   ---->	    5(r)    20(r)            ---->         5(b)    20(b)
 *                                       /                                      /
 *                                    10(r)   													    10(r)
 */
void test_addRedBlackTree_add_10_to_tree_with_root_8_and_left_child_5_right_child_20(void)	{
	setNode(&node10, NULL, NULL, 'r');
	setNode(&node5, NULL, NULL, 'r');
	setNode(&node20, NULL, NULL, 'r');
	setNode(&node8, &node5, &node20, 'b');
	Node *root = &node8;

	printf("Start test_addRedBlackTree_add_10_to_tree_with_root_8_and_left_child_5_right_child_20\n");
	_addRedBlackTree(&root, &node10);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node8);

	TEST_ASSERT_EQUAL_NODE(&node5, &node20, 'r', &node8);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
	TEST_ASSERT_EQUAL_NODE(&node10, NULL, 'b', &node20);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
}

/* 4-node case
 *
 * Root->  	8(b)              		     8(b)  <-Root                           8(r)
 *         /	\        add 30        /	 \					     flip color         /   \
 *       5(r)  20(r)   ---->	    5(r)    20(r)            ---->         5(b)    20(b)
 *                                           \                                     \
 *                                       			30(r)										              30(r)
 */
void test_addRedBlackTree_add_30_to_tree_with_root_8_and_left_child_5_right_child_20(void)	{
	setNode(&node30, NULL, NULL, 'r');
	setNode(&node5, NULL, NULL, 'r');
	setNode(&node20, NULL, NULL, 'r');
	setNode(&node8, &node5, &node20, 'b');
	Node *root = &node8;

	printf("Start test_addRedBlackTree_add_30_to_tree_with_root_8_and_left_child_5_right_child_20\n");
	_addRedBlackTree(&root, &node30);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node8);

	TEST_ASSERT_EQUAL_NODE(&node5, &node20, 'r', &node8);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
	TEST_ASSERT_EQUAL_NODE(NULL, &node30, 'b', &node20);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node30);
}

/* 4-node case
 *
 * Root->  	20(b)              		    20(b)  <-Root                         20(b)
 *         /	\        add 7        /	  \					     flip color         /    \
 *      10(b)  22(b)   ---->	    10(b)   22(b)         ---->         10(r)      22(b)
 *     /  \                      /   \                               /   \
 *  5(r)   15(r)               5(r)   15(r)                   		 5(b)   15(b)
 *                               \                                   \
 *                                7(r)                                7(r)
 */
void test_addRedBlackTree_add_7_to_tree_with_root_20_and_left_child_10_right_child_22(void)	{
	setNode(&node7, NULL, NULL, 'r');
	setNode(&node5, NULL, NULL, 'r');
	setNode(&node15, NULL, NULL, 'r');
	setNode(&node10, &node5, &node15, 'b');
	setNode(&node22, NULL, NULL, 'b');
	setNode(&node20, &node10, &node22, 'b');
	Node *root = &node20;

	printf("Start test_addRedBlackTree_add_7_to_tree_with_root_20_and_left_child_10_right_child_22\n");
	addRedBlackTree(&root, &node7);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node20);

	TEST_ASSERT_EQUAL_NODE(&node10, &node22, 'b', &node20);
	TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'r', &node10);
	TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node5);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node22);
}

/* 4-node case
 *            Root                                  Root
 *             |                                     |
 *             v                                     v
 *            20(b)                                20(b)                                          20(b)
 *           /	   \                             /      \                                       /       \
 *       4(r)       40(r)         add 7       4(r)        40(r)         flip color           4(b)         40(b)
 *     /   \        /   \         ---->      /   \       /    \           ---->             /   \        /   \
 *  1(b)    10(b) 30(b)  60(b)            1(b)    10(b) 30(b)  60(b)                     1(b)    10(r) 30(b)  60(b)
 *         /   \                                 /   \                                         /   \
 *       5(r)   15(r)                          5(r)   15(r)                                 5(b)    15(b)
 *                                               \                                             \
 *                                                7(r)                                          7(r)
 */
void test_addRedBlackTree_add_7_to_tree_with_root_20_and_left_child_4_right_child_40(void)	{
	setNode(&node7, NULL, NULL, 'r');
	setNode(&node5, NULL, NULL, 'r');
	setNode(&node15, NULL, NULL, 'r');
	setNode(&node1, NULL, NULL, 'b');
	setNode(&node30, NULL, NULL, 'b');
	setNode(&node60, NULL, NULL, 'b');
	setNode(&node10, &node5, &node15, 'b');
	setNode(&node4, &node1, &node10, 'r');
	setNode(&node40, &node30, &node60, 'r');
	setNode(&node20, &node4, &node40, 'b');
	Node *root = &node20;

	printf("Start test_addRedBlackTree_add_7_to_tree_with_root_20_and_left_child_10_right_child_22\n");
	addRedBlackTree(&root, &node7);
	printf("-----------------------------");

	TEST_ASSERT_EQUAL_PTR(root, &node20);

	TEST_ASSERT_EQUAL_NODE(&node4, &node40, 'b', &node20);
	TEST_ASSERT_EQUAL_NODE(&node1, &node10, 'b', &node4);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
	TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'r', &node10);
	TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node5);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
  TEST_ASSERT_EQUAL_NODE(&node30, &node60, 'b', &node40);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node30);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node60);
}

/* Remove RedBlackTree
 *
 * Root ->  1                 NULL
 *              ---->
 *            remove 1
 */
 void test_delRedBlackTree_remove_1_from_the_root(void) {
 
 }
 
 
 
 
 
 
 
 
 