#include "unity.h"
#include "Define.h"
#include "StringObject.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void)  {}

void tearDown(void) {}

/* Valid if the character is start with '#' */
void test_searchDefine_shouldnt_throw_an_exception(void)
{
	String *str; 
  str = stringNew(" # ");
  
  searchDefine(str);
  
  stringDel(str);
}

/* Invalid if the character is not start with '#' */
void test_searchDefine_should_throw_an_exception(void)
{
	String *str; 
  CEXCEPTION_T err;
  
  Try {  
    str = stringNew(" & ");
    searchDefine(str);
    TEST_FAIL_MESSAGE("Should throw ERROR_INVALID_FORMAT exception");
  }
  Catch(err) {
    TEST_ASSERT_EQUAL_MESSAGE(ERROR_INVALID_FORMAT, err, "Expect ERROR_INVALID_FORMAT exception");
  }
  stringDel(str);
}

/* if the string is #define should return 1*/
void test_searchDefine_given_string_define_should_return_1(void)
{
  int result = 0;
	String *str; 
  str = stringNew(" #define");
  
  result = searchDefine(str);
  
  TEST_ASSERT_EQUAL(1, result);
  stringDel(str);
}

/* if the string is not #define should return -1*/
void test_searchDefine_given_string_abcd_should_return_negative_1(void)
{
  int result = 0;
	String *str; 
  str = stringNew(" #abcd ");
  
  result = searchDefine(str);
  
  TEST_ASSERT_EQUAL(-1, result);
  stringDel(str);
}