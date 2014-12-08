#include <stdio.h>
#include <string.h>
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

#define Something(ABC) "ABC.com"



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
  sizeOfArgu = getSizeOfArgu(str, alphaNumericSet);
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
  sizeOfArgu = getSizeOfArgu(str, alphaNumericSet);
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
  sizeOfArgu = getSizeOfArgu(str, alphaNumericSet);
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
    sizeOfArgu = getSizeOfArgu(str, alphaNumericSet);
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
  sizeOfArgu = getSizeOfArgu(str, alphaNumericSet);
  printf("start %d, length %d\n", str->startindex, str->length);
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
  sizeOfArgu = getSizeOfArgu(str, alphaNumericSet);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(1, sizeOfArgu);
  stringDel(str);
}

/** test getSizeOfArguInString() given non-identifier arguments with alphaNumericSetWithSymbol
 **/
void test_getSizeOfArguInString_given_nonIdentifier_arguments_should_get_the_size_of_arguments(void)
{
	String *str = stringNew("3_AX$ , ^920_AS, X_X)");
  int sizeOfArgu = 0;

  printf("Start test_getSizeOfArguInString_given_nonIdentifier_arguments_should_get_the_size_of_arguments\n");
  sizeOfArgu = getSizeOfArguInString(str, alphaNumericSetWithSymbolWithoutBracket);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(3, sizeOfArgu);
  stringDel(str);
}

/** test createMacroInfo() given argument list ( ABC ) should get the argument ABC
 **/
void test_createMacroArguments_given_argument_ABC_should_store_ABC(void)
{
	String *str = stringNew("( ABC )");
  Argument *argu;

  printf("Start test_createMacroArguments_given_argument_ABC_should_store_ABC\n");
  argu = createMacroArguments(str, alphaNumericSet);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(argu);
  TEST_ASSERT_EQUAL_STRING("ABC", argu->entries[0]->string);
  TEST_ASSERT_EQUAL(0, argu->entries[0]->startindex);
  TEST_ASSERT_EQUAL(3, argu->entries[0]->length);

  delMacroArgument(argu);
  stringDel(str);
}

/** test createMacroInfo() given argument list ( _X_Men, dragon, ball_ ) should get 3 arguments info
 **/
void test_createMacroArguments_given_X_Men_dragon_and_ball__3_argument_should_store_these_3_arguments(void)
{
	String *str = stringNew("( _X_Men, dragon, ball_ )");
  Argument *argu;

  printf("Start test_createMacroArguments_given_X_Men_dragon_and_ball__3_argument_should_store_these_3_arguments\n");
  argu = createMacroArguments(str, alphaNumericSet);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(argu);
  TEST_ASSERT_EQUAL_STRING("_X_Men", argu->entries[0]->string);
  TEST_ASSERT_EQUAL(0, argu->entries[0]->startindex);
  TEST_ASSERT_EQUAL(strlen(argu->entries[0]->string), argu->entries[0]->length);
  TEST_ASSERT_EQUAL_STRING("dragon", argu->entries[1]->string);
  TEST_ASSERT_EQUAL(0, argu->entries[1]->startindex);
  TEST_ASSERT_EQUAL(strlen(argu->entries[1]->string), argu->entries[1]->length);
  TEST_ASSERT_EQUAL_STRING("ball_", argu->entries[2]->string);
  TEST_ASSERT_EQUAL(0, argu->entries[2]->startindex);
  TEST_ASSERT_EQUAL(strlen(argu->entries[2]->string), argu->entries[2]->length);

  delMacroArgument(argu);
  stringDel(str);
}

/** test createMacroArguments() given argument list 0 should return NULL
 **/
void test_createMacroArguments_given_zero_argument_should_return_NULL(void)
{
	String *str = stringNew("()");
  Argument *argu = NULL;

  printf("Start test_createMacroArguments_given_zero_argument_should_return_NULL\n");
  argu = createMacroArguments(str, alphaNumericSet);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NULL(argu);

  delMacroArgument(argu);
  stringDel(str);
}

/** test createMacroInfo() given macroName with argument should store into macroInfo
 **/
void test_createMacroInfo_given_string_contain_macro_argument_should_store_into_macroInfo(void)
{
  String *str = stringNew("Add(X) a + x\n");
  Macro *macro;

  printf("Start test_createMacroInfo_given_string_contain_macro_argument_should_store_into_macroInfo\n");
  macro = createMacroInfo(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("Add", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("a + x", macro->content->string);
  TEST_ASSERT_EQUAL(1, macro->argument->size);
  TEST_ASSERT_EQUAL_STRING("X", macro->argument->entries[0]->string);
  TEST_ASSERT_EQUAL(0, macro->argument->entries[0]->startindex);
  TEST_ASSERT_EQUAL(1, macro->argument->entries[0]->length);

  //free all malloc memory in tree
  delMacroNameAndContent(macro);
  stringDel(str);
}

/** test createMacroInfo() given random identifier argument should store all inside macroInfo
 **/
void test_createMacroInfo_given_random_argument_should_store_all_if_it_is_identifier(void)
{
  String *str = stringNew("sum( _alien, boy123_ , _cat123 , dog_78)    alien +  boy_\n");
  Macro *macro;

  printf("Start test_createMacroInfo_given_random_argument_should_store_all_if_it_is_identifier\n");
  macro = createMacroInfo(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("sum", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("alien +  boy_", macro->content->string);
  TEST_ASSERT_EQUAL(4, macro->argument->size);
  TEST_ASSERT_EQUAL_STRING("_alien", macro->argument->entries[0]->string);
  TEST_ASSERT_EQUAL_STRING("boy123_", macro->argument->entries[1]->string);
  TEST_ASSERT_EQUAL_STRING("_cat123", macro->argument->entries[2]->string);
  TEST_ASSERT_EQUAL_STRING("dog_78", macro->argument->entries[3]->string);

  //free all malloc memory in tree
  delMacroNameAndContent(macro);
  stringDel(str);
}

/** test createMacroInfo() given random identifier argument but missing closed bracket should throw an error
 **/
void test_createMacroInfo_given_random_argument_but_missing_closed_bracket_should_throw_an_error(void)
{
  String *str;
  Macro *macro;
  CEXCEPTION_T err;

  printf("Start test_createMacroInfo_given_random_argument_but_missing_closed_bracket_should_throw_an_error\n");
  Try {
    str = stringNew("sum( b3by, boy123_  123 + b3by\n");
    macro = createMacroInfo(str);
    TEST_FAIL_MESSAGE("Should throw ERR_EXPECT_CLOSED_BRACKET exception");
  }
  Catch(err) {
    TEST_ASSERT_EQUAL_MESSAGE(ERR_EXPECT_CLOSED_BRACKET, err, "Expect ERR_EXPECT_CLOSED_BRACKET exception");
  }
  printf("------------------------------------------------------------\n");

  //free all malloc memory in tree
  stringDel(str);
}

/** test macroPositionInString() given sum(5) should get this macro position in it inside the tree
 **/
void test_macroPositionInString_given_string_sum_bracket_5_should_get_macro_position(void) // <----- Problem
{
	String *str = stringNew("#define sum(X) 10+X\n"
                           "sum(5)\n");
  String *subString;
  LinkedList *head = NULL;

  printf("Start test_macroPositionInString_given_string_sum_bracket_5_should_get_macro_position\n");
  Node *root = addAllMacroIntoTree(str, "define");
  subString = macroPositionInString(str, root);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(subString);
  TEST_ASSERT_EQUAL(20, subString->startindex);
  TEST_ASSERT_EQUAL(6, subString->length);

  destroyAllMacroInTree(root);
  stringDel(str);
}

/** test createMacroArguments() given stringStatement contain macro function with nonIdentifier arguments
 **/
void test_createNonIdentifierArgumentsInString_given_nonIdentifier_arguments_should_store_into_macroInfo(void)
{
  String *str = stringNew("sum(50)\n");
  Argument *argu;

  printf("Start test_createNonIdentifierArgumentsInString_given_nonIdentifier_arguments_should_store_into_macroInfo\n");
  stringSkip(str , 3);
  argu = createNonIdentifierArgumentsInString(str, alphaNumericSetWithSymbolWithoutBracket);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(argu);
  TEST_ASSERT_EQUAL_STRING("50", argu->entries[0]->string);
  TEST_ASSERT_EQUAL(0, argu->entries[0]->startindex);
  TEST_ASSERT_EQUAL(2, argu->entries[0]->length);
  TEST_ASSERT_EQUAL(7, str->startindex);
  TEST_ASSERT_EQUAL(1, str->length);

  //free all malloc memory in tree
  delMacroArgument(argu);
  stringDel(str);
}

/** test createMacroArguments() given stringStatement contain macro function with multiple random non-Identifier arguments
 **/
void test_createNonIdentifierArgumentsInString_given_multiple_nonIdentifier_arguments_should_store_into_macroInfo(void)
{
  String *str = stringNew("foooool(  #$%^, ABC @!!  , code_{++} \t)\n");
  Argument *argu;
  char a = 'a';
  printf("Start test_createNonIdentifierArgumentsInString_given_multiple_nonIdentifier_arguments_should_store_into_macroInfo\n");
  stringSkip(str , 7);
  argu = createNonIdentifierArgumentsInString(str, alphaNumericSetWithSymbolWithoutBracket);
  printf("------------------------------------------------------------\n");
  printf("%s\n", Something(a));
  TEST_ASSERT_NOT_NULL(argu);
  TEST_ASSERT_EQUAL_STRING("#$%^", argu->entries[0]->string);
  TEST_ASSERT_EQUAL(0, argu->entries[0]->startindex);
  TEST_ASSERT_EQUAL(4, argu->entries[0]->length);
  TEST_ASSERT_EQUAL_STRING("ABC @!!", argu->entries[1]->string);
  TEST_ASSERT_EQUAL(0, argu->entries[1]->startindex);
  TEST_ASSERT_EQUAL(6, argu->entries[1]->length);
  TEST_ASSERT_EQUAL_STRING("code_{++}", argu->entries[2]->string);
  TEST_ASSERT_EQUAL(0, argu->entries[2]->startindex);
  TEST_ASSERT_EQUAL(9, argu->entries[2]->length);
  TEST_ASSERT_EQUAL(34, str->startindex);
  TEST_ASSERT_EQUAL(1, str->length);

  //free all malloc memory in tree
  delMacroArgument(argu);
  stringDel(str);
}
