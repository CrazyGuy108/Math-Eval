#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

struct Parser;

#include "expr.h"
#include "lexer.h"

// parses a token stream
// for now it rips tokens straight off of the lexer
struct Parser
{
	struct Lexer* lexer;
	struct Token next;
};

// Parser constructor
void
Parser_init(struct Parser* this, struct Lexer* lexer);

// parses an expression using the right binding power (rbp)
// this tells us how closely an expression on the right side of an operator
//  binds to that operator
struct Expr*
Parser_parseExpr(struct Parser* this, size_t rbp);

// destroys an expression created by Parser_parseExpr
void
Parser_freeExpr(struct Expr** expr);

// consumes the next token
struct Token
Parser_consume(struct Parser* this);

// peeks at the next token but doesn't consume it
const struct Token*
Parser_peek(const struct Parser* this);

#ifdef __cplusplus
}
#endif

#endif // PARSER_H
