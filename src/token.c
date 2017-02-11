#include "token.h"

static struct Expr*
Token_error(const struct Token* this, const char* msg);

const char*
TokenType_toString(enum TokenType type)
{
	switch (type)
	{
	case TOKEN_LPAREN:   return "lparen";
	case TOKEN_RPAREN:   return "rparen";
	case TOKEN_PLUS:     return "plus";
	case TOKEN_MINUS:    return "minus";
	case TOKEN_ASTERISK: return "asterisk";
	case TOKEN_SLASH:    return "slash";
	case TOKEN_CARET:    return "caret";
	case TOKEN_INTEGER:  return "integer";
	case TOKEN_EOF:      return "eof";
	default:             return "invalid";
	}
}

void
Token_init(struct Token* this, enum TokenType type, int value, size_t pos)
{
	this->type = type;
	this->value = value;
	this->pos = pos;
}

struct Expr*
Token_nud(const struct Token* this, struct Parser* parser)
{
	struct Expr* expr;
	switch (this->type)
	{
	case TOKEN_LPAREN:
		expr = Parser_parse(parser, 0);
		if (Parser_consume(parser).type != TOKEN_RPAREN)
		{
			expr = Token_error(this, "unmatched rparen");
		}
		break;
	case TOKEN_RPAREN:
		expr = Token_error(this,
			"found rparen but expected an expression");
		break;
	case TOKEN_PLUS:
	case TOKEN_MINUS:
		expr = malloc(sizeof(struct UnaryExpr));
		if (expr != NULL)
		{
			UnaryExpr_init((struct UnaryExpr*)expr, this->type,
				Parser_parse(parser, 2));
		}
		break;
	case TOKEN_ASTERISK:
		expr = Token_error(this, "asterisk is not a unary operator");
		break;
	case TOKEN_SLASH:
		expr = Token_error(this, "slash is not a unary operator");
		break;
	case TOKEN_CARET:
		expr = Token_error(this, "caret is not a unary operator");
		break;
	case TOKEN_INTEGER:
		expr = malloc(sizeof(struct IntExpr));
		if (expr != NULL)
		{
			IntExpr_init((struct IntExpr*)expr, this->value);
		}
		break;
	case TOKEN_EOF:
		expr = Token_error(this,
			"found eof but expected an expression");
		break;
	default:
		expr = Token_error(this, "internal lexer error!!!");
	}
	return expr;
}

struct Expr*
Token_led(const struct Token* this, struct Parser* parser, struct Expr* left)
{
	struct Expr* expr;
	switch (this->type)
	{
	case TOKEN_LPAREN:
		expr = Token_error(this, "extraneous lparen");
		break;
	case TOKEN_RPAREN:
		expr = Token_error(this, "extraneous rparen");
		break;
	case TOKEN_PLUS:
	case TOKEN_MINUS:
	case TOKEN_ASTERISK:
	case TOKEN_SLASH:
	case TOKEN_CARET:
		expr = malloc(sizeof(struct BinaryExpr));
		if (expr != NULL)
		{
			BinaryExpr_init((struct BinaryExpr*)expr, left,
				this->type, Parser_parse(parser, 2));
		}
		break;
	case TOKEN_INTEGER:
		expr = Token_error(this,
			"found integer but expected an operator");
		break;
	case TOKEN_EOF:
		// return back the expr, since it found the end of file
		expr = left;
		break;
	default:
		expr = Token_error(this, "internal lexer error!!!");
	}
	return expr;
}

int
Token_lbp(const struct Token* this)
{
	switch (this->type)
	{
	case TOKEN_LPAREN:   return 0;
	case TOKEN_RPAREN:   return 0;
	case TOKEN_PLUS:     return 1;
	case TOKEN_MINUS:    return 1;
	case TOKEN_ASTERISK: return 2;
	case TOKEN_SLASH:    return 2;
	case TOKEN_CARET:    return 3;
	case TOKEN_INTEGER:  return 0;
	case TOKEN_EOF:      return 0;
	default:             return 0;
	}
}

enum TokenType
Token_getType(const struct Token* this)
{
	return this->type;
}

int
Token_getValue(const struct Token* this)
{
	return this->value;
}

struct Expr*
Token_error(const struct Token* this, const char* msg)
{
	fprintf(stderr, "error(%zu): %s\n", this->pos, msg);
	struct Expr* expr = malloc(sizeof(struct NullExpr));
	if (expr != NULL)
	{
		NullExpr_init((struct NullExpr*)expr);
	}
	return expr;
}
