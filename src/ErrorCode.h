#ifndef ErrorCode_H
#define ErrorCode_H

typedef enum {
  ERR_NODE_UNAVAILABLE,
  ERR_INVALID_FORMAT,
  ERR_EMPTY_MACRO_NAME,
  ERR_INVALID_IDENTIFIER,
  ERR_INVALID_DIRECTIVE
} ErrorCode;

#endif //ErrorCode_H