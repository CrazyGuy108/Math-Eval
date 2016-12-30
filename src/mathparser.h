#ifndef MATHPARSER_H
#define MATHPARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "parser.h"

// subclass of Parser, for parsing math expressions
struct MathParser
{
	struct Parser super;
	struct MathParselets* parselets;
};

// constructor
void
MathParser_init(struct MathParser* this, struct Lexer* lexer);

// destructor
void
MathParser_v_dtor(struct MathParser* this);

// Parser_prefix override
struct PrefixParselet*
MathParser_v_prefix(struct MathParser* this, enum TokenType type);

// Parser_infix override
struct InfixParselet*
MathParser_v_infix(struct MathParser* this, enum TokenType type);

extern const struct Parser_vtable MathParser_vtable;

#ifdef __cplusplus
}
#endif

#endif // MATHPARSER_H
