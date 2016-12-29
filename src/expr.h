#ifndef EXPR_H
#define EXPR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "token.h"

// base class for expressions
struct Expr
{
	const struct Expr_vtable* vtable;
};

// Expr constructor
void
Expr_init(struct Expr* this);

// virtual destructor wrapper for Expr subclasses
void
Expr_dtor(struct Expr* this);

// integer expression
struct IntExpr
{
	struct Expr super;
	long int value;
};

// IntExpr constructor
void
IntExpr_init(struct IntExpr* this, long int value);

// unary operator expression
struct UnaryExpr
{
	struct Expr super;
	enum TokenType operator;
	struct Expr* expr;
};

// UnaryExpr constructor
void
UnaryExpr_init(struct UnaryExpr* this, enum TokenType operator,
	struct Expr* expr);

// binary operator expression
struct BinaryExpr
{
	struct Expr super;
	struct Expr* left;
	enum TokenType operator;
	struct Expr* right;
};

// BinaryExpr constructor
void
BinaryExpr_init(struct BinaryExpr* this, struct Expr* left,
	enum TokenType operator, struct Expr* right);

#ifdef __cplusplus
}
#endif

#endif // EXPR_H
