#ifndef EXPR_H
#define EXPR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "token.h"

// base class for expressions
struct Expr
{
	const struct Expr_vtable* vtable;
};

// integer expression, e.g. "1337"
struct IntExpr
{
	struct Expr super;
	long int value;
};

// unary operator expression, e.g. "-a"
struct UnaryExpr
{
	struct Expr super;
	enum TokenType operator;
	struct Expr* expr;
};

// binary operator expression, e.g. "a+b"
struct BinaryExpr
{
	struct Expr super;
	struct Expr* left;
	enum TokenType operator;
	struct Expr* right;
};

// Expr constructor
void
Expr_init(struct Expr* this);

// virtual destructor wrapper for Expr subclasses
void
Expr_dtor(struct Expr* this);

// virtual function wrapper for Expr subclasses
// evaluates the expression and returns its value
long int
Expr_eval(const struct Expr* this);

// virtual function wrapper for Expr subclasses
// prints the expression to the specified output stream
void
Expr_fprint(const struct Expr* this, FILE* stream);

// IntExpr constructor
void
IntExpr_init(struct IntExpr* this, long int value);

// UnaryExpr constructor
void
UnaryExpr_init(struct UnaryExpr* this, enum TokenType operator,
	struct Expr* expr);

// BinaryExpr constructor
void
BinaryExpr_init(struct BinaryExpr* this, struct Expr* left,
	enum TokenType operator, struct Expr* right);

#ifdef __cplusplus
}
#endif

#endif // EXPR_H
