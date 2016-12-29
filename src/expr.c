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

static void
UnaryExpr_v_dtor(struct UnaryExpr* this);

static void
BinaryExpr_v_dtor(struct BinaryExpr* this);

// vtables
static const struct Expr_vtable Expr_vtable = { &Expr_v_dtor };
static const struct Expr_vtable IntExpr_vtable = { (void(*)(struct Expr*))
	&IntExpr_v_dtor };
static const struct Expr_vtable UnaryExpr_vtable = { (void(*)(struct Expr*))
	&UnaryExpr_v_dtor };
static const struct Expr_vtable BinaryExpr_vtable = { (void(*)(struct Expr*))
	&BinaryExpr_v_dtor };

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
UnaryExpr_init(struct UnaryExpr* this, enum TokenType operator,
	struct Expr* expr)
{
	Expr_init(&this->super);
	this->super.vtable = &UnaryExpr_vtable;
	this->operator = operator;
	this->expr = expr;
}

void
BinaryExpr_init(struct BinaryExpr* this, struct Expr* left,
	enum TokenType operator, struct Expr* right)
{
	Expr_init(&this->super);
	this->super.vtable = &BinaryExpr_vtable;
	this->left = left;
	this->operator = operator;
	this->right = right;
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

void
UnaryExpr_v_dtor(struct UnaryExpr* this)
{
	Expr_v_dtor(&this->super);
	if (this->expr != NULL)
	{
		Expr_dtor(this->expr);
		free(this->expr);
	}
}

void
BinaryExpr_v_dtor(struct BinaryExpr* this)
{
	Expr_v_dtor(&this->super);
	if (this->left != NULL)
	{
		Expr_dtor(this->left);
		free(this->left);
	}
	if (this->right != NULL)
	{
		Expr_dtor(this->right);
		free(this->right);
	}
}
