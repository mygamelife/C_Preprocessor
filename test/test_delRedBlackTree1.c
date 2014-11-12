#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotations.h"
#include "RedBlackTree.h"
#include "CustomAssertions.h"
#include "CException.h"
#include "ErrorCode.h"

Node node1, node2, node3, node4, node5, node6, node7, node8, node10, node13, node15,
     node20, node22, node30, node40, node60; //Share to all test

/* Run reset before test*/
void setUp(void)	{
	resetNode(&node1, 1);
	resetNode(&node2, 2);
	resetNode(&node3, 3);
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

/*test isDoubleBlack
 *  input : pass in root pointer
 *  output  : return 1 if it is 'd' color else return 0
 */
void test_isDoubleBlack_given_NULL_pointer_should_return_1(void) {
  Node *root = NULL;

  int result = isDoubleBlack(root);

  TEST_ASSERT_EQUAL(1, result);
}

void test_isDoubleBlack_given_node_with_doubleBlack_color_should_return_1(void) {
  setNode(&node10, NULL, NULL, 'd');
  Node *root = &node10;

  int result = isDoubleBlack(root);

  TEST_ASSERT_EQUAL(1, result);
}

/**case 1
 *          Root                                Root                                  Root
 *            |                                 |                                      |
 *            v                                 v                                      v
 *              /                                 /                                     /
 *          2(b)            remove 1            2(b)          left-rotate             4(b)
 *         /   \            ---->             //    \           ---->               /     \
 *      1(b)    4(b)                        (d)      4(b)                        2(b)      5(b)
 *                  \                                   \
 *                   5(r)                                5(r)
 *
 */
void test_delRedBlackTree_remove_1_from_tree_with_right_sibling_red_case1(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'r');
  setNode(&node4, NULL, &node5, 'b');
  setNode(&node2, &node1, &node4, 'b');
  Node *root, *result;
  root = &node2;

  printf("Start test_delRedBlackTree_remove_1_from_tree_with_right_sibling_red_case1\n");
  result = _delRedBlackTree(&root, &node1);
  printf("-------------------------------------------------------\n");

  TEST_ASSERT_EQUAL_PTR(&node1, result);
  TEST_ASSERT_EQUAL_PTR(&node4, root);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
}

/**case 1
 *          Root                                Root                                  Root
 *            |                                 |                                      |
 *            v                                 v                                      v
 *              /                                 /                                     /
 *          2(b)            remove 1            2(b)          right-left-rotate       4(b)
 *         /   \            ---->             //    \           ---->               /     \
 *      1(b)    5(b)                        (d)      5(b)                        2(b)      5(b)
 *             /                                    /
 *          4(r)                                4(r)
 *
 */
void test_delRedBlackTree_remove_1_from_tree_with_left_sibling_red_case1(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node4, NULL, NULL, 'r');
  setNode(&node5, &node4, NULL, 'b');
  setNode(&node2, &node1, &node5, 'b');
  Node *root, *result;
  root = &node2;

  printf("Start test_delRedBlackTree_remove_1_from_tree_with_left_sibling_red_case1\n");
  result = _delRedBlackTree(&root, &node1);
  printf("-------------------------------------------------------\n");

  TEST_ASSERT_EQUAL_PTR(&node1, result);

  TEST_ASSERT_EQUAL_PTR(&node4, root);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
}

/**case 1
 *                  Root                              Root                                  Root
 *                  |                                 |                                      |
 *                 v                                 v                                      v
 *                  /                                 /                                     /
 *               5(b)           remove 10           5(b)          right-rotate             2(b)
 *             /   \            ---->             /   \\           ---->                 /    \
 *         2(b)    10(b)                      2(b)     (d)                           1(b)      5(b)
 *        /                                   /
 *      1(r)                              1(r)
 *
 */
void test_delRedBlackTree_remove_10_from_tree_with_left_sibling_black_left_nephew_red_case1(void) {
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node2, &node1, NULL, 'b');
  setNode(&node10, NULL, NULL, 'b');
  setNode(&node5, &node2, &node10, 'b');
  Node *root, *result;
  root = &node5;

  printf("Start test_delRedBlackTree_remove_10_from_tree_with_left_sibling_black_left_nephew_red_case1\n");
  result = _delRedBlackTree(&root, &node10);
  printf("-------------------------------------------------------\n");

  TEST_ASSERT_EQUAL_PTR(&node10, result);

  TEST_ASSERT_EQUAL_PTR(&node2, root);
  TEST_ASSERT_EQUAL_NODE(&node1, &node5, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
}

/**case 1
 *                  Root                              Root                                  Root
 *                  |                                 |                                      |
 *                 v                                 v                                      v
 *                  /                                 /                                     /
 *               5(b)           remove 10           5(b)          left-right-rotate       2(b)
 *             /   \            ---->             /   \\           ---->                 /    \
 *         1(b)    10(b)                      1(b)     (d)                           1(b)      5(b)
 *            \                                  \
 *             2(r)                               2(r)
 *
 */
void test_delRedBlackTree_remove_10_from_tree_with_left_sibling_black_right_nephew_red_case1(void) {
  setNode(&node2, NULL, NULL, 'r');
  setNode(&node1, NULL, &node2, 'b');
  setNode(&node10, NULL, NULL, 'b');
  setNode(&node5, &node1, &node10, 'b');
  Node *root, *result;
  root = &node5;

  printf("Start test_delRedBlackTree_remove_10_from_tree_with_left_sibling_black_right_nephew_red_case1\n");
  result = _delRedBlackTree(&root, &node10);
  printf("-------------------------------------------------------\n");

  TEST_ASSERT_EQUAL_PTR(&node10, result);

  TEST_ASSERT_EQUAL_PTR(&node2, root);
  TEST_ASSERT_EQUAL_NODE(&node1, &node5, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
}

/**case 2
 *                  Root                              Root                                Root
 *                  |                                 |                                    |
 *                 v                                 v                                    v
 *                  /                                 /                                   //
 *               2(b)           remove 1            2(b)          colorFlip              2(d)
 *             /   \            ---->             //   \           ---->                    \
 *         1(b)     3(b)                        (d)     3(b)                                 3(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_both_siblings_and_nephews_are_black_case2(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'b');
  Node *root, *result;
  root = &node2;

  printf("Start test_delRedBlackTree_remove_1_from_tree_with_both_siblings_and_nephews_are_black_case2\n");
  result = _delRedBlackTree(&root, &node1);
  printf("-------------------------------------------------------\n");

  TEST_ASSERT_EQUAL_PTR(&node1, result);

  TEST_ASSERT_EQUAL_PTR(&node2, root);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'd', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
}

/**case 2
 *                  Root                              Root                                Root
 *                  |                                 |                                    |
 *                 v                                 v                                    v
 *                  /                                 /                                   //
 *               2(b)           remove 3            2(b)          colorFlip              2(d)
 *             /   \            ---->             /    \\           ---->               /
 *         1(b)     3(b)                       1(b)     (d)                         1(r)
 */
void test_delRedBlackTree_remove_3_from_tree_with_both_siblings_and_nephews_are_black_case2(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'b');
  Node *root, *result;
  root = &node2;

  printf("Start test_delRedBlackTree_remove_3_from_tree_with_both_siblings_and_nephews_are_black_case2\n");
  result = _delRedBlackTree(&root, &node3);
  printf("-------------------------------------------------------\n");

  TEST_ASSERT_EQUAL_PTR(&node3, result);

  TEST_ASSERT_EQUAL_PTR(&node2, root);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'd', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
}

/**case 2
 *                  Root                              Root                                Root
 *                  |                                 |                                    |
 *                 v                                 v                                    v
 *                  /                                 /                                     /
 *               2(r)           remove 1            2(r)          colorFlip              2(b)
 *             /   \            ---->             //    \           ---->                   \
 *         1(b)     3(b)                       (d)       3(b)                                3(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_both_siblings_and_nephews_are_black_case2b(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  Node *root, *result;
  root = &node2;

  printf("Start test_delRedBlackTree_remove_1_from_tree_with_both_siblings_and_nephews_are_black_case2b\n");
  result = _delRedBlackTree(&root, &node1);
  printf("-------------------------------------------------------\n");

  TEST_ASSERT_EQUAL_PTR(&node1, result);

  TEST_ASSERT_EQUAL_PTR(&node2, root);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
}

/**case 2
 *                  Root                              Root                                Root
 *                  |                                 |                                    |
 *                 v                                 v                                    v
 *                  /                                 /                                     /
 *               2(r)           remove 3            2(r)          colorFlip              2(b)
 *             /   \            ---->             /     \\           ---->              /
 *         1(b)     3(b)                       1(b)      (d)                         1(r)
 */
void test_delRedBlackTree_remove_3_from_tree_with_both_siblings_and_nephews_are_black_case2b(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  Node *root, *result;
  root = &node2;

  printf("Start test_delRedBlackTree_remove_3_from_tree_with_both_siblings_and_nephews_are_black_case2b\n");
  result = _delRedBlackTree(&root, &node3);
  printf("-------------------------------------------------------\n");

  TEST_ASSERT_EQUAL_PTR(&node3, result);

  TEST_ASSERT_EQUAL_PTR(&node2, root);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
}

/**case 3
 *                  Root                              Root                                Root                            Root
 *                  |                                 |                                    |                              |
 *                 v                                 v                                    v                               v
 *                  /                                 /                                  /                                  /
 *               2(b)           remove 1            2(b)          left-rotate          4(b)         Use Case 2            4(b)
 *             /   \            ---->            //     \           ---->            /    \           ---->            /      \
 *         1(b)     4(r)                       (d)       4(r)                    2(r)      5(b)                    2(b)        5(b)
 *                /     \                              /    \                   //   \                                \
 *             3(b)      5(b)                      3(b)      5(b)             (d)     3(b)                             3(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_siblings_red_case3(void) {
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node4, &node3, &node5, 'r');
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node2, &node1, &node4, 'b');
  Node *root, *result;
  root = &node2;

  printf("Start test_delRedBlackTree_remove_1_from_tree_with_siblings_red_case3\n");
  result = _delRedBlackTree(&root, &node1);
  printf("-------------------------------------------------------\n");

  TEST_ASSERT_EQUAL_PTR(&node1, result);

  TEST_ASSERT_EQUAL_PTR(&node4, root);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
}

/**case 3
 *                  Root                              Root                                Root                            Root
 *                  |                                 |                                    |                              |
 *                 v                                 v                                    v                               v
 *                 /                                 /                                    /                               /
 *              5(b)           remove 8             5(b)          right-rotate          2(b)         Use Case 2          2(b)
 *            /     \            ---->            /     \\           ---->            /    \           ---->           /     \
 *        2(r)       8(b)                     2(r)       (d)                      1(b)      5(r)                   1(b)       5(b)
 *      /     \                             /     \                                       /    \\                           /
 *  1(b)       3(b)                     1(b)       3(b)                               3(b)      (d)                     3(r)
 */
void test_delRedBlackTree_remove_8_from_tree_with_siblings_red_case3(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node8, NULL, NULL, 'b');
  setNode(&node5, &node2, &node8, 'b');
  Node *root, *result;
  root = &node5;

  printf("Start test_delRedBlackTree_remove_8_from_tree_with_siblings_red_case3\n");
  result = _delRedBlackTree(&root, &node8);
  printf("-------------------------------------------------------\n");

  TEST_ASSERT_EQUAL_PTR(&node8, result);

  TEST_ASSERT_EQUAL_PTR(&node2, root);
  TEST_ASSERT_EQUAL_NODE(&node1, &node5, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(&node3, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
}

/**case 3
 *                  Root                              Root                                Root                            Root
 *                  |                                 |                                    |                              |
 *                 v                                 v                                    v                               v
 *                 /                                 /                                    /                               /
 *              2(b)           remove 1             2(b)          left-rotate          5(b)         Use Case 1          5(b)
 *            /     \            ---->           //     \           ---->            /    \           ---->           /     \
 *        1(b)       5(r)                       (d)      5(r)                    2(r)      6(b)                   3(r)       6(b)
 *                 /     \                             /     \                      \                           /     \
 *             3(b)       6(b)                     3(b)       6(b)                   3(b)                   2(b)       4(b)
 *            /    \                              /   \                                 \
 *          -       4(r)                        -      4(r)                              4(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_siblings_red_case3b(void) {
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node4, NULL, NULL, 'r');
  setNode(&node3, NULL, &node4, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node5, &node3, &node6, 'r');
  setNode(&node2, &node1, &node5, 'b');
  Node *root, *result;
  root = &node2;

  printf("Start test_delRedBlackTree_remove_1_from_tree_with_siblings_red_case3b\n");
  result = _delRedBlackTree(&root, &node1);
  printf("-------------------------------------------------------\n");

  TEST_ASSERT_EQUAL_PTR(&node1, result);

  TEST_ASSERT_EQUAL_PTR(&node5, root);
  TEST_ASSERT_EQUAL_NODE(&node3, &node6, 'b', root);
  TEST_ASSERT_EQUAL_NODE(&node2, &node4, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node6);
}