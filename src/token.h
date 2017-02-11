#ifndef TOKEN_H
#define TOKEN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>

// the type of token that a Token can represent
enum TokenType
{
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_ASTERISK,
	TOKEN_SLASH,
	TOKEN_CARET,
	TOKEN_INTEGER,
	TOKEN_EOF,
	TOKEN_INVALID
};

// left/right binding power of a token
// if rbp is omitted, it's assumed to be the same as the lbp
enum BindingPower
{
	LBP_LPAREN   = 0,
	LBP_RPAREN   = 0,
	LBP_PLUS     = 1,
	LBP_MINUS    = 1,
	LBP_ASTERISK = 2,
	LBP_SLASH    = 2,
	LBP_CARET    = 3,
	RBP_CARET    = 2, // right-associative
	LBP_INTEGER  = 0,
	LBP_EOF      = 0,
	LBP_INVALID  = 0
};

// a single lexer token
struct Token
{
	enum BindingPower lbp;
	enum TokenType type;
	int value;
	size_t pos;
};

#include "expr.h"
#include "parser.h"

// converts a TokenType to a string
const char*
TokenType_toString(enum TokenType type);

// Token constructor
void
Token_init(struct Token* this, enum TokenType type, int value, size_t pos);

// calls the null denotation (nud) of a token
// this is called when an expression to the left of this token is bound to
//  another operator so it's treated as null, that cheating imbecile
struct Expr*
Token_nud(const struct Token* this, struct Parser* parser);

// calls the left denotation (led) of a token
// this is called when an expression to the left of this token is bound to this
//  more than the one to the left of that expression
struct Expr*
Token_led(const struct Token* this, struct Parser* parser, struct Expr* left);

// gets the left binding power (lbp) of a token
// this tells us how closely the token on the left side of an operator binds to
//  that operator
enum BindingPower
Token_lbp(const struct Token* this);

// gets the type of a token
enum TokenType
Token_getType(const struct Token* this);

// gets the value of a token
int
Token_getValue(const struct Token* this);

#ifdef __cplusplus
}
#endif

#endif // TOKEN_H
