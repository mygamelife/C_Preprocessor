#include "unity.h"
#include "Preprocessor.h"
#include "StringObject.h"
#include "LinkList.h"
#include "ErrorCode.h"
#include "CException.h"
void setUp(void)  {}

void tearDown(void) {}

/* Invalid if the character is not start with '#' */
void test_searchDirective_should_throw_an_exception(void)
{
	String *str; 
  CEXCEPTION_T err;
  
  Try {  
    str = stringNew(" & ");
    searchDirective(str, "define");
    TEST_FAIL_MESSAGE("Should throw ERROR_INVALID_FORMAT exception");
  }
  Catch(err) {
    TEST_ASSERT_EQUAL_MESSAGE(ERROR_INVALID_FORMAT, err, "Expect ERROR_INVALID_FORMAT exception");
  }
  stringDel(str);
}

/* if the string is #define should return 1*/
void test_searchDirective_given_string_define_should_return_1(void)
{
  int result = 0;
	String *str; 
  str = stringNew(" #define");
  
  result = searchDirective(str, "define");
  
  TEST_ASSERT_EQUAL(1, result);
  stringDel(str);
}

/* if the string is not #define should return -1*/
void test_searchDirective_given_string_abcd_should_return_negative_1(void)
{
  int result = 0;
	String *str; 
  str = stringNew(" # d e fine ");
  
  result = searchDirective(str, "define");
  
  TEST_ASSERT_EQUAL(-1, result);
  stringDel(str);
}

/* if the string is #include should return 1*/
void test_searchDirective_given_string_include_should_return_1(void)
{
  int result = 0;
	String *str; 
  str = stringNew(" #  include  ");
  
  result = searchDirective(str, "include");
  
  TEST_ASSERT_EQUAL(1, result);
  stringDel(str);
}

/* "ABC 10" ABC should contain in linkList->name and 10 in linklist->value */
void test_searchMacroName_given_define_ABC_macroName_should_contain_in_LinkList(void)
{
  int result = 0;
	String *str; LinkList *link; 
  str = stringNew("#define ABC 10");
  
  result = searchDirective(str, "define");
  TEST_ASSERT_EQUAL(1, result);
  TEST_ASSERT_EQUAL(7, str->startindex);
  
  link = searchMacro(str);
  TEST_ASSERT_EQUAL(14, str->startindex);
  TEST_ASSERT_EQUAL(0, str->length);
  TEST_ASSERT_EQUAL_STRING("ABC", link->name);
  TEST_ASSERT_EQUAL_STRING("10", link->value);
  TEST_ASSERT_NULL(link->next);
  
  linkListDel(link);
  stringDel(str);
}

/* "MAX 100"
 * "MIN 50"
 * linklist should contain this 2 information 
 */
void test_searchMacroName_given_MAX_100_and_MIN_50_should_contain_in_LinkList(void)
{
  int result = 0;
	String *str; LinkList *link; 
  str = stringNew("#define MAX 100\n"
                  "#define MIN 50\n");
  
  result = searchDirective(str, "define");
  TEST_ASSERT_EQUAL(1, result);
  TEST_ASSERT_EQUAL(7, str->startindex);

  link = searchMacro(str);
  TEST_ASSERT_EQUAL(15, str->startindex);
  TEST_ASSERT_EQUAL(16, str->length);
  TEST_ASSERT_EQUAL_STRING("MAX", link->name);
  TEST_ASSERT_EQUAL_STRING("100", link->value);
  TEST_ASSERT_NULL(link->next);
  
  linkListDel(link);
  stringDel(str);
}