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