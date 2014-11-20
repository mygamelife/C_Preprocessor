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
  int result = 0;
	String *str = stringNew("MAX 100");

  printf("Start test_getMacroInfo_given_name_MAX_content_100_should_return_macro_pointer_with_these_info\n");
  Macro *macro = getMacroInfo(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("MAX", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("100", macro->content->string);

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
  int result = 0;
	String *str = stringNew("MINUTE 50\n"
                          "SECOND 3000\n");

  printf("Start test_getMacroInfo_given_name_MINUTE_50_and_SECOND_3000_should_return_macro_pointer_with_these_info\n");
  Macro *macro = getMacroInfo(str);
  macro = getMacroInfo(str);
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macro);
  TEST_ASSERT_EQUAL_STRING("SECOND", macro->name->string);
  TEST_ASSERT_EQUAL_STRING("3000", macro->content->string);
  TEST_ASSERT_EQUAL(21, str->startindex);
  TEST_ASSERT_EQUAL(1, str->length);

  delMacro(macro);
  stringDel(str);
}

/** test destroyAllMacroInTree() added two macroNode into tree should free all of them
 *  #define BYE BY3
 *  #define HI H1
 *
 ** result : free all the malloc memory in tree
 **/
void test_destroyAllMacroInTree_given_BYE_HI_macroNode_added_into_tree_should_remove_all_and_become_NULL(void)
{
  int result = 0;
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
  // Macro *macro2 = (Macro*)root->right->dataPtr;
  // printf("root %s\n", macro->name->string);
  // printf("root right %s\n", macro2->name->string);

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
  int result = 0;
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

/** test findMacro() given added macroNode tree:
 ** tree  :
 *                 MIDDLE(20)
 *                /     \
 *      (30)LARGE        SMALL(10)
 *
 ** result :
 *          return macroContent contain 10
 **/
void test_findMacro_given_added_macroNode_tree_and_find_SMALL_should_return_10(void)
{
  int result = 0;
	String *str = stringNew("#define MIDDLE 20\n"
                          "#define LARGE 30\n"
                          "#define SMALL 10\n");

  printf("Start test_findMacro_given_added_macroNode_tree_and_find_SMALL_should_return_10\n");
  //add all macroNode to tree
  Node *root = addAllMacroIntoTree(str, "define");

  //find targetMacro in tree
  Macro *macroContent = findMacro(root, "SMALL");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macroContent);
  TEST_ASSERT_EQUAL_STRING("10", macroContent->content->string);

  //free all malloc memory in tree
  destroyAllMacroInTree(root);
  stringDel(str);
}

/** test findMacro() given added 7 macroNode tree:
 * Search the IN macroNode in the tree and return the content of it which is 30
 ** result :
 *          return macroContent contain 30
 **/
void test_findMacro_given_added_macroNode_tree_and_find_IN_should_return_30(void)
{
  int result = 0;
	String *str = stringNew("#define FIND 10\n"
                          "#define TARGET 20\n"
                          "#define IN 30\n"
                          "#define SEVEN 40\n"
                          "#define MACRO 50\n"
                          "#define NODE 60\n"
                          "#define TREE 70\n");

  printf("Start test_findMacro_given_added_macroNode_tree_and_find_IN_should_return_30\n");
  //add all macroNode to tree
  Node *root = addAllMacroIntoTree(str, "define");

  //find targetMacro in tree
  Macro *macroContent = findMacro(root, "IN");
  printf("------------------------------------------------------------\n");

  TEST_ASSERT_NOT_NULL(macroContent);
  TEST_ASSERT_EQUAL_STRING("30", macroContent->content->string);

  destroyAllMacroInTree(root);
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
  int result = 0;
	String *str = stringNew("#define BIG 999\n"
                          "X = BIG;\n");

  printf("Start test_directiveDefine_given_BIG_999_and_X_equal_BIG_should_replace_BIG_to_999\n");
  directiveDefine(str, "define");
  printf("------------------------------------------------------------\n");

  // TEST_ASSERT_NOT_NULL(macro);
  // TEST_ASSERT_EQUAL_STRING("MAX", macro->name->string);
  // TEST_ASSERT_EQUAL_STRING("100", macro->content->string);

  // delMacro(macro);
  // stringDel(str);
}