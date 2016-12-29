#ifndef EXPR_H
#define EXPR_H

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif // EXPR_H
