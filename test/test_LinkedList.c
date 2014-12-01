#include "unity.h"
#include "LinkedList.h"

void setUp(void)  {}

void tearDown(void) {}

/** test linkListNew()
 ** Create a new list for linkedList and return the linkList pointer
 **/
void test_linkListNew_should_add_list_into_LinkedList(void) {
  char *name = "LinkList";
  LinkedList *link = linkListNew(name);

  TEST_ASSERT_NOT_NULL(link);
  char *result = (char*)link->data;
  TEST_ASSERT_NOT_NULL(link);
  TEST_ASSERT_EQUAL_STRING("LinkList", result);

  destroyAllLinkedLists(link);
}

/** test addLinkedList()
 ** Given one created newList should add into LinkedList
 *
 ** result  :
 *
 *                    After Add           ----------
 *     head-> NULL      --->      head-> | newList | -> NULL
 *                                       ----------
 **/
void test_addLinkedList_should_add_created_list_into_LinkedList(void) {
  char *name = "YOYO";
  LinkedList *head = NULL;
  LinkedList *newList = linkListNew(name);

  printf("Start test_addLinkedList_should_add_created_list_into_LinkedList\n");
  addLinkedList(&head, newList);
  printf("----------------------------------------------------------------");

  TEST_ASSERT_NOT_NULL(head);
  TEST_ASSERT_NULL(head->next);
  char *result = (char*)head->data;
  TEST_ASSERT_EQUAL_STRING("YOYO", result);

  destroyAllLinkedLists(head);
}

/** test addLinkedList()
 ** Given two created newList should add into LinkedList
 *
 ** result  :
 *
 *                    Add first                                   second
 *                      list              ----------              list              ----------     ----------
 *     head-> NULL      --->      head-> |  lsit1  | -> NULL      --->      head-> |  list1  | -> |  list2  | -> NULL
 *                                       ----------                                ----------     ----------
 *
 *                   Add third
 *                     list           ----------     ----------     ----------
 *                     --->  head->  |  list1  | -> |  list2  | -> |  list3  | -> NULL
 *                                   ----------     ----------     ----------
 **/
void test_addLinkedList_should_add_two_created_list_into_LinkedList(void) {
  char *name1 = "IM";
  char *name2 = "JUST";
  char *name3 = "LIST";

  LinkedList *head = NULL;
  LinkedList *list1 = linkListNew(name1);
  LinkedList *list2 = linkListNew(name2);
  LinkedList *list3 = linkListNew(name3);

  printf("Start test_addLinkedList_should_add_created_list_into_LinkedList\n");
  addLinkedList(&head, list1);

  TEST_ASSERT_NOT_NULL(head);
  TEST_ASSERT_NULL(head->next);
  char *result1 = (char*)head->data;
  TEST_ASSERT_EQUAL_STRING("IM", result1);

  addLinkedList(&head, list2);
  TEST_ASSERT_NOT_NULL(head->next);
  char *result2 = (char*)head->next->data;
  TEST_ASSERT_EQUAL_STRING("JUST", result2);

  addLinkedList(&head, list3);
  TEST_ASSERT_NOT_NULL(head->next->next);
  TEST_ASSERT_NULL(head->next->next->next);
  char *result3 = (char*)head->next->next->data;
  TEST_ASSERT_EQUAL_STRING("LIST", result3);

  printf("----------------------------------------------------------------");

  destroyAllLinkedLists(head);
}

/** test int compare(void *dataInCollection, void *targetData)
 ** Given 2 completely equal string should return 1
 **/
void test_compare_given_2_completely_equal_string_should_return_1(void) {
  char *name1 = "YOLO";
  char *name2 = "YOLO";
  int result = 0;

  printf("Start test_compare_given_2_completely_equal_string_should_return_1\n");
  result = compareChar(name1, name2);
  printf("----------------------------------------------------------------");

  TEST_ASSERT_EQUAL(1, result);
}

/** test int compare(void *dataInCollection, void *targetData)
 ** Given 2 different string should return 0
 **/
void test_compare_given_2_different_string_should_return_0(void) {
  char *name1 = "BYE";
  char *name2 = "HI";
  int result = 0;

  printf("Start test_compare_given_2_different_string_should_return_0\n");
  result = compareChar(name1, name2);
  printf("----------------------------------------------------------------");

  TEST_ASSERT_EQUAL(0, result);
}

/** test findLinkedList
 ** Given targetName "newName" should return 1
 **/
void test_findLinkedList_given_targetName_newName_should_return_1(void) {
  char *name = "newName";
  char *target = "newName";
  int result;
  LinkedList *head = NULL;
  LinkedList *newList = linkListNew(name);

  printf("Start test_findLinkedList_given_targetName_newName_should_return_1\n");
  addLinkedList(&head, newList);
  result = findList(&head, target);
  printf("----------------------------------------------------------------");

  TEST_ASSERT_EQUAL(1, result);
  destroyAllLinkedLists(head);
}

/** test findLinkedList
 ** Given targetName "name2" should return 1
 **/
void test_findLinkedList_given_target_name_name2_should_return_1(void) {
  char *name1 = "name1";
  char *name2 = "name2";
  char *name3 = "name3";
  char *target = "name2";
  int result = 0;
  LinkedList *head = NULL;
  LinkedList *list1 = linkListNew(name1);
  LinkedList *list2 = linkListNew(name2);
  LinkedList *list3 = linkListNew(name3);

  printf("test_findLinkedList_given_target_name_name2_should_return_1\n");
  addLinkedList(&head, list1);
  addLinkedList(&head, list2);
  addLinkedList(&head, list3);
  result = findList(&head, target);
  printf("----------------------------------------------------------------");

  TEST_ASSERT_EQUAL(1, result);
  destroyAllLinkedLists(head);
}

/** test findLinkedList
 ** Given target name doesnt exist in LinkedList should return 0
 **/
void test_findLinkedList_given_target_name_doesnt_exist_in_LinkedList_should_return_0(void) {
  char *name1 = "Oh";
  char *name2 = "Yeah";
  char *name3 = "Baby~";
  char *target = "What!?";
  int result = 0;
  LinkedList *head = NULL;
  LinkedList *list1 = linkListNew(name1);
  LinkedList *list2 = linkListNew(name2);
  LinkedList *list3 = linkListNew(name3);

  printf("test_findLinkedList_given_target_name_doesnt_exist_in_LinkedList_should_return_0\n");
  addLinkedList(&head, list1);
  addLinkedList(&head, list2);
  addLinkedList(&head, list3);
  result = findList(&head, target);
  printf("----------------------------------------------------------------");

  TEST_ASSERT_EQUAL(0, result);
  destroyAllLinkedLists(head);
}