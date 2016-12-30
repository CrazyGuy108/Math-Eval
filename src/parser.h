#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "expr.h"
#include "lexer.h"

// forward-declare Parser so parselet.h knows about it
struct Parser;

#include "parselet.h"

// parses a token stream
// for now it rips tokens straight off of the lexer
struct Parser
{
	const struct Parser_vtable* vtable;
	struct Lexer* lexer;
	struct Token next;
};

// main vtable for Parser subclasses
struct Parser_vtable
{
	void (*dtor)(struct Parser*);
	struct PrefixParselet* (*prefix)(struct Parser*, enum TokenType);
	struct InfixParselet* (*infix)(struct Parser*, enum TokenType);
};

// Parser constructor
void
Parser_init(struct Parser* this, struct Lexer* lexer);

// virtual destructor wrapper for Parser subclasses
void
Parser_dtor(struct Parser* this);

// virtual member function wrapper for Parser subclasses
// creates/gets a PrefixParselet based on the TokenType
struct PrefixParselet*
Parser_prefix(struct Parser* this, enum TokenType type);

// virtual member function wrapper for Parser subclasses
// creates/gets an InfixParselet based on the TokenType
struct InfixParselet*
Parser_infix(struct Parser* this, enum TokenType type);

// generates an expression of a precedence not lower than what was given
struct Expr*
Parser_parseExpr(struct Parser* this, size_t precedence);

// destroys an expression created by Parser_parseExpr
void
Parser_freeExpr(struct Expr** expr);

// consumes the next token
struct Token
Parser_consume(struct Parser* this);

// peeks at the next token but doesn't consume it
const struct Token*
Parser_peek(const struct Parser* this);

// main Parser destructor
// all subclass destructors should call this
void
Parser_v_dtor(struct Parser* this);

extern const struct Parser_vtable Parser_vtable;

#ifdef __cplusplus
}
#endif

#endif // PARSER_H
