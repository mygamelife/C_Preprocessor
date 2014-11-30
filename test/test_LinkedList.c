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