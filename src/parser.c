#include <stdlib.h>
#include "parser.h"

void
Parser_init(struct Parser* this, struct Lexer* lexer)
{
	this->lexer = lexer;
	this->next = Lexer_next(lexer);
}

struct Expr*
Parser_parse(struct Parser* this, enum BindingPower rbp)
{
	struct Token t = Parser_consume(this);
	struct Expr* left = Token_nud(&t, this);
	while (rbp < Token_lbp(Parser_peek(this)))
	{
		t = Parser_consume(this);
		left = Token_led(&t, this, left);
	}
	return left;
}

void
Parser_free(struct Expr* expr)
{
	if (expr != NULL)
	{
		Expr_dtor(expr);
		free(expr);
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
