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

/** test macroPositionInString():
 ** macro :
 *          #define search Macro
 *
 ** String :
 *          X trying to search Macro;
 **/
void test_macroPositionInString_given_string_X_trying_to_search_Macro_should_get_search_macroInfo(void) // <----- Problem
{
	String *str = stringNew("#define search Macro\n"
                           "A = 999\n");
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
  stringDel(subString);
  stringDel(str);
}

void test_replaceMacroInString_given_TEN_in_string_should_replace_it_with_10(void) // <----- Problem
{
	String *str = stringNew("X = TEN;");
	String *subStr = stringSubString(str, 4, 3);
  Macro *macro = newMacro("TEN", "10");
  char *result;
  int size = size = (str->length) - (macro->name->length) + (macro->content->length);

  printf("Start test_replaceMacroInString_given_TEN_in_string_should_replace_it_with_10\n");
  result = replaceMacroInString(str, subStr, macro, size);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("X = 10;", result);

  subStringDel(result);
  delMacro(macro);
  stringDel(subStr);
  stringDel(str);
}

/** test directiveDefine() given string:
 *  #define Japan ABC
 *  #define ABC Ohaiyo
 *  S = Japan
 *
 ** result :
 *          S = Japan -->  S = ABC --> S = Ohaiyo
 **/
void test_directiveDefine_given_Japan_and_ABC_should_replace_Japan_with_Ohaiyo(void)
{
	String *str = stringNew("#define Japan ABC\n"
                          "#define ABC Ohaiyo\n"
                          "S = Japan\n");
  String *result;

  printf("Start test_directiveDefine_given_Japan_and_ABC_should_replace_Japan_with_Ohaiyo\n");
  result = directiveDefine(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("S = Ohaiyo", result->string);
  TEST_ASSERT_EQUAL(0, result->startindex);
  TEST_ASSERT_EQUAL(10, result->length);

  subStringDel(result->string);
  stringDel(result);
  stringDel(str);
}

/** test directiveDefine() given string:
 *  #define ONE 1
 *  #define TWO 2
 *  X = ONE + TWO
 *
 ** result :
 *          X = 1 + TWO
 *          X = 1 + 2
 **/
void test_directiveDefine_given_ONE_plus_ONE_should_replace_two_ONE_with_1(void)
{
	String *str = stringNew("#define ONE 1\n"
                          "#define TWO 2\n"
                          "#define Three 3\n"
                          "X = ONE + TWO + Three");
  String *result;

  printf("Start test_directiveDefine_given_ONE_plus_ONE_should_replace_two_ONE_with_1\n");
  result = directiveDefine(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("X = 1 + 2 + 3", result->string);
  TEST_ASSERT_EQUAL(0, result->startindex);
  TEST_ASSERT_EQUAL(13, result->length);

  subStringDel(result->string);
  stringDel(result);
  stringDel(str);
}

/** test directiveDefine() given string:
 *  #define blank
 *  #define _someth1ng #Sur prise
 *  S = blank * _someth1ng
 *
 ** result :
 *          S = blank * _someth1ng --> S =  * _someth1ng --> S =  * #Sur prise
 **/
void test_directiveDefine_should_replace_blank_with_empty_string_and_replace__something_with_sur_prise(void)
{
	String *str = stringNew("#define blank\n"
                          "#define _someth1ng #Sur prise\n"
                          "S = blank * _someth1ng");
  String *result;

  printf("Start test_directiveDefine_should_replace_blank_with_empty_string_and_replace__something_with_sur_prise\n");
  result = directiveDefine(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("S =  * #Sur prise", result->string);
  TEST_ASSERT_EQUAL(0, result->startindex);
  TEST_ASSERT_EQUAL(17, result->length);

  subStringDel(result->string);
  stringDel(result);
  stringDel(str);
}

/** test directiveDefine() given string:
 *  #define BES123 800X
 *  #define _Dumb _dumb2 + 3
 *  #define _dumb2 DUMB DUMB
 *
 *  Im BES123 * (xox + _Dumb)
 *
 ** result :
 *          Im 800X * (xox + DUMB DUMB + 3)
 **/
void Xtest_directiveDefine_given_BES123__Dumb__dumb2_should_replace_all_the_given_macro(void)
{
	String *str = stringNew("#define BES123 800X\n"
                          "#define _Dumb _dumb2 + 3\n"
                          "#define _dumb2 DUMB DUMB\n"
                          "Im BES123 * (xox + _Dumb)");
  String *result;

  printf("Start test_directiveDefine_given_BES123__Dumb__dumb2_should_replace_all_the_given_macro\n");
  result = directiveDefine(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("Im 800X * (xox + DUMB DUMB + 3)", result->string);
  TEST_ASSERT_EQUAL(0, result->startindex);
  TEST_ASSERT_EQUAL(31, result->length);

  subStringDel(result->string);
  stringDel(result);
  stringDel(str);
}

/** test directiveDefine() with cyclic problem (Happen in beginning):
 *  #define _MAX _MAX
 *
 *  A = _MAX
 **/
void Xtest_directiveDefine_with_cyclic_problem_happen_in_beginning(void)
{
	String *str = stringNew("#define _MAX _MAX\n"
                          "A = _MAX");
  String *result;

  printf("Start test_directiveDefine_with_cyclic_problem_happen_in_beginning\n");
  result = directiveDefine(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("A = _MAX", result->string);
  TEST_ASSERT_EQUAL(0, result->startindex);
  TEST_ASSERT_EQUAL(8, result->length);

  subStringDel(result->string);
  stringDel(result);
  stringDel(str);
}

/** test directiveDefine() with cyclic problem (Happen in end):
 *  #define _Sing Song
 *  #define Song _Sing
 *
 *  i _Sing
 **/
void Xtest_directiveDefine_with_cyclic_problem_02(void)
{
	String *str = stringNew("#define _Sing Song\n"
                          "#define Song _Sing\n"
                          "i _Sing");
  String *result;

  printf("Start test_directiveDefine_with_cyclic_problem_02\n");
  result = directiveDefine(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("i _Sing", result->string);
  TEST_ASSERT_EQUAL(0, result->startindex);
  TEST_ASSERT_EQUAL(7, result->length);

  subStringDel(result->string);
  stringDel(result);
  stringDel(str);
}

/** test directiveDefine() with cyclic problem:
 *  #define Start End
 *  #define End Start
 *  #define Cont $_$
 *
 *  Let's Start Cont
 **/
void Xtest_directiveDefine_with_cyclic_problem_03(void)
{
	String *str = stringNew("#define Start End\n"
                          "#define End Start\n"
                          "#define Cont $_$\n"
                          "Let's Start Cont");
  String *result;

  printf("Start test_directiveDefine_with_cyclic_problem_03\n");
  result = directiveDefine(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("Let's Start $_$", result->string);
  TEST_ASSERT_EQUAL(0, result->startindex);
  TEST_ASSERT_EQUAL(15, result->length);

  subStringDel(result->string);
  stringDel(result);
  stringDel(str);
}

/** test directiveDefine() with cyclic problem:
 **/
void Xtest_directiveDefine_with_multiple_cyclic_happen_problem_04(void)
{
	String *str = stringNew("#define Samuel Gay\n"
                          "#define Gay Samuel\n"
                          "#define VeryGay Samuel\n"
                          "#define Who Samuel\n"
                          "Who is Gay VeryGay");
  String *result;

  printf("Start test_directiveDefine_with_multiple_cyclic_happen_problem_04\n");
  result = directiveDefine(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("Samuel is Gay Samuel", result->string);
  TEST_ASSERT_EQUAL(0, result->startindex);
  TEST_ASSERT_EQUAL(20, result->length);

  subStringDel(result->string);
  stringDel(result);
  stringDel(str);
}