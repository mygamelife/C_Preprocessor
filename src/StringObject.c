#include "StringObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

char *numSet = "0123456789";
char *opSet = "(~!@#$%^&*_-+{}=|;:)\'<,.>/?";
char *alphaNumericSet = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
char *alphaSet = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

/* Create a new String
 * input :
 *		charString is the string that we receive
 * return:
 *		str pointer
 */
String *stringNew(char *charString)
{
	String *str = malloc(sizeof(String));
	str->string = charString;
	str->startindex = 0;
	str->length = strlen(charString);

	return str;
}

/* To remove all spaces at left side
 * input :
 *		string
 * output:
 *		string after remove left side spaces
 */
void stringTrimLeft(String *str)
{
	while(isspace(str->string[str->startindex]))
	{
		str->startindex++;
		str->length--;

		if(str->string[str->startindex] == 0)
			str->length = 0;
	}
}

/* To remove all spaces at right side
 * input :
 *		string
 * output:
 *		string after remove right side spaces
 */
void stringTrimRight(String *str)
{
	int i = strlen(str->string);

	if(str->string[i] == 0)
		i--;

	while(isspace(str->string[i]))
	{
		if(str->length == 0)
		break;

		i--;
		str->length--;
	}
}

/* To remove all spaces at left and right side in string
 * input :
 *		string
 * output:
 *		string after remove all spaces on left and right side
 */
void stringTrim(String *str)
{
	stringTrimLeft(str);
	stringTrimRight(str);
}

/* To remove words contain in ContainSet
 * input :
 *		ContainSet character that need to be remove
 * return:
 *		Return the removedWord start index and length
 */
String *stringRemoveWordContaining(String *str , char *containSet)
{
	int i = str->startindex , j = 0 , firstFound = 0 , notInSet = 0;

	String *removedWord = stringNew(str->string); //create new String for removedWord
	removedWord->length = 0;

	while(i < strlen(str->string))
	{
		while(j != strlen(containSet))
		{
			if(str->string[i] == containSet[j]) //searching is containSet inside the string
			{
				if(!firstFound)
				{
					removedWord->startindex = i; //first character found
					firstFound = 1; //make sure this statement wont run again when the first character is found
				}
				removedWord->length++; //one word is detected in ContainSet
				str->startindex = i+1;
				notInSet = 0;

				goto jump;
			}

			if(firstFound == 1)
				notInSet = 1;

			j++;
		}

		if(notInSet == 1)
			goto end;

jump:
		i++;
		j = 0;
	}

end:
	str->length = strlen(str->string) - str->startindex;
	return removedWord;
}

/* To remove words not contain in ContainSet
 * input :
 *		notContainSet is character that don't need to be remove
 * return:
 *		Return the notRemovedWord start index and length
 */
String *stringRemoveWordNotContaining(String *str , char *notContainSet)
{
	int i = str->startindex , j = 0 , firstFound = 0 , notInSet = 0;

	String *notRemovedWord = stringNew(str->string); //create new String for notRemovedWord
	notRemovedWord->length = 0;

	while(i < strlen(str->string))
	{
		while(j != strlen(notContainSet))
		{
			if(str->string[i] != notContainSet[j])
			{
				if(!firstFound)
				{
					notRemovedWord->startindex = i; //first character found
					firstFound = 1;
					if(i != 0)
						str->length = str->length - i;
				}

				notRemovedWord->length++; //one word is detected in ContainSet
				str->startindex = i+1;
				str->length--; //decrement once after one word removed
				notInSet = 0;

				goto jump;
			}

			if(firstFound == 1)
				notInSet = 1;

			j++;
		}

		if(notInSet == 1)
			goto end;
jump:
		i++;
		j = 0;
	}

end:
	return notRemovedWord;
}

/* Find the character according to the relative position
 * input :
 *			relativePos the position of string
 * return :
 *			if relative position is valid in this string return the relative position character
 *			else return negative 1
 */
int stringCharAt(String *str ,  int relativePos)
{
	if((relativePos < 0 ) || relativePos > (strlen(str->string) - 1))
		return -1;

	return str->string[relativePos];
}

/* Remove one character and move start index to next position
 * input :
 *			*str is the pointer pointing the string that need to be remove
 * return :
 *			return the removed character from the string
 */
int stringRemoveChar(String *str)
{
	char removedChar;

	//start index move to next position after one char removed
	removedChar = str->string[str->startindex++];
	str->length--;

	return removedChar;
}

/* Skip number of character in string
 * input :
 *			numOfCharToSkip number of character wanted to be skip
 * output :
 *			str->startindex point to character after skip
 */
void stringSkip(String *str , int numOfCharToSkip)
{
	if(numOfCharToSkip < 0)
		str->startindex = 0;

	else if((str->length - 1) >= numOfCharToSkip)
	{
		str->startindex = numOfCharToSkip;
		str->length = str->length - numOfCharToSkip;
	}

	else
	{
		str->startindex = str->length;
		str->length = 0;
	}
}

/* Remove SubString inside the character according to the length
 * input :
 *			length is the substring length to know how many character should remove as a substring
 * return :
 *			store the removed substring in charStr and return
 */
char *stringSubStringInChars(String *str , int length)
{
	int i = 0 , j = str->startindex;
	char *charStr = malloc(sizeof(char) * length + 1); //malloc charStr in order to return

	for(i ; i < length ; i++)
	{
		charStr[i] = str->string[j++];
		str->startindex++;

		if(str->length != 0)  {
			str->length--;
    }

		charStr[i+1] = 0; //Create delimiter "\0" for the string
	}

	return charStr;
}

/* Convert substring into integer
 * input :
 *			subString get it from function stringSubStringInChars
 * return :
 *			return subString in integer form
 */
int subStringToInteger(char *subString)
{
	int integer;

	integer = atoi(subString); //atoi ASCII to integer

	return integer;
}

/* Free memory allocate
 * free str pointer
 */
void stringDel(String *str)
{
	if(str)
		free(str);
}

/* Free memory allocate
 * free sub string pointer
 */
void subStringDel(char *subString)
{
	if(subString)
		free(subString);
}

/* Check the relative position of the string if in contain in containSet
 * input :
 *			String *str is the string that contain a expression
 *			containSet is the words that we want
 * output :
 *			if string contain words inside containSet return 1
 *			else return 0
 */
int stringCharAtInSet(String *str , int relativePos , char *containSet)
{
	int i = 0;

	while(i != strlen(containSet))
	{
		if(str->string[relativePos] == containSet[i++])
			return 1;
	}

	return 0;
}

/* Get the substring location out from the string
 * input :
 *			start is the start location for the substring
 *			length is the total character of the substring
 * return :
 *		 	return the subString
 */
String *stringSubString(String *str , int start , int length)
{
	String *subStr = stringNew(str->string);

	if(start >= strlen(subStr->string))
	{
		subStr->startindex = strlen(subStr->string);
		subStr->length = 0;
		return subStr;
	}

	subStr->startindex = start;
	subStr->length = length;
	// printf("start = %d\n" , subStr->startindex);
	// printf("length = %d\n" , subStr->length);
	return subStr;
}

String *stringRemoveOperator(String *str , char *containSet)
{
	int i = str->startindex , j = 0;

	String *removedWord = stringNew(str->string); //create new String for removedWord
	removedWord->length = 0;

	while(i < strlen(str->string))
	{
		while(j != strlen(containSet))
		{
			if(str->string[i] == containSet[j]) //searching is containSet inside the string
			{
				if(str->string[i] == '&') //check "&" operator
				{
					if(str->string[i+1] == '&') //check "&&" operator
					{
						removedWord->startindex = i;
						removedWord->length = 2;
						str->startindex = i+2;
						str->length -= 2;
						str->length = strlen(str->string) - str->startindex;
						return removedWord;
					}
					goto jump;
				}

				else if(str->string[i] == '|') //check "||" operator
				{
					if(str->string[i+1] == '|')
					{
						removedWord->startindex = i;
						removedWord->length = 2;
						str->startindex = i+2;
						str->length -= 2;
						str->length = strlen(str->string) - str->startindex;
						return removedWord;
					}
					goto jump;
				}

				else if(str->string[i] == '<') //check "<<" operator
				{
					if(str->string[i+1] == '<')
					{
						removedWord->startindex = i;
						removedWord->length = 2;
						str->startindex = i+2;
						str->length -= 2;
						str->length = strlen(str->string) - str->startindex;
						return removedWord;
					}
					goto jump;
				}

				else if(str->string[i] == '>') //check ">>" operator
				{
					if(str->string[i+1] == '>')
					{
						removedWord->startindex = i;
						removedWord->length = 2;
						str->startindex = i+2;
						str->length -= 2;
						str->length = strlen(str->string) - str->startindex;
						return removedWord;
					}
					goto jump;
				}

				else if(str->string[i] == '=') //check "==" operator
				{
					if(str->string[i+1] == '=')
					{
						removedWord->startindex = i;
						removedWord->length = 2;
						str->startindex = i+2;
						str->length -= 2;
						str->length = strlen(str->string) - str->startindex;
						return removedWord;
					}
					goto jump;
				}
jump:
				removedWord->startindex = i;
				removedWord->length++;
				str->startindex = i+1;
				str->length = strlen(str->string) - str->startindex;
				return removedWord;
			}

			j++;
		}
		i++;
		j = 0;
	}
	return removedWord;
}