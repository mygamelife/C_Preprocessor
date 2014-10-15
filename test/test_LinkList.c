#include "unity.h"
#include "LinkList.h"

void setUp(void)  {}

void tearDown(void) {}

void test_linkListNew(void)
{
	LinkList *link = linkListNew("ABC", "123");
  
  TEST_ASSERT_NOT_NULL(link);
  TEST_ASSERT_EQUAL_STRING("ABC", link->name);
  TEST_ASSERT_EQUAL_STRING("123", link->value);
  TEST_ASSERT_NULL(link->next);
  linkListDel(link);
}

void test_linkListNew_2(void)
{
	LinkList *link; 
  link = linkListNew("AB", "10");
  link = linkListNew("CD", "244");
  
  TEST_ASSERT_NOT_NULL(link);
  TEST_ASSERT_EQUAL_STRING("AB", link->name);
  TEST_ASSERT_EQUAL_STRING("10", link->value);
  TEST_ASSERT_NOT_NULL(link->next);
  TEST_ASSERT_EQUAL_STRING("CD", link->next->name);
  TEST_ASSERT_EQUAL_STRING("244", link->next->value);
  TEST_ASSERT_NULL(link->next->next);
  linkListDel(link);
}