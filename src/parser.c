#include "parser.h"

void
Parser_init(struct Parser* this, struct Lexer* lexer)
{
	this->lexer = lexer;
	this->next = Lexer_next(lexer);
}

struct Expr*
Parser_parseExpr(struct Parser* this, size_t precedence)
{
	return NULL; // placeholder
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
