#include <malloc.h>
#include "unity.h"
#include "Macro.h"
#include "StringObject.h"

void setUp(void)  {}

void tearDown(void) {}

/** test newMacro given name "A" and content "123"
 *
 *    *macro  --> String *name    = "A"
 *            --> String *content = "123"
 */
void test_newMacro_given_name_A_and_content_123(void)
{
  Macro *macro = newMacro("A", "123", newMacroArgument(1));

  //Name
  TEST_ASSERT_EQUAL("A", macro->name->string);
  TEST_ASSERT_EQUAL(0, macro->name->startindex);
  TEST_ASSERT_EQUAL(1, macro->name->length);

  //Content
  TEST_ASSERT_EQUAL("123", macro->content->string);
  TEST_ASSERT_EQUAL(0, macro->content->startindex);
  TEST_ASSERT_EQUAL(3, macro->content->length);

  //Argument
  TEST_ASSERT_EQUAL(1, macro->argument->size);
  TEST_ASSERT_NULL(macro->argument->entries[0]);

  //free malloc
  delMacro(macro);
}

/* test newMacroArgument given arguments size
 */
void test_newMacroArgument_given_arguments_size_3(void)
{
  Argument *argu = newMacroArgument(3);

  TEST_ASSERT_EQUAL(3, argu->size);
  TEST_ASSERT_NULL(argu->entries[0]);

  //free malloc
  delMacroArgument(argu);
}

/* test newMacroArgument given arguments size
 */
void test_newMacroArgumentx_given_arguments_size_3(void)
{
  Argu *argu = newMacroArgu(3);

  TEST_ASSERT_EQUAL(3, argu->size);
  argu->entries[0]->name = stringNew("hello");

  printf("name %s\n", argu->entries[0]->name->string);
  printf("start %d\n", argu->entries[0]->name->startindex);
  printf("length %d\n", argu->entries[0]->name->length);

  argu->entries[1]->name = stringNew("Night");

  printf("name %s\n", argu->entries[1]->name->string);
  printf("start %d\n", argu->entries[1]->name->startindex);
  printf("length %d\n", argu->entries[1]->name->length);

    argu->entries[1]->value = stringNew("Morning");

  printf("name %s\n", argu->entries[1]->value->string);
  printf("start %d\n", argu->entries[1]->value->startindex);
  printf("length %d\n", argu->entries[1]->value->length);
  //free malloc
  // delMacroArgument(argu);
}