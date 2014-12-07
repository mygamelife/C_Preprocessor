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
/***************************************************************/
/**                                                           **/
/**  This TESTCODE is used to test define function as macro   **/
/**                                                           **/
/***************************************************************/

/** test getSizeOfArgu() given 1 arugment should return 1
 **/
void test_getSizeOfArgu_given_1_argument_should_return_1(void)
{
	String *str = stringNew("X");
  int sizeOfArgu = 0;

  printf("Start test_createMacroInfo_given_macroName_with_bracket_symbol\n");
  sizeOfArgu = getSizeOfArgu(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(1, sizeOfArgu);
  stringDel(str);
}

/** test getSizeOfArgu() given 2 arugment should return 2
 **/
void test_getSizeOfArgu_given_2_argument_should_return_2(void)
{
	String *str = stringNew("A,B");
  int sizeOfArgu = 0;

  printf("Start test_getSizeOfArgu_given_2_argument_should_return_2\n");
  sizeOfArgu = getSizeOfArgu(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(2, sizeOfArgu);
  stringDel(str);
}

/** test getSizeOfArgu() given multiple arugments should return 4
 **/
void test_getSizeOfArgu_given_multiple_arguments_should_return_4(void)
{
	String *str = stringNew("_two,_awesome,seven10,t3r3ssa");
  int sizeOfArgu = 0;

  printf("Start test_getSizeOfArgu_given_multiple_arguments_should_return_4\n");
  sizeOfArgu = getSizeOfArgu(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(4, sizeOfArgu);
  stringDel(str);
}

/** test getSizeOfArgu() given non-identifier arugments should throw an error
 **/
void test_getSizeOfArgu_given_nonIdentifier_arguments_should_throw_an_error(void)
{
	String *str;
  int sizeOfArgu = 0;
  CEXCEPTION_T err;
  
  printf("Start test_getSizeOfArgu_given_nonIdentifier_arguments_should_throw_an_error\n");
  
  Try {
    str = stringNew(" onlyOne, 123_max");
    sizeOfArgu = getSizeOfArgu(str);
    TEST_FAIL_MESSAGE("Should throw ERR_INVALID_IDENTIFIER exception");
  }
  Catch(err) {
    TEST_ASSERT_EQUAL_MESSAGE(ERR_INVALID_IDENTIFIER, err, "Expect ERR_INVALID_IDENTIFIER exception");
  }
  
  printf("------------------------------------------------------------\n");

  stringDel(str);
}

/** test getSizeOfArgu() given spaces between arugments should able to get the size
 **/
void test_getSizeOfArgu_given_spaces_between_arguments_should_able_to_get_the_size_of_argu(void)
{
	String *str = stringNew("  Maze      ,       runnerrr");
  int sizeOfArgu = 0;

  printf("Start test_getSizeOfArgu_given_spaces_between_arguments_should_able_to_get_the_size_of_argu\n");
  sizeOfArgu = getSizeOfArgu(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(2, sizeOfArgu);
  stringDel(str);
}

/** test getSizeOfArgu() given arguments end with symbol comma ',' should able to return size of arguments
 **/
void test_getSizeOfArgu_given_arguments_end_with_symbol_comma_should_return_size_of_arguments(void)
{
	String *str = stringNew("comma ,");
  int sizeOfArgu = 0;

  printf("Start test_getSizeOfArgu_given_arguments_end_with_symbol_comma_should_return_size_of_arguments\n");
  sizeOfArgu = getSizeOfArgu(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(1, sizeOfArgu);
  stringDel(str);
}

/** test createMacroInfo() given argument list ( ABC ) should get the argument ABC
 **/
void test_createMacroInfo_given_argument_ABC_should_store_ABC(void)
{
	String *str = stringNew("( ABC )");
  Argument *argu;

  printf("Start test_createMacroInfo_given_argument_ABC_should_store_ABC\n");
  argu = createMacroArguments(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(argu);
  TEST_ASSERT_EQUAL_STRING("ABC", argu->entries[0]->string);
  TEST_ASSERT_EQUAL(0, argu->entries[0]->startindex);
  TEST_ASSERT_EQUAL(3, argu->entries[0]->length);

  delMacroArgument(argu);
  stringDel(str);
}

/** test macroPositionInString():
 ** macro :
 *          #define Add(X) 10 + X
 *          Sum = Add(5)
 ** String :
 *          Search Something
 **/
void Xtest_macroPositionInString_given_Add_5_should_get_the_Add_5_position(void) // <----- Problem
{
	String *str = stringNew("#define Add(X) 10 + X\n"
                           "Sum = Add(5)");
  String *subString;
  LinkedList *head = NULL;

  printf("Start test_macroPositionInString_given_string_X_trying_to_search_Macro_should_get_search_macroInfo\n");
  Node *root = addAllMacroIntoTree(str, "define");
  subString = macroPositionInString(str, root);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(subString);
  TEST_ASSERT_EQUAL(0, subString->startindex);
  TEST_ASSERT_EQUAL(0, subString->length);

  destroyAllMacroInTree(root);
  stringDel(str);
}