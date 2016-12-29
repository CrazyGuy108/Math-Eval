#include "expr.h"

// main vtable for Expr subclasses
struct Expr_vtable
{
	void (*dtor)(struct Expr*);
};

// destructors
static void
Expr_v_dtor(struct Expr* this);

static void
IntExpr_v_dtor(struct IntExpr* this);

// vtables
static const struct Expr_vtable Expr_vtable = { &Expr_v_dtor };
static const struct Expr_vtable IntExpr_vtable = { (void(*)(struct Expr*))
	&IntExpr_v_dtor };

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
IntExpr_init(struct IntExpr* this, long int value)
{
	Expr_init(&this->super);
	this->super.vtable = &IntExpr_vtable;
	this->value = value;
}

void
Expr_v_dtor(struct Expr* this)
{
}

void
IntExpr_v_dtor(struct IntExpr* this)
{
	Expr_v_dtor(&this->super);
}
