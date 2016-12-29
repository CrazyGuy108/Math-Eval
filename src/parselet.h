#ifndef PARSELET_H
#define PARSELET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "parser.h"
#include "token.h"

// base class for prefix parselets
struct PrefixParselet
{
	const struct PrefixParselet_vtable* vtable;
};

// parselet for expressions grouped inside parentheses
struct GroupParselet
{
	struct PrefixParselet super;
};

// parselet for integers
struct IntParselet
{
	struct PrefixParselet super;
};

// parselet for unary operators
struct UnaryParselet
{
	struct PrefixParselet super;
	int precedence;
};

// PrefixParselet constructor
void
PrefixParselet_init(struct PrefixParselet* this);

// virtual destructor wrapper for PrefixParselet subclasses
void
PrefixParselet_dtor(struct PrefixParselet* this);

// virtual function wrapper for PrefixParselet subclasses
// generates an expression using the parser and the current token
struct Expr*
PrefixParselet_parse(struct PrefixParselet* this, struct Parser* parser,
	const struct Token* token);

// GroupParselet constructor
void
GroupParselet_init(struct GroupParselet* this);

// IntParselet constructor
void
IntParselet_init(struct IntParselet* this);

// UnaryParselet constructor
void
UnaryParselet_init(struct UnaryParselet* this, int precedence);

#ifdef __cplusplus
}
#endif

#endif // PARSELET_H
