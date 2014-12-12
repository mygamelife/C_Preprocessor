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
  TEST_ASSERT_EQUAL_STRING("ABC", argu->entries[0]->name->string);
  TEST_ASSERT_EQUAL(0, argu->entries[0]->name->startindex);
  TEST_ASSERT_EQUAL(3, argu->entries[0]->name->length);

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
  TEST_ASSERT_EQUAL_STRING("_X_Men", argu->entries[0]->name->string);
  TEST_ASSERT_EQUAL_STRING("dragon", argu->entries[1]->name->string);
  TEST_ASSERT_EQUAL_STRING("ball_", argu->entries[2]->name->string);

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

  TEST_ASSERT_NOT_NULL(argu);
  TEST_ASSERT_EQUAL(0, argu->size);

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
  TEST_ASSERT_EQUAL_STRING("X", macro->argument->entries[0]->name->string);
  TEST_ASSERT_EQUAL(0, macro->argument->entries[0]->name->startindex);
  TEST_ASSERT_EQUAL(1, macro->argument->entries[0]->name->length);

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
  TEST_ASSERT_EQUAL_STRING("_alien", macro->argument->entries[0]->name->string);
  TEST_ASSERT_EQUAL_STRING("boy123_", macro->argument->entries[1]->name->string);
  TEST_ASSERT_EQUAL_STRING("_cat123", macro->argument->entries[2]->name->string);
  TEST_ASSERT_EQUAL_STRING("dog_78", macro->argument->entries[3]->name->string);

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

void test_createMacroInfo_given_string_contain_space_between_name_and_argument_shouldnt_get_any_argument(void)
{
  String *str = stringNew("min_max (high ,  low) abc\n");
  Macro *macro;

  printf("Start test_createMacroInfo_given_string_contain_space_between_name_and_argument_shouldnt_get_any_argument\n");
  macro = createMacroInfo(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("min_max", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("(high ,  low) abc", macro->content->string);

  //free all malloc memory in tree
  delMacroNameAndContent(macro);
  stringDel(str);
}

/** test verifyRedifineArguments() given redefined macro arguments should return 1
 **/
void test_verifyRedifineArguments_given_redefined_macro_argument_should_return_1(void)
{
  String *str = stringNew("dota2(creep, creep) GGWP\n");
  Macro *macro = NULL;
  int result = 0;

  printf("Start test_verifyRedifineArguments_given_redefined_macro_argument_should_return_1\n");
  macro = createMacroInfo(str);
  result = verifyRedifineArguments(macro);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(1, result);
  //free all malloc memory in tree
  delMacroNameAndContent(macro);
  stringDel(str);
}

/** test verifyRedifineArguments() given redefined macro arguments should return 1
 **/
void test_verifyRedifineArguments_given_multiple_arguments_should_able_verify_redefined_macro_and_return_1(void)
{
  String *str = stringNew("hero(cm, ta, dk, ta, golem) GGWP\n");
  Macro *macro = NULL;
  int result = 0;

  printf("Start test_verifyRedifineArguments_given_multiple_arguments_should_able_verify_redefined_macro_and_return_1\n");
  macro = createMacroInfo(str);
  result = verifyRedifineArguments(macro);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(1, result);
  //free all malloc memory in tree
  delMacroNameAndContent(macro);
  stringDel(str);
}

/** test verifyRedifineArguments() given each unique macro arguments should return 0
 **/
void test_verifyRedifineArguments_given_each_unique_arguments_should_return_0(void)
{
  String *str = stringNew("Alphabets(X, Y, Z, A) alpha\n");
  Macro *macro = NULL;
  int result = 0;

  printf("Start test_verifyRedifineArguments_given_each_unique_arguments_should_return_0\n");
  macro = createMacroInfo(str);
  result = verifyRedifineArguments(macro);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(0, result);
  //free all malloc memory in tree
  delMacroNameAndContent(macro);
  stringDel(str);
}

/** test directiveDefine() redefined macro arguments
 **/
void test_addAllMacroIntoTree_given_redefined_macro_argument_should_throw_error(void)
{
  String *str;
	Node *root = NULL;
  CEXCEPTION_T err;

  printf("Start test_addAllMacroIntoTree_given_redefined_macro_argument_should_throw_error\n");
  Try {
    str = stringNew("#define Baymax(hero ,bay ,max ,hero) BigHero6\n");
    root = addAllMacroIntoTree(str, "define");
    TEST_FAIL_MESSAGE("Should throw ERR_MACRO_ARGUMENTS_REDEFINED exception");
  }
  Catch(err)  {
    TEST_ASSERT_EQUAL_MESSAGE(ERR_MACRO_ARGUMENTS_REDEFINED, err, "Expect ERR_MACRO_ARGUMENTS_REDEFINED exception");
    TEST_ASSERT_NULL(root);
  }
  printf("------------------------------------------------------------\n");

  //free all malloc memory in tree
  destroyAllMacroInTree(root);
  stringDel(str);
}

/** test createMacroInfo() given macroName with argument size zero
 **/
void test_createMacroInfo_given_string_contain_macro_argument_size_zero_should_store_into_macroInfo(void)
{
  String *str = stringNew("Hungry() eat\n");
  Macro *macro;

  printf("Start test_createMacroInfo_given_string_contain_macro_argument_size_zero_should_store_into_macroInfo\n");
  macro = createMacroInfo(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("Hungry", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("eat", macro->content->string);
  TEST_ASSERT_EQUAL(0, macro->argument->size);

  //free all malloc memory in tree
  delMacroNameAndContent(macro);
  stringDel(str);
}

/** test modifyMacroPositionWithArguments() given sum(5) should get this macro position in it inside the tree
 **/
void test_modifyMacroPositionWithArguments_given_string_sum_bracket_5_should_get_macro_position(void)
{
	String *str = stringNew("#define sum(X) 10+X\n");
  String *str2 = stringNew("sum(5)\n");

  printf("Start test_modifyMacroPositionWithArguments_given_string_sum_bracket_5_should_get_macro_position\n");
  Node *root = addAllMacroIntoTree(str, "define");
  Macro *foundMacro = findMacroInTree(root, "sum");
  String *subString = getMacroPositionInString(str2, root);
  modifyMacroPositionWithArguments(subString, foundMacro);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(subString);
  TEST_ASSERT_EQUAL(0, subString->startindex);
  TEST_ASSERT_EQUAL(6, subString->length);

  destroyAllMacroInTree(root);
  stringDel(subString);
  stringDel(str);
}

void test_modifyMacroPositionWithArguments_given_statement_with_argument_should_get_the_position(void)
{
	String *str = stringNew("#define mult(A, B) A*B\n");
  String *str2 = stringNew("Ans = mult(A, B) + 4\n");

  printf("Start test_modifyMacroPositionWithArguments_given_statement_with_argument_should_get_the_position\n");
  Node *root = addAllMacroIntoTree(str, "define");
  Macro *foundMacro = findMacroInTree(root, "mult");
  String *subString = getMacroPositionInString(str2, root);
  modifyMacroPositionWithArguments(subString, foundMacro);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(subString);
  TEST_ASSERT_EQUAL(6, subString->startindex);
  TEST_ASSERT_EQUAL(10, subString->length);

  destroyAllMacroInTree(root);
  stringDel(str);
}

/*  Given macroName with argument but string statement don't have argument should throw an error
 */
void test_storeArgumentsInString_given_macroName_with_arguments_but_statement_dont_have_argument_should_throw_an_error(void)
{
  String *str;
  String *str2;
  String *macroSubString;
  Macro *foundMacro;
  Node *root;
  CEXCEPTION_T err;

  printf("Start test_storeArgumentsInString_given_macroName_with_arguments_but_statement_dont_have_argument_should_throw_an_error\n");
  Try {
    str = stringNew("#define random()\n");
    str2 = stringNew("random % 88");
    root = addAllMacroIntoTree(str, "define");
    foundMacro = findMacroInTree(root, "random");
    macroSubString = getMacroPositionInString(str2, root);
    storeArgumentsInString(str2, foundMacro);
    TEST_FAIL_MESSAGE("Should throw ERR_EXPECT_ARGUMENT exception");
  }
  Catch(err)  {
    TEST_ASSERT_EQUAL_MESSAGE(ERR_EXPECT_ARGUMENT, err, "Expect ERR_EXPECT_ARGUMENT exception");
  }
  printf("------------------------------------------------------------\n");

  destroyAllMacroInTree(root);
  stringDel(macroSubString);
  stringDel(str);
  stringDel(str2);
}

void test_storeArgumentsInString_given_macroName_without_arguments_but_statement_with_argument_should_throw_an_error(void)
{
  String *str;
  String *str2;
  String *macroSubString;
  Macro *foundMacro;
  Node *root;
  CEXCEPTION_T err;

  printf("Start test_storeArgumentsInString_given_macroName_without_arguments_but_statement_with_argument_should_throw_an_error\n");
  Try {
    str = stringNew("#define PoweRanger\n");
    str2 = stringNew("random * PoweRanger()");
    root = addAllMacroIntoTree(str, "define");
    foundMacro = findMacroInTree(root, "PoweRanger");
    macroSubString = getMacroPositionInString(str2, root);
    storeArgumentsInString(str2, foundMacro);
    TEST_FAIL_MESSAGE("Should throw ERR_EXPECT_NO_ARGUMENT exception");
  }
  Catch(err)  {
    TEST_ASSERT_EQUAL_MESSAGE(ERR_EXPECT_NO_ARGUMENT, err, "Expect ERR_EXPECT_NO_ARGUMENT exception");
  }
  printf("------------------------------------------------------------\n");

  destroyAllMacroInTree(root);
  stringDel(macroSubString);
  stringDel(str);
  stringDel(str2);
}

void test_storeArgumentsInString_given_statement_with_argument_should_store_into_argument_value(void)
{
	String *str = stringNew("#define max(A , B) A + B\n");
  String *str2 = stringNew("max(100, 2000)");
  String *macroSubString;
  Macro *foundMacro;

  printf("Start test_storeArgumentsInString_given_statement_with_argument_should_store_into_argument_value\n");
  Node *root = addAllMacroIntoTree(str, "define");
  foundMacro = findMacroInTree(root, "max");
  macroSubString = getMacroPositionInString(str2, root);
  storeArgumentsInString(str2, foundMacro);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(foundMacro);
  TEST_ASSERT_EQUAL(2, foundMacro->argument->size);
  TEST_ASSERT_EQUAL_STRING("100", foundMacro->argument->entries[0]->value->string);
  TEST_ASSERT_EQUAL_STRING("2000", foundMacro->argument->entries[1]->value->string);

  destroyAllMacroInTree(root);
  stringDel(macroSubString);
  stringDel(str);
  stringDel(str2);
}

void test_storeArgumentsInString_given_statement_with_mismatch_argument_size_should_throw_an_error(void)
{
	String *str;
  String *str2;
  String *macroSubString;
  Macro *foundMacro;
  Node *root;
  CEXCEPTION_T err;

  printf("Start test_storeArgumentsInString_given_statement_with_mismatch_argument_size_should_throw_an_error\n");
  Try {
    str = stringNew("#define test(_A32, SS2, mon3y) A + B\n");
    str2 = stringNew("test(#24, ^7&, *88%, @#$, ())");
    root = addAllMacroIntoTree(str, "define");
    foundMacro = findMacroInTree(root, "test");
    macroSubString = getMacroPositionInString(str2, root);
    storeArgumentsInString(str2, foundMacro);
    TEST_FAIL_MESSAGE("Should throw ERR_MISMATCH_ARGUMENT_SIZE exception");
  }
  Catch(err)  {
    TEST_ASSERT_EQUAL_MESSAGE(ERR_MISMATCH_ARGUMENT_SIZE, err, "Expect ERR_MISMATCH_ARGUMENT_SIZE exception");
  }
  printf("------------------------------------------------------------\n");

  destroyAllMacroInTree(root);
  stringDel(macroSubString);
  stringDel(str);
  stringDel(str2);
}

void test_storeArgumentsInString_given_statement_with_closed_bracket_inside_argument_should_store_into_argument_value(void)
{
	String *str = stringNew("#define kanji(Oracle, ohaiyo) orange\n");
  String *str2 = stringNew("kanji(&_&,^_^))+432");
  String *macroSubString;
  Macro *foundMacro;

  printf("Start test_storeArgumentsInString_given_statement_with_closed_bracket_inside_argument_should_store_into_argument_value\n");
  Node *root = addAllMacroIntoTree(str, "define");
  foundMacro = findMacroInTree(root, "kanji");
  macroSubString = getMacroPositionInString(str2, root);
  storeArgumentsInString(str2, foundMacro);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(foundMacro);
  TEST_ASSERT_EQUAL(2, foundMacro->argument->size);
  TEST_ASSERT_EQUAL_STRING("&_&", foundMacro->argument->entries[0]->value->string);
  TEST_ASSERT_EQUAL_STRING("^_^", foundMacro->argument->entries[1]->value->string);

  destroyAllMacroInTree(root);
  stringDel(macroSubString);
  stringDel(str);
  stringDel(str2);
}

/** test storeArgumentsInString() given arguments with spaces
 **/
void test_storeArgumentsInString_given_arguments_with_spaces(void)
{
  String *str = stringNew("#define foooool(So, Ra, Aoi)");
  String *str2 = stringNew("foooool(  #$%^, ABC @!!  , code_{++} \t)\n");
  String *macroSubString;
  Macro *foundMacro;
  Node *root;
  CEXCEPTION_T err;

  printf("Start test_storeArgumentsInString_given_statement_with_closed_bracket_inside_argument_should_store_into_argument_value\n");
  Try {
    str = stringNew("#define foooool(So, Ra, Aoi)");
    str2 = stringNew("foooool(  #$%^, ABC @!!  , code_{++} \t)\n");
    root = addAllMacroIntoTree(str, "define");
    foundMacro = findMacroInTree(root, "foooool");
    macroSubString = getMacroPositionInString(str2, root);
    storeArgumentsInString(str2, foundMacro);
    TEST_FAIL_MESSAGE("Should throw ERR_MISMATCH_ARGUMENT_SIZE exception");
  }
  Catch(err)  {
    TEST_ASSERT_EQUAL_MESSAGE(ERR_MISMATCH_ARGUMENT_SIZE, err, "Expect ERR_MISMATCH_ARGUMENT_SIZE exception");
  }
  printf("------------------------------------------------------------\n");

  destroyAllMacroInTree(root);
  stringDel(macroSubString);
  stringDel(str);
  stringDel(str2);
}

void test_replaceMacroInString_given_statement_and_macro_with_argument(void)
{
	String *str = stringNew("#define divide(A) A/123\n");
  String *latestString = stringNew("total = divide(5) && OMG");
  char *replacedMacroString;
  int size;

  printf("Start test_replaceMacroInString_given_statement_and_macro_with_argument\n");
  Node *root = addAllMacroIntoTree(str, "define");
  Macro *foundMacro = findMacroInTree(root, "divide");
  String *macroSubString = getMacroPositionInString(latestString, root);
  modifyMacroPositionWithArguments(macroSubString, foundMacro);
  size = strlen(latestString->string) - macroSubString->length + (foundMacro->content->length);
  storeArgumentsInString(latestString, foundMacro);
  replacedMacroString = replaceMacroInString(latestString, macroSubString, foundMacro, size);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(replacedMacroString);
  TEST_ASSERT_EQUAL_STRING("total = A/123 && OMG", replacedMacroString);

  subStringDel(replacedMacroString);
  stringDel(latestString);
  stringDel(str);
}

void test_replaceMacroInString_given_statement_with_multiple_arguments(void)
{
	String *str = stringNew("#define getRandom(Apples, _Dog, XMEN, _Spiderman, _DragonClaw, _Pudge_X, Fire_in_, The_hol3) \\\n"
                          "_Spiderman, XMEN and _Pudge_X eating Apples\n");
  String *latestString = stringNew("Just getRandom(A%%, B^B, C*, $D, E*@, Code, Fun, AsAlways) for Fun");
  char *replacedMacroString;
  int size;

  printf("Start test_replaceMacroInString_given_statement_with_multiple_arguments\n");
  Node *root = addAllMacroIntoTree(str, "define");
  Macro *foundMacro = findMacroInTree(root, "getRandom");
  String *macroSubString = getMacroPositionInString(latestString, root);
  modifyMacroPositionWithArguments(macroSubString, foundMacro);
  size = strlen(latestString->string) - macroSubString->length + (foundMacro->content->length);
  storeArgumentsInString(latestString, foundMacro);
  replacedMacroString = replaceMacroInString(latestString, macroSubString, foundMacro, size);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(replacedMacroString);
  TEST_ASSERT_EQUAL_STRING("Just _Spiderman, XMEN and _Pudge_X eating Apples for Fun", replacedMacroString);

  subStringDel(replacedMacroString);
  stringDel(latestString);
  stringDel(str);
}

void test_replaceArgumentsInString_given_statement_with_arguments_should_replace_the_argument(void)
{
	String *str = stringNew("#define divide(A) A/123\n");
  String *latestString = stringNew("total = divide(99) && OMG");
  char *replacedArgumentsString, *replacedMacroString;
  int size;

  printf("Start test_replaceArgumentsInString_given_statement_with_arguments_should_replace_the_argument\n");
  Node *root = addAllMacroIntoTree(str, "define");
  Macro *foundMacro = findMacroInTree(root, "divide");
  String *macroSubString = getMacroPositionInString(latestString, root);
  storeArgumentsInString(latestString, foundMacro);
  modifyMacroPositionWithArguments(macroSubString, foundMacro);
  size = strlen(latestString->string) - macroSubString->length + (foundMacro->content->length);
  replacedMacroString = replaceMacroInString(latestString, macroSubString, foundMacro, size);
  String *str2 = stringNew(replacedMacroString);
  String *argumentSubString = stringRemoveWordContaining(str2 , foundMacro->argument->entries[0]->name->string);
  // total = A/123 && OMG
  size = strlen(str2->string) - argumentSubString->length + foundMacro->argument->entries[0]->value->length;
  replacedArgumentsString = replaceArgumentsInString(str2, argumentSubString, foundMacro->argument->entries[0]->value->string, size);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(replacedArgumentsString);
  TEST_ASSERT_EQUAL_STRING("total = 99/123 && OMG", replacedArgumentsString);

  subStringDel(replacedMacroString);
  subStringDel(replacedArgumentsString);
  stringDel(argumentSubString);
  stringDel(latestString);
  stringDel(str2);
  stringDel(str);
}

void test_searchAndReplaceArgumentsInString_given_statement_with_multiple_arguments_should_replace_all_the_arguments(void)
{
	String *str = stringNew("#define getMax(first, second) \\\n"
                          "first * second\n");
  String *latestString = stringNew("getMax(40$, 60)");
  char *replacedMacroString, *finalResult = NULL;
  int size;

  printf("Start test_searchAndReplaceArgumentsInString_given_statement_with_multiple_arguments_should_replace_all_the_arguments\n");
  Node *root = addAllMacroIntoTree(str, "define");
  Macro *foundMacro = findMacroInTree(root, "getMax");
  String *macroSubString = getMacroPositionInString(latestString, root);
  modifyMacroPositionWithArguments(macroSubString, foundMacro);
  size = strlen(latestString->string) - macroSubString->length + (foundMacro->content->length);
  storeArgumentsInString(latestString, foundMacro);
  replacedMacroString = replaceMacroInString(latestString, macroSubString, foundMacro, size);
  finalResult = searchAndReplaceArgumentsInString(replacedMacroString, foundMacro);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(finalResult);
  TEST_ASSERT_EQUAL_STRING("40$ * 60", finalResult);

  subStringDel(replacedMacroString);
  stringDel(latestString);
  stringDel(str);
}