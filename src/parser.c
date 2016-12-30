#include "parser.h"

// gets the precedence of the next InfixParselet
static inline int
Parser_getPrec(struct Parser* this);

void
Parser_init(struct Parser* this, struct Lexer* lexer)
{
	this->vtable = &Parser_vtable;
	this->lexer = lexer;
	this->next = Lexer_next(lexer);
}

void
Parser_dtor(struct Parser* this)
{
	this->vtable->dtor(this);
}

struct PrefixParselet*
Parser_prefix(struct Parser* this, enum TokenType type)
{
	return this->vtable->prefix(this, type);
}

struct InfixParselet*
Parser_infix(struct Parser* this, enum TokenType type)
{
	return this->vtable->infix(this, type);
}

struct Expr*
Parser_parseExpr(struct Parser* this, size_t precedence)
{
	struct Token token = Parser_consume(this);
	struct PrefixParselet* prefix = Parser_prefix(this,
		Token_getType(&token));
	if (prefix != NULL)
	{
		struct Expr* left = PrefixParselet_parse(prefix, this, &token);
		while (precedence < Parser_getPrec(this))
		{
			token = Parser_consume(this);
			struct InfixParselet* infix = Parser_infix(this,
				Token_getType(&token));
			left = InfixParselet_parse(infix, this, left, &token);
		}

		return left;
	}
	else
	{
		fprintf(stderr, "error!\n"); // placeholder
		return NULL;
	}
}

void
Parser_freeExpr(struct Expr** expr)
{
	if (expr != NULL && *expr != NULL)
	{
		Expr_dtor(*expr);
		free(*expr);
		*expr = NULL;
	}
}

struct Token
Parser_consume(struct Parser* this)
{
	struct Token tmp = this->next;
	this->next = Lexer_next(this->lexer);
	return tmp;
}

const struct Token*
Parser_peek(const struct Parser* this)
{
	return &this->next;
}

void
Parser_v_dtor(struct Parser* this)
{
}

const struct Parser_vtable Parser_vtable = { NULL, NULL, NULL };

int
Parser_getPrec(struct Parser* this)
{
	struct InfixParselet* infix = Parser_infix(this,
		Token_getType(Parser_peek(this)));
	return infix != NULL ? InfixParselet_getPrec(infix) : 0;
}
