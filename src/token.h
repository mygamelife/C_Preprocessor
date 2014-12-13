#ifndef ErrorCode_H
#define ErrorCode_H

typedef enum {
  ERR_NODE_UNAVAILABLE,
  ERR_INVALID_FORMAT,
  ERR_EMPTY_MACRO_NAME,
  ERR_MACRO_REDEFINED,
  ERR_MACRO_ARGUMENTS_REDEFINED,
  ERR_INVALID_IDENTIFIER,
  ERR_INVALID_DIRECTIVE,
  ERR_EXPECT_CLOSED_BRACKET,
  ERR_EXPECT_ARGUMENT,
  ERR_EXPECT_NO_ARGUMENT,
  ERR_EXPECT_SPACE,
  ERR_EXPECT_IDENTIFIER,
  ERR_MISMATCH_ARGUMENT_SIZE
} ErrorCode;

#endif //ErrorCode_H

#ifndef StringObject_H
#define StringObject_H

extern char *numSet;
extern char *opSet;
extern char *alphaNumericSet;
extern char *alphaNumericSetWithBracket;
extern char *alphaNumericSetWithSymbol;
extern char *alphaNumericSetWithSymbolWithoutBracket;
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
void stringTrimUntilEOL(String *str);
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
String *stringSearchWordContaining(String *str , char *containSet);
#endif // StringObject_H


