#include "parselet.h"

// PrefixParselet section

typedef void (*PrefixParselet_dtor_t)(struct PrefixParselet*);
typedef struct Expr* (*PrefixParselet_parse_t)(struct PrefixParselet*,
	struct Parser*, const struct Token*);

struct PrefixParselet_vtable
{
	PrefixParselet_dtor_t dtor;
	PrefixParselet_parse_t parse;
};

static void
PrefixParselet_v_dtor(struct PrefixParselet* this);

static void
GroupParselet_v_dtor(struct GroupParselet* this);

static void
IntParselet_v_dtor(struct IntParselet* this);

static void
UnaryParselet_v_dtor(struct UnaryParselet* this);

static struct Expr*
GroupParselet_v_parse(struct GroupParselet* this, struct Parser* parser,
	const struct Token* token);

static struct Expr*
IntParselet_v_parse(struct IntParselet* this, struct Parser* parser,
	const struct Token* token);

static struct Expr*
UnaryParselet_v_parse(struct UnaryParselet* this, struct Parser* parser,
	const struct Token* token);

// vtables
static const struct PrefixParselet_vtable PrefixParselet_vtable =
{
	NULL,
	NULL
};
static const struct PrefixParselet_vtable GroupParselet_vtable =
{
	(PrefixParselet_dtor_t)&GroupParselet_v_dtor,
	(PrefixParselet_parse_t)&GroupParselet_v_parse
};
static const struct PrefixParselet_vtable IntParselet_vtable =
{
	(PrefixParselet_dtor_t)&IntParselet_v_dtor,
	(PrefixParselet_parse_t)&IntParselet_v_parse
};
static const struct PrefixParselet_vtable UnaryParselet_vtable =
{
	(PrefixParselet_dtor_t)&UnaryParselet_v_dtor,
	(PrefixParselet_parse_t)&UnaryParselet_v_parse
};

void
PrefixParselet_init(struct PrefixParselet* this)
{
	this->vtable = &PrefixParselet_vtable;
}

void
PrefixParselet_dtor(struct PrefixParselet* this)
{
	this->vtable->dtor(this);
}

struct Expr*
PrefixParselet_parse(struct PrefixParselet* this, struct Parser* parser,
	const struct Token* token)
{
	return this->vtable->parse(this, parser, token);
}

void
GroupParselet_init(struct GroupParselet* this)
{
	PrefixParselet_init(&this->super);
	this->super.vtable = &GroupParselet_vtable;
}

void
IntParselet_init(struct IntParselet* this)
{
	PrefixParselet_init(&this->super);
	this->super.vtable = &IntParselet_vtable;
}

void
UnaryParselet_init(struct UnaryParselet* this, int precedence)
{
	PrefixParselet_init(&this->super);
	this->super.vtable = &UnaryParselet_vtable;
	this->precedence = precedence;
}

void
PrefixParselet_v_dtor(struct PrefixParselet* this)
{
}

void
GroupParselet_v_dtor(struct GroupParselet* this)
{
	PrefixParselet_v_dtor(&this->super);
}

void
IntParselet_v_dtor(struct IntParselet* this)
{
	PrefixParselet_v_dtor(&this->super);
}

void
UnaryParselet_v_dtor(struct UnaryParselet* this)
{
	PrefixParselet_v_dtor(&this->super);
}

static struct Expr*
GroupParselet_v_parse(struct GroupParselet* this, struct Parser* parser,
	const struct Token* token)
{
	struct Expr* expr = Parser_parseExpr(parser, 0);
	struct Token rparen = Parser_consume(parser);
	if (Token_getType(&rparen) != TOKEN_RPAREN)
	{
		fprintf(stderr, "error!\n"); // placeholder
		return NULL;
	}
	else
	{
		return expr;
	}
}

static struct Expr*
IntParselet_v_parse(struct IntParselet* this, struct Parser* parser,
	const struct Token* token)
{
	struct IntExpr* expr = malloc(sizeof(struct IntExpr));
	if (expr != NULL)
	{
		IntExpr_init(expr, Token_getValue(token));
	}
	return (struct Expr*)expr;
}

static struct Expr*
UnaryParselet_v_parse(struct UnaryParselet* this, struct Parser* parser,
	const struct Token* token)
{
	struct UnaryExpr* expr = malloc(sizeof(struct UnaryExpr));
	if (expr != NULL)
	{
		UnaryExpr_init(expr, Token_getType(token),
			Parser_parseExpr(parser, this->precedence));
	}
	return (struct Expr*)expr;
}

// InfixParselet section

typedef void (*InfixParselet_dtor_t)(struct InfixParselet*);
typedef struct Expr* (*InfixParselet_parse_t)(struct InfixParselet*,
	struct Parser*, struct Expr*, const struct Token*);
typedef int (*InfixParselet_getPrec_t)(struct InfixParselet* this);

struct InfixParselet_vtable
{
	InfixParselet_dtor_t dtor;
	InfixParselet_parse_t parse;
	InfixParselet_getPrec_t getPrec;
};

static void
InfixParselet_v_dtor(struct InfixParselet* this);

static void
BinaryParselet_v_dtor(struct BinaryParselet* this);

static struct Expr*
BinaryParselet_v_parse(struct BinaryParselet* this, struct Parser* parser,
	struct Expr* left, const struct Token* token);

static int
BinaryParselet_v_getPrec(struct BinaryParselet* this);

static const struct InfixParselet_vtable InfixParselet_vtable =
{
	NULL,
	NULL,
	NULL
};
static const struct InfixParselet_vtable BinaryParselet_vtable =
{
	(InfixParselet_dtor_t)&BinaryParselet_v_dtor,
	(InfixParselet_parse_t)&BinaryParselet_v_parse,
	(InfixParselet_getPrec_t)&BinaryParselet_v_getPrec
};

void
InfixParselet_init(struct InfixParselet* this)
{
	this->vtable = &InfixParselet_vtable;
}

void
InfixParselet_dtor(struct InfixParselet* this)
{
	this->vtable->dtor(this);
}

struct Expr*
InfixParselet_parse(struct InfixParselet* this, struct Parser* parser,
	struct Expr* left, const struct Token* token)
{
	return this->vtable->parse(this, parser, left, token);
}

int
InfixParselet_getPrec(struct InfixParselet* this)
{
	return this->vtable->getPrec(this);
}

void
BinaryParselet_init(struct BinaryParselet* this, int precedence,
	bool associativity)
{
	InfixParselet_init(&this->super);
	this->super.vtable = &BinaryParselet_vtable;
	this->precedence = precedence;
	this->associativity = associativity;
}

void
InfixParselet_v_dtor(struct InfixParselet* this)
{
}

void
BinaryParselet_v_dtor(struct BinaryParselet* this)
{
	InfixParselet_v_dtor(&this->super);
}

struct Expr*
BinaryParselet_v_parse(struct BinaryParselet* this, struct Parser* parser,
	struct Expr* left, const struct Token* token)
{
	struct BinaryExpr* expr = malloc(sizeof(struct BinaryExpr));
	if (expr != NULL)
	{
		BinaryExpr_init(expr, left, Token_getType(token),
			Parser_parseExpr(parser, this->precedence -
				(this->associativity ? 1 : 0)));
	}
	return (struct Expr*)expr;
}

int
BinaryParselet_v_getPrec(struct BinaryParselet* this)
{
	return this->precedence;
}
