#include <malloc.h>
#include "unity.h"
#include "Preprocessor.h"
#include "StringObject.h"
#include "ErrorCode.h"
#include "CException.h"
#include "Macro.h"
#include "RedBlackTree.h"
#include "Node.h"
#include "Rotations.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "LinkedList.h"

void setUp(void)  {}

void tearDown(void) {}

/** test createMacroInfo() given string contain backslash '\' behind macro name
 **/
void Xtest_createMacroInfo_given_string_contain_backslash_behind_macroName_should_remove_backslash_can_get_macro_content(void)
{
	String *str = stringNew("Android\\\n"
                          "COC\n"
                          "X = AB");
  Macro *macro;

  printf("Start test_createMacroInfo_given_string_contain_backslash_behind_macroName_should_remove_backslash_can_get_macro_content\n");
  macro = createMacroInfo(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("Android", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("COC", macro->content->string); //empty content
  TEST_ASSERT_EQUAL(3, macro->content->length); //empty content

  delMacroNameAndContent(macro);
  stringDel(str);
}