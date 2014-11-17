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

void setUp(void)  {}

void tearDown(void) {}

/** test isHashTag given # should return 1 **/
void test_isHashTag_given_hashtag_should_return_1(void)
{
  int result = 0;
	String *str = stringNew("#");

  result = isHashTag(str);

  TEST_ASSERT_EQUAL(1, result);
  stringDel(str);
}

/** test isHashTag given $ should return 1 **/
void test_isHashTag_given_dollarSign_should_return_0(void)
{
  int result = 0;
	String *str = stringNew("$");

  result = isHashTag(str);

  TEST_ASSERT_EQUAL(0, result);
  stringDel(str);
}

/** test isDirective given #define should return 1 **/
void test_isDirective_given_define_should_return_1(void)
{
  int result = 0;
	String *str = stringNew("#define");

  result = isDirective(str, "define");

  TEST_ASSERT_EQUAL(1, result);
  stringDel(str);
}

/** test isDirective given invalid symbol "!" should throw an error**/
void test_isDirective_should_throw_an_exception(void)
{
	String *str;
  CEXCEPTION_T err;

  Try {
    str = stringNew("!include");
    isDirective(str, "include");
    TEST_FAIL_MESSAGE("Should throw ERROR_INVALID_FORMAT exception");
  }
  Catch(err) {
    TEST_ASSERT_EQUAL_MESSAGE(ERR_INVALID_FORMAT, err, "Expect ERROR_INVALID_FORMAT exception");
  }
  stringDel(str);
}

/** test isDirective given "     #   define" space between # and directive name should return 1 **/
void test_isDirective_space_between_hashtag_and_directiveName_should_return_1(void)
{
  int result = 0;
	String *str = stringNew("     #   define");

  result = isDirective(str, "define");

  TEST_ASSERT_EQUAL(1, result);
  stringDel(str);
}

/** test isDirective given "   # in  clude" space at # and inside directive name should return 0 **/
void test_isDirective_space_between_hashtag_and_inside_directiveName_should_return_0(void)
{
  int result = 0;
	String *str = stringNew("   # in  clude");

  result = isDirective(str, "include");

  TEST_ASSERT_EQUAL(0, result);
  stringDel(str);
}

/** test isIdentifier given "_MAX_123" should return 1 **/
void test_isIdentifier_given__MAX_123_should_return_1(void)
{
  int result = 0;
	String *str = stringNew("_MAX_123");

  result = isIdentifier(str);

  TEST_ASSERT_EQUAL(1, result);
  stringDel(str);
}

/** test isIdentifier given "123MAX" should return 0 **/
void test_isIdentifier_given_123MAX_should_return_0(void)
{
  int result = 0;
	String *str = stringNew("123MAX");

  result = isIdentifier(str);

  TEST_ASSERT_EQUAL(0, result);
  stringDel(str);
}

/** test getMacroInfo() given
 *  name = "MAX"
 *  content = "100"
 *  macro pointer should contain all these information
 **/
void test_getMacroInfo_given_name_MAX_content_100_should_return_macro_pointer_with_these_info(void)
{
  int result = 0;
	String *str = stringNew("#define ABC 100");

  printf("Start test_getMacroInfo_given_name_MAX_content_100_should_return_macro_pointer_with_these_info\n");
  Macro *macro = getMacroInfo(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("ABC", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("100", macro->content->string);

  delMacro(macro);
  stringDel(str);
}