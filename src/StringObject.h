#ifndef StringObject_H
#define StringObject_H

extern char *numSet;
extern char *opSet;
extern char *alphaNumericSet;
extern char *alphaNumericSetWithSymbol;
extern char *alphaSet;

typedef struct
{
	char *string;
	int startindex;
	int length;
}String;

String *stringNew(char *charString);
void stringTrimLeft(String *str);
void stringTrimRight(String *str);
void stringTrim(String *str);
String *stringRemoveWordContaining (String *str , char *containSet);
String *stringRemoveWordNotContaining (String *str , char *notContainSet);
int stringCharAt(String *str ,  int relativePos);
int stringRemoveChar(String *str);
void stringSkip(String *str , int numOfCharToSkip);
char *stringSubStringInChars(String *str , int length);
int subStringToInteger(char *subString);
void stringDel(String *str);
void subStringDel(char *subString);
int stringCharAtInSet(String *str , int relativePos , char *containSet);
String *stringSubString(String *str , int start , int length);
String *stringRemoveOperator(String *str , char *containSet);
void subStringToArray(char charArry[], String *str);
#endif // StringObject_H
