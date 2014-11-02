#include "unity.h"
#include "StringObject.h"
#include <string.h>

void setUp(void)
{
}

void tearDown(void)
{
}

/*
 * Create a new String
 */ 
void test_stringNew_given_NEW_startindex_0_and_length_0(void)
{
	String *str = stringNew("NEW");
	
	TEST_ASSERT_EQUAL_STRING("NEW" , str->string);
	TEST_ASSERT_EQUAL(0 , str->startindex);
	TEST_ASSERT_EQUAL(3 , str->length);
	
	stringDel(str);
}

/*
 * Trim all the spaces from left and stop at non-spaces character
 */
void test_stringTrimLeft_should_skip_spaces_on_left_sides_0(void)
{
	String *str = stringNew(" 2+2");
	stringTrimLeft(str);
	
	TEST_ASSERT_EQUAL(1 , str->startindex);
	TEST_ASSERT_EQUAL(3 , str->length);
	
	stringDel(str);
}

/*
 * Trim all the spaces included \t from left and stop at non-spaces character
 */
void test_stringTrimLeft_should_skip_spaces_on_left_sides_1(void)
{
	String *str = stringNew("\t\tABC");
	stringTrimLeft(str);
	
	TEST_ASSERT_EQUAL(2 , str->startindex);
	TEST_ASSERT_EQUAL(3 , str->length);
	
	stringDel(str);
}

/*
 * Trim all the spaces included \t from left and character is between spaces
 */
void test_stringTrimLeft_should_skip_spaces_on_left_sides_2(void)
{
	String *str = stringNew("\t  C \tHAOS");
	stringTrimLeft(str);
	
	TEST_ASSERT_EQUAL(3 , str->startindex);
	TEST_ASSERT_EQUAL(7 , str->length);
	
	stringDel(str);
}

/*
 * Trim all the spaces from right
 */
void test_stringTrimRight_should_skip_spaces_on_left_sides_0(void)
{
	String *str = stringNew("SLEEPLY ");
	stringTrimRight(str);

	TEST_ASSERT_EQUAL(0 , str->startindex);
	TEST_ASSERT_EQUAL(7 , str->length);
	
	stringDel(str);
}

/*
 * Trim all the spaces on right side of the string and 
 * str->length should remain same when i call stringTrimRight x2
 */
void test_stringTrimRight_should_skip_spaces_on_left_sides_str_length_will_remain_same_when_i_call_trim_right_x2(void)
{
	String *str = stringNew("  DRY    ");
	stringTrimRight(str);
	
	TEST_ASSERT_EQUAL(0 , str->startindex);
	TEST_ASSERT_EQUAL(5 , str->length);
	
	stringDel(str);
}

/*
 * Trim all the spaces on right side included \t and don't care the spaces in between character
 */
void test_stringTrimRight_should_skip_spaces_on_left_sides_2(void)
{
	String *str = stringNew("\t\tLO VE\t\t");
	stringTrimRight(str);
	
	TEST_ASSERT_EQUAL(0 , str->startindex);
	TEST_ASSERT_EQUAL(7 , str->length);
	
	stringDel(str);
}

/*
 * Trim spaces on left and right of the string
 */
void test_stringTrim_should_skip_spaces_on_left_and_right_sides_0(void)
{
	String *str = stringNew(" Stress ");
	stringTrim(str);
		
	TEST_ASSERT_EQUAL(1 , str->startindex);
	TEST_ASSERT_EQUAL(6 , str->length);
	
	stringDel(str);
}

/*
 * Trim spaces on left and right of the string and don't trim spaces in middle of string
 */
void test_stringTrim_should_skip_spaces_on_left_and_right_sides_1(void)
{
	String *str = stringNew("  2 +6 "); 
	stringTrim(str);

	TEST_ASSERT_EQUAL(2 , str->startindex);
	TEST_ASSERT_EQUAL(4 , str->length);
	
	stringDel(str);
}

/*
 * Trim spaces on left and right of the string (Included \t tab) and don't trim spaces in middle of string
 */
void test_stringTrim_should_skip_spaces_on_left_and_right_sides_2(void)
{
	String *str = stringNew("\t \t 13 +20 \t \t "); 
	stringTrim(str);

	TEST_ASSERT_EQUAL(4 , str->startindex);
	TEST_ASSERT_EQUAL(6 , str->length);
	
	stringDel(str);
}

/*
 * Given " HELLO" and containSet "L" should remove two LL 
 */
void test_stringRemoveWordContaining_given_HELLO_should_remove_L(void)
{
	String *str = stringNew(" HELLO");
	String *result;
	stringTrim(str);
	result = stringRemoveWordContaining(str , "L");
	
	/*Removed String*/
	TEST_ASSERT_EQUAL(3 , result->startindex);
	TEST_ASSERT_EQUAL(2 , result->length);
	/*Original String after Removed Word Containing*/
	TEST_ASSERT_EQUAL(5 , str->startindex);
	TEST_ASSERT_EQUAL(1 , str->length);
	
	stringDel(str);
}

/*
 * Given "MAXIS" and containSet "AI" should remove A and stop at X since X not inside containSet
 */ 
void test_stringRemoveWordContaining_MAXIS_should_remove_A(void)
{
	String *str = stringNew("MAXIS");
	stringTrim(str);
	String *result;	
	result = stringRemoveWordContaining(str , "AI");
	
	/*Removed String*/
	TEST_ASSERT_EQUAL(1 , result->startindex);
	TEST_ASSERT_EQUAL(1 , result->length);
	/*Original String after Removed Word Containing*/
	TEST_ASSERT_EQUAL(2 , str->startindex);
	TEST_ASSERT_EQUAL(3 , str->length);
	
	stringDel(str);
}

/*
 * given " \t 21 + 32  \t " and containSet "01234"
 * 21 will be remove and str->startindex stop at position next to 21 which is space
 */
void test_stringRemoveWordContaining_space_tab_21_plus_32_space_tab_should_remove_21(void)
{
	String *str = stringNew(" \t 21 + 32  \t ");
	stringTrim(str);
	String *result;
	result = stringRemoveWordContaining(str , "01234");
	
	/*Removed String*/
	TEST_ASSERT_EQUAL(3 , result->startindex);
	TEST_ASSERT_EQUAL(2 , result->length);
	/*Original String after Removed Word Containing*/
	TEST_ASSERT_EQUAL(5 , str->startindex);
	TEST_ASSERT_EQUAL(9 , str->length);
	
	stringDel(str);
}

/*
 * given "\t -10 + 2 " and containSet "43210"
 * skip negative sign
 * 10 will be remove and str->startindex stop at position next to 10 which is space
 */
void test_stringRemoveWordContaining_tab_space_negative_10_plus_2_space_should_remove_10(void)
{
	String *str = stringNew("\t -10 + 2 ");
	stringTrim(str);
	String *result;
	result = stringRemoveWordContaining(str , "43210");
	
	/*Removed String*/
	TEST_ASSERT_EQUAL(3 , result->startindex);
	TEST_ASSERT_EQUAL(2 , result->length);
	/*Original String after Removed Word Containing*/
	TEST_ASSERT_EQUAL(5 , str->startindex);
	TEST_ASSERT_EQUAL(5 , str->length);
	
	stringDel(str);
}

/*
 * given "\tAB + CD\t" and containSet "+"
 * should remove "+" only and remain " CD\t" ,str->length is 4 
 */
void test_stringRemoveWordContaining_tab_AB_plus_CD_tab_should_remove_nothing(void)
{
	String *str = stringNew("\tAB + CD\t");
	stringTrim(str);
	String *result;
	result = stringRemoveWordContaining(str , "+");
	
	/*Removed String*/
	TEST_ASSERT_EQUAL(4 , result->startindex);
	TEST_ASSERT_EQUAL(1 , result->length);
	/*Original String after Removed Word Containing*/
	TEST_ASSERT_EQUAL(5 , str->startindex);
	TEST_ASSERT_EQUAL(4 , str->length);
	
	stringDel(str);
}

/*
 * Given " Beef " and containSet "f"
 * when call stringRemoveWordContaining x2 should remove nothing and str->length should 0
 */
void test_stringRemoveWordContaining_Beef_and_call_stringRemoveWordContaining_x2_should_nothing(void)
{	
	String *str = stringNew(" Beef ");
	String *result;
	stringTrim(str);
	result = stringRemoveWordContaining(str , "f");
	stringTrim(str);
	result = stringRemoveWordContaining(str , "f");
	
	/*Removed String*/
	TEST_ASSERT_EQUAL(0 , result->startindex);
	TEST_ASSERT_EQUAL(0 , result->length);
	/*Original String after Removed Word Containing*/
	TEST_ASSERT_EQUAL(6 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	stringDel(str);
}

/*
 * given " 123 + 65 * 91 " and containSet "0123456789"
 * After call stringRemoveWordContaining x4 should remove nothing and str->length is 0
 */
void test_stringRemoveWordContaining_123_plus_65_times_91_should_remove_nothing(void)
{
	String *str = stringNew(" 123 + 65 * 91 ");
	String *result;
	stringTrim(str);
	result = stringRemoveWordContaining(str , "0123456789");
	stringTrim(str);
	result = stringRemoveWordContaining(str , "0123456789");
	stringTrim(str);
	result = stringRemoveWordContaining(str , "0123456789");
	stringTrim(str);
	result = stringRemoveWordContaining(str , "0123456789");
	
	/*Removed String*/
	TEST_ASSERT_EQUAL(0 , result->startindex);
	TEST_ASSERT_EQUAL(0 , result->length);
	/*Original String after Removed Word Containing*/
	TEST_ASSERT_EQUAL(15 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	stringDel(str);
}

/*
 * Given ",ABC" and notContainSet "A"
 * Should remove comma "," and stop at A because A contain in notContainSet
*/
void test_stringRemoveWordNotContaining_comma_ABC_comma_should_remove_ABC(void)
{
	String *str = stringNew(",ABC");
	stringTrim(str);
	String *result;
	result = stringRemoveWordNotContaining(str , "A");
	
	/*Removed string from not containing in notContainSet*/
	TEST_ASSERT_EQUAL(0 , result->startindex);
	TEST_ASSERT_EQUAL(1 , result->length);
	/*String contain in notContainSet*/
	TEST_ASSERT_EQUAL(1 , str->startindex);
	TEST_ASSERT_EQUAL(3 , str->length);
	
	stringDel(str);
}

/*
 * Given "Jel'ly" and notContainSet "'"
 * Should remove "Jel" and stop at apostrophe ' because ' contain in notContainSet
*/
void test_stringRemoveWordNotContaining_Jel_apostrophe_ly_should_remove_Jel(void)
{
	String *str = stringNew("Jel'ly");
	stringTrim(str);
	String *result;
	result = stringRemoveWordNotContaining(str , "'");
	
	/*Removed string from not containing in notContainSet*/
	TEST_ASSERT_EQUAL(0 , result->startindex);
	TEST_ASSERT_EQUAL(3 , result->length);
	/*String contain in notContainSet*/
	TEST_ASSERT_EQUAL(3 , str->startindex);
	TEST_ASSERT_EQUAL(3 , str->length);
	
	stringDel(str);
}

/*
 * Given "Lady[]" and notContainSet "[]"
 * Should remove "Lady" and stop at square bracket [ because [ contain in notContainSet
*/
void test_stringRemoveWordNotContaining_Lady_square_bracket_should_remove_square_bracket(void)
{
	String *str = stringNew("Lady[]");
	stringTrim(str);
	String *result;
	result = stringRemoveWordNotContaining(str , "[]");
	
	/*Removed string from not containing in notContainSet*/
	TEST_ASSERT_EQUAL(0 , result->startindex);
	TEST_ASSERT_EQUAL(6 , result->length);
	/*String contain in notContainSet*/
	TEST_ASSERT_EQUAL(6 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	stringDel(str);
}

/*
 * Given "Oil," and notContainSet ";'["
 * Should remove all because all words not contain inside notContainSet
*/
void test_stringRemoveWordNotContaining_Oil_comma_should_remove_Oil_comma(void)
{
	String *str = stringNew("Oil,");
	stringTrim(str);
	String *result;
	result = stringRemoveWordNotContaining(str , ";'[");
	
	/*Removed string from not containing in notContainSet*/
	TEST_ASSERT_EQUAL(0 , result->startindex);
	TEST_ASSERT_EQUAL(4 , result->length);
	/*String contain in notContainSet*/
	TEST_ASSERT_EQUAL(4 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	stringDel(str);
}

/*
 * Given string "Apple" and relativePos 1
 * Should return the relative position character "p"
 */
void test_stringCharAt_given_Apple_and_relative_position_1_should_return_p(void)
{
	int charAtThisPosition;
	String *str = stringNew("Apple");
	charAtThisPosition = stringCharAt(str , 1);
	
	/* p = 112 in ASCII table */
	TEST_ASSERT_EQUAL(112 , charAtThisPosition);
	
	stringDel(str);
}

/*
 * Given string "Orange" and relativePos 6
 * Should return -1
 */
void test_stringCharAt_given_Orange_and_relative_position_6_should_return_negative_1(void)
{
	int charAtThisPosition;
	String *str = stringNew("Orange");
	charAtThisPosition = stringCharAt(str , 6);
	
	/* position 6 is beyond the position "e" */
	TEST_ASSERT_EQUAL(-1 , charAtThisPosition);
	
	stringDel(str);
}

/*
 * Given string "2+3" and relativePos -5
 * Should return -1
 */
void test_stringCharAt_given_2_plus_3_and_relative_position_negative_five_should_return_negative_1(void)
{
	int charAtThisPosition;
	String *str = stringNew("2+3");
	charAtThisPosition = stringCharAt(str , -5);
	
	/* -5 is not a valid position inside the string */
	TEST_ASSERT_EQUAL(-1 , charAtThisPosition);
	
	stringDel(str);
}

/*
 * Given string "Q" and should remove only one character "Q" and startindex 1 and length is 0
 */
void test_stringCharAt_given_Q_should_remove_Q(void)
{
	int removedChar;
	String *str = stringNew("Q");
	removedChar = stringRemoveChar(str);
	
	/* Q = 81 in ASCII table */
	TEST_ASSERT_EQUAL(81 , removedChar);
	TEST_ASSERT_EQUAL(1 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	stringDel(str);
}

/*
 * Given string "Bone" and should remove character "B" and startindex 1 and length is 3
 */
void test_stringCharAt_given_Bone_should_remove_B(void)
{
	int removedChar;
	String *str = stringNew("Bone");
	removedChar = stringRemoveChar(str);
	
	/* B = 66 in ASCII table */
	TEST_ASSERT_EQUAL(66 , removedChar);
	TEST_ASSERT_EQUAL(1 , str->startindex);
	TEST_ASSERT_EQUAL(3 , str->length);
	
	stringDel(str);
}

/*
 * Given string "Pig" remove 2 times startindex = 2 & length = 1
 */
void test_stringCharAt_given_Pig_and_removex2_should_remove_i(void)
{
	int removedChar;
	String *str = stringNew("Pig");
	removedChar = stringRemoveChar(str);
	removedChar = stringRemoveChar(str);
	
	/* i = 105 in ASCII table */
	TEST_ASSERT_EQUAL(105 , removedChar);
	TEST_ASSERT_EQUAL(2 , str->startindex);
	TEST_ASSERT_EQUAL(1 , str->length);
	
	stringDel(str);
}

/*
 * Given string "TED" and number of character to skip is 1 
 * Should skip "T" and remain "ED"
 */
void test_stringSkip_given_TED_and_skip_1_char_should_skip_T(void)
{
	String *str = stringNew("TED");
	stringSkip(str , 1);
	
	TEST_ASSERT_EQUAL(1 , str->startindex);
	TEST_ASSERT_EQUAL(2 , str->length);
	
	stringDel(str);
}

/*
 * Given string "Error" and number of character to skip is 4 
 * Should skip "Erro" and remain "r"
 */
void test_stringSkip_given_Error_and_skip_4_char_should_skip_Erro(void)
{
	String *str = stringNew("Error");
	stringSkip(str , 4);
	
	TEST_ASSERT_EQUAL(4 , str->startindex);
	TEST_ASSERT_EQUAL(1 , str->length);
	
	stringDel(str);
}

/*
 * Given string "Angel" and number of character to skip is 5 
 * Should skip "Angel" and remain nothing
 */
void test_stringSkip_given_Angel_and_skip_5_char_should_skip_all_character(void)
{
	String *str = stringNew("Angel");
	stringSkip(str , 5);
	
	TEST_ASSERT_EQUAL(0 , str->string[str->startindex]);
	TEST_ASSERT_EQUAL(5 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	stringDel(str);
}

/*
 * Given string "Monalisa" and number of character to skip is -2 
 * Should skip nothing
 */
void test_stringSkip_given_Monalisa_and_skip_negative_two_char_should_skip_nothing(void)
{
	String *str = stringNew("Monalisa");
	stringSkip(str , -2);
	
	TEST_ASSERT_EQUAL(0 , str->startindex);
	TEST_ASSERT_EQUAL(8 , str->length);
	
	stringDel(str);
}

/*
 * Given string "Miracle" and number of character to skip is 10 
 * Should skip all character and startindex pointing at 5
 */
void test_stringSkip_given_Miracle_and_skip_10_char_should_skip_all_character_and_stop_at_position_7(void)
{
	String *str = stringNew("Miracle");
	stringSkip(str , 10);
	
	TEST_ASSERT_EQUAL(0 , str->string[str->startindex]);
	TEST_ASSERT_EQUAL(7 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	stringDel(str);
}

/*
 * Given "82+29" and length is 2 should remove "82" as a substring
 */
void test_stringSubStringInChars_given_82_plus_29_and_length_is_2_should_return_82(void)
{
	char *subString;
	String *str = stringNew("82+29");
	subString = stringSubStringInChars(str , 2);
	
	TEST_ASSERT_EQUAL_STRING("82" , subString);
	TEST_ASSERT_EQUAL(2 , str->startindex);
	TEST_ASSERT_EQUAL(3 , str->length);
	
	subStringDel(subString);
	stringDel(str);
}

/*
 * Given "40*5", length is 2 and call subString twice should return *5
 */
void test_stringSubStringInChars_given_40_times_5_length_is_2_and_call_subString_x2_should_return_times_5(void)
{
	char *subString;
	String *str = stringNew("40*5");
	subString = stringSubStringInChars(str , 2);
	subString = stringSubStringInChars(str , 2);
	
	TEST_ASSERT_EQUAL_STRING("*5" , subString);
	TEST_ASSERT_EQUAL(4 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	subStringDel(subString);
	stringDel(str);
}

/*
 * Given "65*160", length is 6 and call subString twice should nothing
 */
void test_stringSubStringInChars_given_65_times_160_length_is_6_and_call_subString_x2_should_return_nothing(void)
{
	char *subString;
	String *str = stringNew("65*160");
	subString = stringSubStringInChars(str , 6);
	subString = stringSubStringInChars(str , 6);
	
	TEST_ASSERT_EQUAL_STRING("" , subString);
	TEST_ASSERT_EQUAL(12 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	subStringDel(subString);
	stringDel(str);
}

/*
 * Given "-234 * 1" and length is 2 should remove "-234 " as a substring
 */
void test_stringSubStringInChars_given_negative_234_times_1_and_length_is_5_should_return_negative_234_space(void)
{
	char *subString;
	String *str = stringNew("-234 * 1");
	subString = stringSubStringInChars(str , 5);
	
	TEST_ASSERT_EQUAL_STRING("-234 " , subString);
	
	subStringDel(subString);
	stringDel(str);
}

/*
 * Given "20/5" skip 3 characters and take the remaining character "5" as substring
 */
void test_stringSubStringInChars_given_20_divide_5_skip_3_chars_and_length_is_1_should_return_5(void)
{
	char *subString;
	String *str = stringNew("20/5");
	stringSkip(str , 3);
	subString = stringSubStringInChars(str , 1);
	
	TEST_ASSERT_EQUAL_STRING("5" , subString);
	
	subStringDel(subString);
	stringDel(str);
}

/*
 * Given "12+34*67" skip 4 characters and take the remaining character "4*67" as substring
 */
void test_stringSubStringInChars_given_12_plus_34_times_67_skip_4_chars_and_length_is_4_should_return_9_times_67(void)
{
	char *subString;
	String *str = stringNew("12+34*67");
	stringSkip(str , 4);
	subString = stringSubStringInChars(str , 4);
	
	TEST_ASSERT_EQUAL_STRING("4*67" , subString);
	
	subStringDel(subString);
	stringDel(str);
}

/*
 * Given "149" should return 149 as a integer
 */
void test_subStringToInteger_given_149_should_return_149_in_integer(void)
{
	char *number = "149";
	int integer = subStringToInteger(number);

	TEST_ASSERT_EQUAL(149 , integer);
}

/*
 * Given "-50" should return 149 as a integer
 */
void test_subStringToInteger_given_negative_50_should_return_negative_50_in_integer(void)
{
	char *number = "-50";
	int integer = subStringToInteger(number);

	TEST_ASSERT_EQUAL(-50 , integer);
}

/*
 * Given "1 + 10" given first position 0 and containSet is numSet
 * 1 should contain in containSet and return 1 else 0
 */
void test_stringCharAtInSet_given_1_plus_10_should_return_1(void)
{
	String *str = stringNew("1 + 10");
	int result = stringCharAtInSet(str , 0 , numSet);
	
	TEST_ASSERT_EQUAL(1 , result);
}

/*
 * Given " ABC + 1" given position 2 and containSet is alphaSet
 * 1 should contain in containSet and return 1 else 0
 */
void test_stringCharAtInSet_given_A_plus_1_should_return_1(void)
{
	String *str = stringNew("ABC + 1");
	int result = stringCharAtInSet(str , 2 , alphaSet);
	
	TEST_ASSERT_EQUAL(1 , result);
}

/*
 * Given "-123 + A" given position 5 and containSet is alphaNumericSet
 * 1 should contain in containSet and return 1 else 0
 */
void test_stringCharAtInSet_given_negative_123_plus_A_should_return_0(void)
{
	String *str = stringNew("-123 + A");
	int result = stringCharAtInSet(str , 5 , alphaNumericSet);
	
	TEST_ASSERT_EQUAL(0 , result);
}

/*
 * Given string "123" and start index is 0 and length is 3
 * should store "123" in subStr 
 */
void test_stringSubstring_given_123_start_0_and_length_3_should_put_into_string_subStr(void)
{
	String *str = stringNew("123");
	String *subStr = stringSubString(str , 0 , 3);
	
	TEST_ASSERT_NOT_NULL(subStr);
	TEST_ASSERT_EQUAL_STRING("123" , subStr->string);
	TEST_ASSERT_EQUAL(0 , subStr->startindex);
	TEST_ASSERT_EQUAL(3 , subStr->length);
	
	stringDel(str);
	stringDel(subStr);
}

/*
 * Given string "1+23" and start index is 3 and length is 1
 * should store "3" in subStr 
 */
void test_stringSubstring_given_1_plus_23_start_3_and_length_1_should_put_into_string_subStr(void)
{
	String *str = stringNew("1+23");
	String *subStr = stringSubString(str , 3 , 1);
	
	TEST_ASSERT_NOT_NULL(subStr);
	TEST_ASSERT_EQUAL_STRING("1+23" , subStr->string);
	TEST_ASSERT_EQUAL(3 , subStr->startindex);
	TEST_ASSERT_EQUAL(1 , subStr->length);
	
	stringDel(str);
	stringDel(subStr);
}

/*
 * Given string "12-32" and start index is 7 and length is 3
 * should store 5 in start index and length should be 0
 */
void test_stringSubstring_given_12_minus_32_start_7_and_length_3_should_put_5_into_string_subStr_startindex_and_length_0(void)
{
	String *str = stringNew("12-32");
	String *subStr = stringSubString(str , 7 , 3);
	
	TEST_ASSERT_NOT_NULL(subStr);
	TEST_ASSERT_EQUAL_STRING("12-32" , subStr->string);
	TEST_ASSERT_EQUAL(5 , subStr->startindex);
	TEST_ASSERT_EQUAL(0 , subStr->length);
	
	stringDel(str);
	stringDel(subStr);
}

/*
 * Given string "Cow" and start index is 3 and length is 3
 * should store 3 in start index and length should be 0
 */
void test_stringSubstring_given_Cow_start_3_and_length_3_should_put_3_into_string_subStr_startindex_and_length_0(void)
{
	String *str = stringNew("Cow");
	String *subStr = stringSubString(str , 3 , 3);
	
	TEST_ASSERT_NOT_NULL(subStr);
	TEST_ASSERT_EQUAL_STRING("Cow" , subStr->string);
	TEST_ASSERT_EQUAL(3 , subStr->startindex);
	TEST_ASSERT_EQUAL(0 , subStr->length);
	
	stringDel(str);
	stringDel(subStr);
}

// /*
 // * Given string "+-" and operator set
 // * should remove only one operator "+" 
 // */
// void test_stringRemoveOperator_minus_plus_operator_and_opSet_should_get_minus_operator(void)
// {
	// String *str = stringNew("+-");
	// String *removedOp = stringRemoveOperator(str , opSet);
	
	// TEST_ASSERT_NOT_NULL(removedOp);
	// TEST_ASSERT_EQUAL_STRING("+-" , removedOp->string);
	// TEST_ASSERT_EQUAL(0 , removedOp->startindex);
	// TEST_ASSERT_EQUAL(1 , removedOp->length);
	// TEST_ASSERT_EQUAL(1 , str->startindex);
	// TEST_ASSERT_EQUAL(1 , str->length);
	
	// stringDel(str);
// }

/*
 * Given string "&" and operator set
 * should remove only one operator "&", start index = 0 and length is 2
 */
void test_stringRemoveOperator_logical_AND_operatorx3_and_opSet_should_get_Bitwise_AND_operator(void)
{
	String *str = stringNew("& &&");
	stringTrim(str);
	String *removedOp = stringRemoveOperator(str , opSet);
	stringTrim(str);
	removedOp = stringRemoveOperator(str , opSet);
	stringTrim(str);
	
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(2 , removedOp->startindex);
	TEST_ASSERT_EQUAL(2 , removedOp->length);
	
	stringDel(str);
}

/*
 * Given string "&&" and operator set
 * should remove only one operator "&&", start index = 0 and length is 2
 */
void test_stringRemoveOperator_logical_AND_operator_and_opSet_should_get_logical_AND_operator(void)
{
	String *str = stringNew("&&");
	String *removedOp = stringRemoveOperator(str , opSet);
	
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL_STRING("&&" , removedOp->string);
	TEST_ASSERT_EQUAL(0 , removedOp->startindex);
	TEST_ASSERT_EQUAL(2 , removedOp->length);
	TEST_ASSERT_EQUAL(2 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	stringDel(str);
}

/*
 * Given string "|||" and operator set
 * should remove only one operator "||" and one "|"
 */
void test_stringRemoveOperator_Three_OR_operator_and_should_remove_3_OR_Operator(void)
{
	String *str = stringNew("|||");
	String *removedOp = stringRemoveOperator(str , opSet);
	
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(0 , removedOp->startindex);
	TEST_ASSERT_EQUAL(2 , removedOp->length);
	TEST_ASSERT_EQUAL(2 , str->startindex);
	TEST_ASSERT_EQUAL(1 , str->length);
	
	removedOp = stringRemoveOperator(str , opSet);
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL(2 , removedOp->startindex);
	TEST_ASSERT_EQUAL(1 , removedOp->length);
	TEST_ASSERT_EQUAL(3 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	stringDel(str);
}
/*
 * Given string "||" and operator set
 * should remove only one operator "||", start index = 0 and length is 2
 */
void test_stringRemoveOperator_logical_OR_operator_and_opSet_should_get_logical_OR_operator(void)
{
	String *str = stringNew("||");
	String *removedOp = stringRemoveOperator(str , opSet);
	
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL_STRING("||" , removedOp->string);
	TEST_ASSERT_EQUAL(0 , removedOp->startindex);
	TEST_ASSERT_EQUAL(2 , removedOp->length);
	TEST_ASSERT_EQUAL(2 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	stringDel(str);
}

/*
 * Given string "4" and operator set
 * should remove only one operator "||", start index = 0 and length is 2
 */
void test_stringRemoveOperator_4_operator_and_opSet_should_get_logical_OR_operator(void)
{
	String *str = stringNew("+||");
	String *removedOp = stringRemoveOperator(str , opSet);
	removedOp = stringRemoveOperator(str , opSet);
	
	TEST_ASSERT_NOT_NULL(removedOp);
	TEST_ASSERT_EQUAL_STRING("+||" , removedOp->string);
	TEST_ASSERT_EQUAL(1 , removedOp->startindex);
	TEST_ASSERT_EQUAL(2 , removedOp->length);
	TEST_ASSERT_EQUAL(3 , str->startindex);
	TEST_ASSERT_EQUAL(0 , str->length);
	
	stringDel(str);
}
