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
void test_isHashTag_given_dollar_sign_should_return_0(void)
{
  int result = 0;
	String *str = stringNew("$");

  result = isHashTag(str);

  TEST_ASSERT_EQUAL(0, result);
  stringDel(str);
}

/** test isDirective given invalid directive name should throw an error**/
void test_isDirective_should_throw_an_exception(void)
{
	String *str;
  CEXCEPTION_T err;

  Try {
    str = stringNew("HALELUYA");
    int result = isDirective(str, "include");
    TEST_FAIL_MESSAGE("Should throw ERR_INVALID_DIRECTIVE exception");
  }
  Catch(err) {
    TEST_ASSERT_EQUAL_MESSAGE(ERR_INVALID_DIRECTIVE, err, "Expect ERR_INVALID_DIRECTIVE exception");
  }
  stringDel(str);
}

/** test isDirective given "   # in  clude" space at # and inside directive name should throw an error **/
void test_isDirective_space_between_hashtag_and_inside_directiveName_should_throw_error(void)
{
	String *str;
  CEXCEPTION_T err;

  Try {
    str = stringNew("   # in  clude");
    isDirective(str, "include");
    TEST_FAIL_MESSAGE("Should throw ERR_INVALID_DIRECTIVE exception");
  }
  Catch(err) {
    TEST_ASSERT_EQUAL_MESSAGE(ERR_INVALID_DIRECTIVE, err, "Expect ERR_INVALID_DIRECTIVE exception");
  }
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

/** test isDirective given "     #   define" space between # and directive name should return 1 **/
void test_isDirective_space_between_hashtag_and_directiveName_should_return_1(void)
{
  int result = 0;
	String *str = stringNew("     #   define");

  result = isDirective(str, "define");

  TEST_ASSERT_EQUAL(1, result);
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
  String *str;
  CEXCEPTION_T err;

  Try {
    str = stringNew("123MAX");
    result = isIdentifier(str);
    TEST_FAIL_MESSAGE("Should throw ERR_INVALID_IDENTIFIER exception");
  }
  Catch(err) {
    TEST_ASSERT_EQUAL_MESSAGE(ERR_INVALID_IDENTIFIER, err, "Expect ERR_INVALID_IDENTIFIER exception");
  }
  stringDel(str);
}

/** test getMacroInfo() given 1 info
 *  name = "MAX"
 *  content = "100"
 *  macro pointer should contain all these information
 **/
void test_getMacroInfo_given_name_MAX_content_100_should_return_macro_pointer_with_these_info(void)
{
	String *str = stringNew("MAX 100");

  printf("Start test_getMacroInfo_given_name_MAX_content_100_should_return_macro_pointer_with_these_info\n");
  Macro *macro = getMacroInfo(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("MAX", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("100", macro->content->string);

  delMacroNameAndContent(macro);
  delMacro(macro);
  stringDel(str);
}

/** test getMacroInfo() given 2 info
 *  name = "MINUTE"
 *  content = "50"
 *  name = "SECOND"
 *  content = "3000"
 *  macro pointer should contain all these information
 **/
void test_getMacroInfo_given_name_MINUTE_50_and_SECOND_3000_should_return_macro_pointer_with_these_info(void)
{
	String *str = stringNew("MINUTE 50\n"
                          "SECOND 3000\n");

  printf("Start test_getMacroInfo_given_name_MINUTE_50_and_SECOND_3000_should_return_macro_pointer_with_these_info\n");
  
  Macro *macro = getMacroInfo(str);
  //free memory
  delMacroNameAndContent(macro);
  delMacro(macro);
  
  macro = getMacroInfo(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("SECOND", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("3000", macro->content->string);
  TEST_ASSERT_EQUAL(21, str->startindex);
  TEST_ASSERT_EQUAL(1, str->length);

  delMacroNameAndContent(macro);
  delMacro(macro);
  stringDel(str);
}

/** test getMacroInfo() given 2 info
 *  _MAX32 = "4 $$"
 *  ONE_1 = "ABC * 5"
 *  _2TWO = "!@#$%"
 *  macro pointer should contain all these information
 **/
void test_getMacroInfo_given_name_3_identifier_name_and_3_random_content_should_return_macro_pointer_with_these_info(void)
{
	String *str = stringNew("_MAX32 4 $$\n"
                          "ONE_1 ABC * 5\n"
                          "_2TWO !@#$%\n");

  printf("Start test_getMacroInfo_given_name_3_identifier_name_and_3_random_content_should_return_macro_pointer_with_these_info\n");
  Macro *macro = getMacroInfo(str);
  
  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("_MAX32", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("4 $$", macro->content->string);
  
  delMacroNameAndContent(macro);
  delMacro(macro);
  
  macro = getMacroInfo(str);
  
  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("ONE_1", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("ABC * 5", macro->content->string);
  
  delMacroNameAndContent(macro);
  delMacro(macro);
  
  macro = getMacroInfo(str);
  
  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("_2TWO", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("!@#$%", macro->content->string);
  printf("------------------------------------------------------------\n");

  delMacroNameAndContent(macro);
  delMacro(macro);
  stringDel(str);
}

/** test getMacroInfo() given empty macro name
 *  should throw ERR_EMPTY_MACRO_NAME
 **/
void Xtest_getMacroInfo_given_empty_info_should_return_NULL(void)
{
  String *str;
  Macro *macro = NULL;
  CEXCEPTION_T err;
	
  printf("Start test_getMacroInfo_given_empty_info_should_return_NULL\n");  
  Try {
    str = stringNew(" \n");
    macro = getMacroInfo(str);
    TEST_FAIL_MESSAGE("Should throw ERR_EMPTY_MACRO_NAME exception");
  }
  Catch(err) {
    TEST_ASSERT_EQUAL_MESSAGE(ERR_EMPTY_MACRO_NAME, err, "Expect ERR_EMPTY_MACRO_NAME exception");
  }
  printf("------------------------------------------------------------\n");

  delMacroNameAndContent(macro);
  delMacro(macro);
  stringDel(str);
}

/** test getMacroInfo() given macro name but empty content
 *  should return NULL
 **/
void Xtest_getMacroInfo_given_macro_name_but_empty_info_should_return_NULL(void)
{
	String *str = stringNew("EmptyContent\n");

  printf("Start test_getMacroInfo_given_macro_name_but_empty_info_should_return_NULL\n");  
  Macro *macro = getMacroInfo(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("EmptyContent", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("", macro->content->string); //empty content

  delMacroNameAndContent(macro);
  delMacro(macro);
  stringDel(str);
}

/** test destroyAllMacroInTree() added two macroNode into tree should free all of them
 *  #define BYE BY3
 *  #define HI H1
 *
 ** result : free all the malloc memory in tree
 **/
void Xtest_destroyAllMacroInTree_given_BYE_HI_macroNode_added_into_tree_should_remove_all_and_become_NULL(void)
{
	String *str = stringNew("#define BYE BY3\n"
                          "#define HI H1\n");

  printf("Start test_destroyAllMacroInTree_given_BYE_HI_macroNode_added_into_tree_should_remove_all_and_become_NULL\n");
  Node *root = addAllMacroIntoTree(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(root);
  Macro *m1 = (Macro*)root->dataPtr;
  TEST_ASSERT_EQUAL_STRING("BYE", m1->name->string);
  TEST_ASSERT_EQUAL_STRING("BY3", m1->content->string);

  TEST_ASSERT_NOT_NULL(root->right);
  Macro *m2 = (Macro*)root->right->dataPtr;
  TEST_ASSERT_EQUAL_STRING("HI", m2->name->string);
  TEST_ASSERT_EQUAL_STRING("H1", m2->content->string);

  //free all malloc memory in tree
  destroyAllMacroInTree(root);
  stringDel(str);
}

/** test directiveDefine() given macro name and empty content
 *  #define empty_content  
 *  
 ** result : should add macroNode which contain macro name but empty content
 **/
void test_addAllMacroIntoTree_given_macroNode_contain_macro_name_but_empty_content_should_add_into_tree(void)
{
	String *str = stringNew("#define empty_content\n");

  printf("Start test_addAllMacroIntoTree_given_macroNode_contain_macro_name_but_empty_content_should_add_into_tree\n");
  Node *root = addAllMacroIntoTree(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(root);
  Macro *m1 = (Macro*)root->dataPtr;
  TEST_ASSERT_EQUAL_STRING("empty_content", m1->name->string);
  TEST_ASSERT_EQUAL_STRING("", m1->content->string);

  //free all malloc memory in tree
  destroyAllMacroInTree(root);
  stringDel(str);
}

/** test directiveDefine() given str pointer and directive name "define"
 *  #define HEIGHT  50cm
 *  #define WIDTH 70cm
 *  #define LENGTH  950
 *  #define AREA  456
 *
 ** result :                    root
 *                               |
 *                               v
 *                              HEIGHT
 *                            /       \
 *                         AREA        WIDTH
 *                                    /
 *                                 LENGTH
 **/
void test_addAllMacroIntoTree_given_HEIGHT_WIDTH_LENGTH_AREA_and_directive_name_define_should_add_all_into_tree(void)
{
	String *str = stringNew("#define HEIGHT 50cm\n"
                          "#define WIDTH 70cm\n"
                          "#define LENGTH 950\n"
                          "#define AREA 456\n");

  printf("Start test_addAllMacroIntoTree_given_HEIGHT_WIDTH_LENGTH_AREA_and_directive_name_define_should_add_all_into_tree\n");
  Node *root = addAllMacroIntoTree(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(root);
  Macro *m1 = (Macro*)root->dataPtr;
  TEST_ASSERT_EQUAL_STRING("HEIGHT", m1->name->string);
  TEST_ASSERT_EQUAL_STRING("50cm", m1->content->string);

  TEST_ASSERT_NOT_NULL(root->right);
  Macro *m2 = (Macro*)root->right->dataPtr;
  TEST_ASSERT_EQUAL_STRING("WIDTH", m2->name->string);
  TEST_ASSERT_EQUAL_STRING("70cm", m2->content->string);

  TEST_ASSERT_NOT_NULL(root->right->left);
  Macro *m3 = (Macro*)root->right->left->dataPtr;
  TEST_ASSERT_EQUAL_STRING("LENGTH", m3->name->string);
  TEST_ASSERT_EQUAL_STRING("950", m3->content->string);

  TEST_ASSERT_NOT_NULL(root->left);
  Macro *m4 = (Macro*)root->left->dataPtr;
  TEST_ASSERT_EQUAL_STRING("AREA", m4->name->string);
  TEST_ASSERT_EQUAL_STRING("456", m4->content->string);

  //free all malloc memory in tree
  destroyAllMacroInTree(root);
  stringDel(str);
}

/** test findMacroInTree() given added macroNode tree:
 ** Given random macroName and content contain symbol/spaces should add into tree
 **/
void test_findMacroInTree_given_random_name_and_content_contain_symbol_and_spaces_should_able_to_find_these_information(void)
{
  int result = 0;
	String *str = stringNew("#define _Apple *_*\n"
                          "#define Alex_123 $hi\n"
                          "#define AoA32 ; bye!!\n");

  printf("Start test_findMacroInTree_given_random_name_and_content_contain_symbol_and_spaces_should_able_to_find_these_information\n");
  //add all macroNode to tree
  Node *root = addAllMacroIntoTree(str, "define");
  Macro *macroContent;

  //find targetMacro in tree
  macroContent = findMacroInTree(root, "_Apple");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macroContent);
  TEST_ASSERT_EQUAL_STRING("*_*", macroContent->content->string);
  
  macroContent = findMacroInTree(root, "Alex_123");
  TEST_ASSERT_EQUAL_STRING("$hi", macroContent->content->string);
  
  macroContent = findMacroInTree(root, "AoA32");
  TEST_ASSERT_EQUAL_STRING("; bye!!", macroContent->content->string);
  //free all malloc memory in tree
  destroyAllMacroInTree(root);
  stringDel(str);
}

/** test findMacroInTree() given added 7 macroNode tree:
 * Search "findSomethingDoesntExist" in all these macroNode should return NULL
 ** result :
 *          should return NULL
 **/
void test_findMacroInTree_given_added_macroNode_tree_and_find_findSomethingDoesntExist_should_return_NULL(void)
{
	String *str = stringNew("#define FIND 10\n"
                          "#define TARGET 20\n"
                          "#define IN 30\n"
                          "#define SEVEN 40\n"
                          "#define MACRO 50\n"
                          "#define NODE 60\n"
                          "#define TREE 70\n");

  printf("Start test_findMacroInTree_given_added_macroNode_tree_and_find_findSomethingDoesntExist_should_return_NULL\n");
  //add all macroNode to tree
  Node *root = addAllMacroIntoTree(str, "define");

  //find targetMacro in tree
  Macro *macroContent = findMacroInTree(root, "findSomethingDoesntExist");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NULL(macroContent);

  destroyAllMacroInTree(root);
  stringDel(str);
}

/** test searchMacroInString():
 ** macro :
 *          #define search Macro
 *
 ** String :
 *          X trying to search Macro;
 **/
void test_searchMacroInString_given_string_X_trying_to_search_Macro_should_get_search_macroInfo(void) // <----- Problem
{
	String *str = stringNew("#define search Macro\n"
                           "X trying to search Macro\n");
  Macro *searchResult;
  
  printf("Start test_searchMacroInString_given_string_X_trying_to_search_Macro_should_get_search_macroInfo\n");
  Node *root = addAllMacroIntoTree(str, "define");
  searchResult = searchMacroInString(str, root);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(searchResult);
  TEST_ASSERT_EQUAL_STRING("search", searchResult->name->string);
  TEST_ASSERT_EQUAL_STRING("Macro", searchResult->content->string);

  destroyAllMacroInTree(root);
  stringDel(str);
}

/** test searchMacroInString():
 ** macro :
 *          #define Doesnt Exist
 *
 ** String :
 *          Search Something
 **/
void test_searchMacroInString_given_Search_Something_should_return_NULL_pointer(void) // <----- Problem
{
	String *str = stringNew("#define Doesnt Exist\n"
                           "Search Something\n");
  Macro *searchResult;
  
  printf("Start test_searchMacroInString_given_string_X_trying_to_search_Macro_should_get_search_macroInfo\n");
  Node *root = addAllMacroIntoTree(str, "define");
  searchResult = searchMacroInString(str, root);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NULL(searchResult);

  destroyAllMacroInTree(root);
  stringDel(str);
}

/** test searchMacroInString():
 ** macro :
 *          #define Empty
 *
 ** String :
 *          Looking for Empty Macro
 **/
void Xtest_searchMacroInString_given_Looking_for_Empty_Macro_should_macro_pointer(void) // <----- Problem
{
	String *str = stringNew("#define Empty        \n"
                           "Looking for Empty Macro\n");
  Macro *searchResult;
  
  printf("Start test_searchMacroInString_given_Looking_for_Empty_Macro_should_macro_pointer\n");
  Node *root = addAllMacroIntoTree(str, "define");
  searchResult = searchMacroInString(str, root);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(searchResult);
  TEST_ASSERT_EQUAL_STRING("Empty", searchResult->name->string);
  TEST_ASSERT_EQUAL_STRING("", searchResult->content->string);

  destroyAllMacroInTree(root);
  stringDel(str);
}

/** test replaceMacroInString():
 **  TEN 10
 **  X = TEN;
 *
 *  should replace TEN to 10
 ** result :
 *          X = 10;
 **/
void Xtest_replaceMacroInString_given_TEN_in_string_should_replace_it_with_10(void) // <----- Problem
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

/** test replaceMacroInString():
 **  Three 3
 **  X = 10 + Three + 5
 *
 *  should replace Three to 3
 ** result :
 *          X = 10 + 3 + 5
 **/
void Xtest_replaceMacroInString_given_Three_in_string_should_replace_it_with_3(void)
{
	String *str = stringNew("X = 10 + Three + 5");
  String *subStr = stringSubString(str, 9, 5);
  Macro *macro = newMacro("Three", "3");
  char *result;
  int size = size = (str->length) - (macro->name->length) + (macro->content->length);
  
  printf("Start test_replaceMacroInString_given_Three_in_string_should_replace_it_with_3\n");
  result = replaceMacroInString(str, subStr, macro, size);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("X = 10 + 3 + 5", result);
  
  subStringDel(result);
  delMacro(macro);
  stringDel(subStr);
  stringDel(str);
}

/** test replaceMacroInString():
 **  ONEFIVE 15
 **  X = 5 + ONEFIVE + Three + 5
 *
 *  should replace ONEFIVE to 15 and other remain the same
 ** result :
 *          X = 5 + 15 + Three + 5
 **/
void Xtest_replaceMacroInString_given_ONEFIVE_in_string_should_replace_it_with_15_other_identifier_should_remain_same(void)
{
	String *str = stringNew("X = 5 + ONEFIVE + Three + 5");
  String *subStr = stringSubString(str, 8, 7);
  Macro *macro = newMacro("ONEFIVE", "15");
  char *result;
  int size = size = (str->length) - (macro->name->length) + (macro->content->length);
  
  printf("Start test_replaceMacroInString_given_ONEFIVE_in_string_should_replace_it_with_15_other_identifier_should_remain_same\n");
  result = replaceMacroInString(str, subStr, macro, size);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("X = 5 + 15 + Three + 5", result);
  
  subStringDel(result);
  delMacro(macro);
  stringDel(subStr);
  stringDel(str);
}

/** test replaceMacroInString():
 **  NINE 99999
 **  X = HI + BYE + 1 + NINE
 *
 *  should only replace NINE to 99999 and other remain the same
 ** result :
 *          X = HI + BYE + 1 + 99999
 **/
void Xtest_replaceMacroInString_given_NINE_in_string_should_only_replace_it_with_99999_other_identifier_should_remain_same(void)
{
	String *str = stringNew("X = HI + BYE + 1 + NINE");
  String *subStr = stringSubString(str, 19, 4);
  Macro *macro = newMacro("NINE", "99999");
  char *result;
  int size = size = (str->length) - (macro->name->length) + (macro->content->length);
  
  printf("Start test_replaceMacroInString_given_NINE_in_string_should_only_replace_it_with_99999_other_identifier_should_remain_same\n");
  result = replaceMacroInString(str, subStr, macro, size);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("X = HI + BYE + 1 + 99999", result);
  
  subStringDel(result);
  delMacro(macro);
  stringDel(subStr);
  stringDel(str);
}

/** test replaceMacroInString():
 **  -EMPTY-
 **  X = HAPPY * HAPPY / 1000
 *
 *  shouldn't anything in the string
 ** result :
 *          X = HAPPY * HAPPY / 1000
 **/
void Xtest_replaceMacroInString_shouldnt_replace_anything_in_the_string(void)
{
	String *str = stringNew("X = HAPPY * HAPPY / 1000");
  String *subStr = stringSubString(str, 4, 2);
  Macro *macro = NULL;
  char *result;
  int size = size = (str->length) - 0 + 0;
  
  printf("Start test_replaceMacroInString_shouldnt_replace_anything_in_the_string\n");
  result = replaceMacroInString(str, subStr, macro, size);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("X = HAPPY * HAPPY / 1000", result);
  
  subStringDel(result);
  delMacro(macro);
  stringDel(subStr);
  stringDel(str);
}

/** test searchAndReplaceMacroInString():
 **  #define Dumb 500
 *
 **  10 + Dumb
 *
 *  should replace Dumb with 500 
 ** result :
 *          10 + 500
 **/
void Xtest_searchAndReplaceMacroInString_given_10_plus_Dumb_in_string_should_replace_it_with_500(void) // <----- Problem
{
	String *str = stringNew("#define Dumb 500\n"
                           "10 + Dumb");
  String *result;
  int found = 0;
  
  printf("Start test_searchAndReplaceMacroInString_given_10_plus_Dumb_in_string_should_replace_it_with_500\n");
  Node *root = addAllMacroIntoTree(str, "define");
  result = searchAndReplaceMacroInString(str, root, &found);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(1, found);
  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("10 + 500", result->string);

  destroyAllMacroInTree(root);
  stringDel(result);
  stringDel(str);
}

/** test searchAndReplaceMacroInString():
 **  #define Mini 888 + Huge
 *  
 **  A = 23 * Mini
 *
 *  should replace Mini with 888 + Huge 
 ** result :
 *          A = 23 * 888 + Huge
 **/
void Xtest_searchAndReplaceMacroInString_given_23_times_Mini_in_string_should_replace_Mini_with_888_plus_Huge(void) // <----- Problem
{
	String *str = stringNew("#define Mini 888 + Huge\n"
                           "A = 23 * Mini");
  String *result;
  int found = 0;
  
  printf("Start test_searchAndReplaceMacroInString_given_23_times_Mini_in_string_should_replace_Mini_with_888_plus_Huge\n");
  Node *root = addAllMacroIntoTree(str, "define");
  result = searchAndReplaceMacroInString(str, root, &found);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(1, found);
  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("A = 23 * 888 + Huge", result->string);

  destroyAllMacroInTree(root);
  stringDel(result);
  stringDel(str);
}

/** test searchAndReplaceMacroInString():
 **  #define _FIRE 18*10
 *  
 **  F = FIRE
 *
 *  shouldn't replace anything and the string remain the same 
 ** result :
 *          F = FIRE
 **/
void Xtest_searchAndReplaceMacroInString_given_F_equal_FIRE_in_string_shouldnt_replace_anything(void) // <----- Problem
{
	String *str = stringNew("#define _FIRE 18*10\n"
                           "F = FIRE");
  String *result;
  int found = 0;
  
  printf("Start test_searchAndReplaceMacroInString_given_F_equal_FIRE_in_string_shouldnt_replace_anything\n");
  Node *root = addAllMacroIntoTree(str, "define");
  result = searchAndReplaceMacroInString(str, root, &found);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_EQUAL(0, found);
  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("F = FIRE", result->string);

  destroyAllMacroInTree(root);
  stringDel(result);
  stringDel(str);
}

/** test directiveDefine() given string:
 *  #define BIG 999
 *  X = BIG;
 *
 ** result :
 *          X = 999;
 **/
void Xtest_directiveDefine_given_BIG_999_and_X_equal_BIG_should_replace_BIG_to_999(void)
{
	String *str = stringNew("#define BIG 99\n"
                          "X = BIG");
  String *result;
  Macro *found;

  printf("Start test_directiveDefine_given_BIG_999_and_X_equal_BIG_should_replace_BIG_to_999\n");
  result = directiveDefine(str, "define");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING("X = 99", result->string);
  TEST_ASSERT_EQUAL(0, result->startindex);
  TEST_ASSERT_EQUAL(6, result->length);

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
void Xtest_directiveDefine_given_ONE_plus_ONE_should_replace_two_ONE_with_1(void)
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
  // TEST_ASSERT_EQUAL(0, result->startindex);
  // TEST_ASSERT_EQUAL(6, result->length);

  stringDel(result);
  stringDel(str);
}