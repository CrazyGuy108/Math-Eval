#include "expr.h"

// computes the integer power
static int
powi(int base, int exponent);

// computes the factorial of a number
static int
facti(int n);

typedef void (*Expr_dtor_t)(struct Expr*);
typedef int (*Expr_eval_t)(const struct Expr*);
typedef void (*Expr_fprint_t)(const struct Expr*, FILE*);

// main vtable for Expr subclasses
struct Expr_vtable
{
	Expr_dtor_t dtor;
	Expr_eval_t eval;
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
NullExpr_v_dtor(struct NullExpr* this);

static int
IntExpr_v_eval(const struct IntExpr* this);

static int
UnaryExpr_v_eval(const struct UnaryExpr* this);

static int
BinaryExpr_v_eval(const struct BinaryExpr* this);

static int
NullExpr_v_eval(const struct NullExpr* this);

static void
IntExpr_v_fprint(const struct IntExpr* this, FILE* stream);

static void
UnaryExpr_v_fprint(const struct UnaryExpr* this, FILE* stream);

static void
BinaryExpr_v_fprint(const struct BinaryExpr* this, FILE* stream);

static void
NullExpr_v_fprint(const struct NullExpr* this, FILE* stream);

// vtables
static const struct Expr_vtable Expr_vtable =
{
	NULL,
	NULL,
	NULL
};
static const struct Expr_vtable IntExpr_vtable =
{
	(Expr_dtor_t)&IntExpr_v_dtor,
	(Expr_eval_t)&IntExpr_v_eval,
	(Expr_fprint_t)&IntExpr_v_fprint
};
static const struct Expr_vtable UnaryExpr_vtable =
{
	(Expr_dtor_t)&UnaryExpr_v_dtor,
	(Expr_eval_t)&UnaryExpr_v_eval,
	(Expr_fprint_t)&UnaryExpr_v_fprint
};
static const struct Expr_vtable BinaryExpr_vtable =
{
	(Expr_dtor_t)&BinaryExpr_v_dtor,
	(Expr_eval_t)&BinaryExpr_v_eval,
	(Expr_fprint_t)&BinaryExpr_v_fprint
};

static const struct Expr_vtable NullExpr_vtable =
{
	(Expr_dtor_t)&NullExpr_v_dtor,
	(Expr_eval_t)&NullExpr_v_eval,
	(Expr_fprint_t)&NullExpr_v_fprint
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

int
Expr_eval(const struct Expr* this)
{
	return this->vtable->eval(this);
}

void
Expr_fprint(const struct Expr* this, FILE* stream)
{
	this->vtable->fprint(this, stream);
}

void
IntExpr_init(struct IntExpr* this, int value)
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
NullExpr_init(struct NullExpr* this)
{
	Expr_init(&this->super);
	this->super.vtable = &NullExpr_vtable;
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
NullExpr_v_dtor(struct NullExpr* this)
{
	Expr_v_dtor(&this->super);
}

int
IntExpr_v_eval(const struct IntExpr* this)
{
	return this->value;
}

int
UnaryExpr_v_eval(const struct UnaryExpr* this)
{
	int expr = Expr_eval(this->expr);
	switch (this->operator)
	{
	case TOKEN_FACT:  return facti(expr);
	case TOKEN_PLUS:  return expr;
	case TOKEN_MINUS: return -expr;
	default:          return 0;
	}
}

int
BinaryExpr_v_eval(const struct BinaryExpr* this)
{
	int left = Expr_eval(this->left);
	int right = Expr_eval(this->right);
	switch (this->operator)
	{
	case TOKEN_CARET:    return powi(left, right);
	case TOKEN_ASTERISK: return left * right;
	case TOKEN_SLASH:    return left / right;
	case TOKEN_MODULO:   return left % right;
	case TOKEN_PLUS:     return left + right;
	case TOKEN_MINUS:    return left - right;
	default:             return 0;
	}
}

int
NullExpr_v_eval(const struct NullExpr* this)
{
	return 0;
}

void
IntExpr_v_fprint(const struct IntExpr* this, FILE* stream)
{
	fprintf(stream, "(int %ld)", this->value);
}

void
UnaryExpr_v_fprint(const struct UnaryExpr* this, FILE* stream)
{
	fprintf(stream, "(%s ", TokenType_toString(this->operator));
	Expr_fprint(this->expr, stream);
	fprintf(stream, ")");
}

void
BinaryExpr_v_fprint(const struct BinaryExpr* this, FILE* stream)
{
	fprintf(stream, "(%s ", TokenType_toString(this->operator));
	Expr_fprint(this->left, stream);
	fprintf(stream, " ");
	Expr_fprint(this->right, stream);
	fprintf(stream, ")");
}

void
NullExpr_v_fprint(const struct NullExpr* this, FILE* stream)
{
	fprintf(stream, "null");
}

int
powi(int base, int exp)
{
	if (exp < 0)
	{
		return 0; // basically rounding negative exponents
	}
	// O(1) space, O(log(n)) time
	int result = 1;
	while (exp != 0)
	{
		if (exp % 2 == 1)
		{
			result *= base;
		}
		base *= base;
		exp /= 2;
	}
	return result;
}

int
facti(int n)
{
	int result = 1;
	for (int i = 2; i <= n; ++i)
	{
		result *= i;
	}
	return result;
}
