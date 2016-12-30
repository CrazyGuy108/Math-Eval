#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "expr.h"
#include "lexer.h"

// parses a token stream
// for now it rips tokens straight off of the lexer
struct Parser
{
	struct Lexer* lexer;
};

// Parser constructor
void
Parser_init(struct Parser* this, struct Lexer* lexer);

// generates an expression of a precedence not lower than what was given
struct Expr*
Parser_parseExpr(struct Parser* this, size_t precedence);

// destroys an expression created by Parser_parseExpr
void
Parser_freeExpr(struct Expr** expr);

// consumes the next token
struct Token
Parser_consume(struct Parser* this);

#ifdef __cplusplus
}
#endif

#endif // PARSER_H
