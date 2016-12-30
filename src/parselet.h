#ifndef PARSELET_H
#define PARSELET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
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

// base class for infix parselets
struct InfixParselet
{
	const struct InfixParselet_vtable* vtable;
};

// parselet for binary operators
struct BinaryParselet
{
	struct InfixParselet super;
	int precedence;
	bool associativity;
};

// InfixParselet constructor
void
InfixParselet_init(struct InfixParselet* this);

// virtual destructor wrapper for InfixParselet subclasses
void
InfixParselet_dtor(struct InfixParselet* this);

// virtual function wrapper for InfixParselet subclasses
// generates an expression using the parser, left operand,
// and the operator token
struct Expr*
InfixParselet_parse(struct InfixParselet* this, struct Parser* parser,
	struct Expr* left, const struct Token* token);

// virtual function wrapper for InfixParselet subclasses
// gets the precedence of the operator that the parselet will be parsing
int
InfixParselet_getPrec(struct InfixParselet* this);

// BinaryParselet constructor
void
BinaryParselet_init(struct BinaryParselet* this, int precedence,
	bool associativity);

#ifdef __cplusplus
}
#endif

#endif // PARSELET_H
