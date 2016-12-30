#ifndef LEXER_H
#define LEXER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <stdlib.h>
#include "token.h"

// generates a stream of Tokens by stepping through the input string
struct Lexer
{
	const char* pos;
};

// initializes a Lexer
void
Lexer_init(struct Lexer* this, const char* source);

// gets/generates the next Token from the source string
// if at the end of the string, the lexer creates an EOF token
struct Token
Lexer_next(struct Lexer* this);

#ifdef __cplusplus
}
#endif

#endif // LEXER_H
