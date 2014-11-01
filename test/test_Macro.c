#include "unity.h"
#include "Macro.h"
#include "StringObject.h"

void setUp(void)  {}

void tearDown(void) {}

void test_newMacro_given_name_A_and_content_123(void)
{
  Macro *macro = newMacro("A", "123");

  //Name
  TEST_ASSERT_EQUAL("A", macro->name->string);
  TEST_ASSERT_EQUAL(0, macro->name->startindex);
  TEST_ASSERT_EQUAL(1, macro->name->length);

  //Content
  TEST_ASSERT_EQUAL("123", macro->content->string);
  TEST_ASSERT_EQUAL(0, macro->content->startindex);
  TEST_ASSERT_EQUAL(3, macro->content->length);

  //free malloc
  macroDel(macro);
}
