#include "expr.h"

// main vtable for Expr subclasses
struct Expr_vtable
{
	void (*dtor)(struct Expr*);
};

// destructors
static void
Expr_v_dtor(struct Expr* this);

// vtables
static const struct Expr_vtable Expr_vtable = { &Expr_v_dtor };

void
Expr_init(struct Expr* this)
{
	this->vtable = &Expr_vtable;
}

void
Expr_dtor(struct Expr* this)
{
	this->vtable->dtor(this);
}

void
Expr_v_dtor(struct Expr* this)
{
}
