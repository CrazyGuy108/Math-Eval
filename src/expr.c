#include "expr.h"

typedef void (*Expr_dtor_t)(struct Expr*);
typedef void (*Expr_fprint_t)(struct Expr*, FILE*);

// main vtable for Expr subclasses
struct Expr_vtable
{
	Expr_dtor_t dtor;
	Expr_fprint_t fprint;
};

static void
Expr_v_dtor(struct Expr* this);

static void
IntExpr_v_dtor(struct IntExpr* this);

static void
UnaryExpr_v_dtor(struct UnaryExpr* this);

static void
BinaryExpr_v_dtor(struct BinaryExpr* this);

static void
IntExpr_v_fprint(struct IntExpr* this, FILE* stream);

static void
UnaryExpr_v_fprint(struct UnaryExpr* this, FILE* stream);

static void
BinaryExpr_v_fprint(struct BinaryExpr* this, FILE* stream);

// vtables
static const struct Expr_vtable Expr_vtable = \
{
	NULL,
	NULL
};
static const struct Expr_vtable IntExpr_vtable =
{
	(Expr_dtor_t)&IntExpr_v_dtor,
	(Expr_fprint_t)&IntExpr_v_fprint
};
static const struct Expr_vtable UnaryExpr_vtable =
{
	(Expr_dtor_t)&UnaryExpr_v_dtor,
	(Expr_fprint_t)&UnaryExpr_v_fprint
};
static const struct Expr_vtable BinaryExpr_vtable =
{
	(Expr_dtor_t)&BinaryExpr_v_dtor,
	(Expr_fprint_t)&BinaryExpr_v_fprint
};

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
Expr_fprint(struct Expr* this, FILE* stream)
{
	this->vtable->fprint(this, stream);
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

void
IntExpr_v_fprint(struct IntExpr* this, FILE* stream)
{
	fprintf(stream, "(int %ld)", this->value);
}

void
UnaryExpr_v_fprint(struct UnaryExpr* this, FILE* stream)
{
	fprintf(stream, "(%s ", TokenType_toString(this->operator));
	Expr_fprint(this->expr, stream);
	fprintf(stream, ")");
}

void
BinaryExpr_v_fprint(struct BinaryExpr* this, FILE* stream)
{
	fprintf(stream, "(%s ", TokenType_toString(this->operator));
	Expr_fprint(this->left, stream);
	fprintf(stream, " ");
	Expr_fprint(this->right, stream);
	fprintf(stream, ")");
}
