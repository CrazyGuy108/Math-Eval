#include "parselet.h"

// convenient typedefs for really long function pointers
typedef void (*PrefixParselet_dtor_t)(struct PrefixParselet*);
typedef struct Expr* (*PrefixParselet_parse_t)(struct PrefixParselet*,
	struct Parser*, const struct Token*);

// main vtable for PrefixParselet subclasses
struct PrefixParselet_vtable
{
	PrefixParselet_dtor_t dtor;
	PrefixParselet_parse_t parse;
};

// protected virtual functions
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
const struct PrefixParselet_vtable PrefixParselet_vtable = { NULL, NULL };
const struct PrefixParselet_vtable GroupParselet_vtable =
{
	(PrefixParselet_dtor_t)&GroupParselet_v_dtor,
	(PrefixParselet_parse_t)&GroupParselet_v_parse
};
const struct PrefixParselet_vtable IntParselet_vtable =
{
	(PrefixParselet_dtor_t)&IntParselet_v_dtor,
	(PrefixParselet_parse_t)&IntParselet_v_parse
};
const struct PrefixParselet_vtable UnaryParselet_vtable =
{
	(PrefixParselet_dtor_t)&UnaryParselet_v_dtor,
	(PrefixParselet_parse_t)&UnaryParselet_v_parse
};

// public functions

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

// protected virtual functions

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
	return NULL; // placeholder
}

static struct Expr*
IntParselet_v_parse(struct IntParselet* this, struct Parser* parser,
	const struct Token* token)
{
	return NULL; // placeholder
}

static struct Expr*
UnaryParselet_v_parse(struct UnaryParselet* this, struct Parser* parser,
	const struct Token* token)
{
	return NULL; // placeholder
}
