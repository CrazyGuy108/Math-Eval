#include "token.h"

static struct Expr*
nud_lparen(const struct Token* this, struct Parser* parser);

static struct Expr*
nud_rparen(const struct Token* this, struct Parser* parser);

static struct Expr*
nud_plus(const struct Token* this, struct Parser* parser);

static struct Expr*
nud_minus(const struct Token* this, struct Parser* parser);

static struct Expr*
nud_asterisk(const struct Token* this, struct Parser* parser);

static struct Expr*
nud_slash(const struct Token* this, struct Parser* parser);

static struct Expr*
nud_caret(const struct Token* this, struct Parser* parser);

static struct Expr*
nud_integer(const struct Token* this, struct Parser* parser);

static struct Expr*
nud_eof(const struct Token* this, struct Parser* parser);

static struct Expr*
nud_invalid(const struct Token* this, struct Parser* parser);

static struct Expr*
led_lparen(const struct Token* this, struct Parser* parser, struct Expr* left);

static struct Expr*
led_rparen(const struct Token* this, struct Parser* parser, struct Expr* left);

static struct Expr*
led_plus(const struct Token* this, struct Parser* parser, struct Expr* left);

static struct Expr*
led_minus(const struct Token* this, struct Parser* parser, struct Expr* left);

static struct Expr*
led_asterisk(const struct Token* this, struct Parser* parser,
	struct Expr* left);

static struct Expr*
led_slash(const struct Token* this, struct Parser* parser, struct Expr* left);

static struct Expr*
led_caret(const struct Token* this, struct Parser* parser, struct Expr* left);

static struct Expr*
led_integer(const struct Token* this, struct Parser* parser,
	struct Expr* left);

static struct Expr*
led_eof(const struct Token* this, struct Parser* parser, struct Expr* left);

static struct Expr*
led_invalid(const struct Token* this, struct Parser* parser,
	struct Expr* left);

static struct Expr* (*nud[])(const struct Token* this, struct Parser* parser) =
{
	&nud_lparen,
	&nud_rparen,
	&nud_plus,
	&nud_minus,
	&nud_asterisk,
	&nud_slash,
	&nud_caret,
	&nud_integer,
	&nud_eof,
	&nud_invalid
};

static struct Expr* (*led[])(const struct Token* this, struct Parser* parser,
	struct Expr* left) =
{
	&led_lparen,
	&led_rparen,
	&led_plus,
	&led_minus,
	&led_asterisk,
	&led_slash,
	&led_caret,
	&led_integer,
	&led_eof,
	&led_invalid
};

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
Token_init(struct Token* this, enum TokenType type, int value)
{
	this->type = type;
	this->value = value;
}

struct Expr*
Token_nud(const struct Token* this, struct Parser* parser)
{
	return nud[this->type](this, parser);
}

struct Expr*
Token_led(const struct Token* this, struct Parser* parser, struct Expr* left)
{
	return led[this->type](this, parser, left);
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
nud_lparen(const struct Token* this, struct Parser* parser)
{
	struct Expr* expr = Parser_parseExpr(parser, 0);
	struct Token rparen = Parser_consume(parser);
	if (Token_getType(&rparen) != TOKEN_RPAREN)
	{
		fprintf(stderr, "error: unmatched rparen\n");
		Parser_freeExpr(&expr);
		expr = malloc(sizeof(struct NullExpr));
		if (expr != NULL)
		{
			NullExpr_init((struct NullExpr*)expr);
		}
	}
	return expr;
}

struct Expr*
nud_rparen(const struct Token* this, struct Parser* parser)
{
	fprintf(stderr, "error: found rparen but expected an expression\n");
	struct Expr* expr = malloc(sizeof(struct NullExpr));
	if (expr != NULL)
	{
		NullExpr_init((struct NullExpr*)expr);
	}
	return expr;
}

struct Expr*
nud_plus(const struct Token* this, struct Parser* parser)
{
	struct Expr* expr = malloc(sizeof(struct UnaryExpr));
	if (expr != NULL)
	{
		UnaryExpr_init((struct UnaryExpr*)expr, TOKEN_PLUS, Parser_parseExpr(parser, 2));
	}
	return expr;
}

struct Expr*
nud_minus(const struct Token* this, struct Parser* parser)
{
	struct Expr* expr = malloc(sizeof(struct UnaryExpr));
	if (expr != NULL)
	{
		UnaryExpr_init((struct UnaryExpr*)expr, TOKEN_MINUS, Parser_parseExpr(parser, 2));
	}
	return expr;
}

struct Expr*
nud_asterisk(const struct Token* this, struct Parser* parser)
{
	fprintf(stderr, "error: asterisk is not a unary operator\n");
	struct Expr* expr = malloc(sizeof(struct NullExpr));
	if (expr != NULL)
	{
		NullExpr_init((struct NullExpr*)expr);
	}
	return expr;
}

struct Expr*
nud_slash(const struct Token* this, struct Parser* parser)
{
	fprintf(stderr, "error: slash is not a unary operator\n");
	struct Expr* expr = malloc(sizeof(struct NullExpr));
	if (expr != NULL)
	{
		NullExpr_init((struct NullExpr*)expr);
	}
	return expr;
}

struct Expr*
nud_caret(const struct Token* this, struct Parser* parser)
{
	fprintf(stderr, "error: caret is not a unary operator\n");
	struct Expr* expr = malloc(sizeof(struct NullExpr));
	if (expr != NULL)
	{
		NullExpr_init((struct NullExpr*)expr);
	}
	return expr;
}

struct Expr*
nud_integer(const struct Token* this, struct Parser* parser)
{
	struct Expr* expr = malloc(sizeof(struct IntExpr));
	if (expr != NULL)
	{
		IntExpr_init((struct IntExpr*)expr, this->value);
	}
	return expr;
}

struct Expr*
nud_eof(const struct Token* this, struct Parser* parser)
{
	fprintf(stderr, "error: found eof but expected an expression\n");
	struct Expr* expr = malloc(sizeof(struct NullExpr));
	if (expr != NULL)
	{
		NullExpr_init((struct NullExpr*)expr);
	}
	return expr;
}

struct Expr*
nud_invalid(const struct Token* this, struct Parser* parser)
{
	// pass - lexer already took care of that, or did it?
	return NULL; // placeholder
}

struct Expr*
led_lparen(const struct Token* this, struct Parser* parser, struct Expr* left)
{
	// function call or group application (wip)
	return NULL; // placeholder
}

struct Expr*
led_rparen(const struct Token* this, struct Parser* parser, struct Expr* left)
{
	fprintf(stderr, "error: extraneous rparan\n");
	struct Expr* expr = malloc(sizeof(struct NullExpr));
	if (expr != NULL)
	{
		NullExpr_init((struct NullExpr*)expr);
	}
	return expr;
}

struct Expr*
led_plus(const struct Token* this, struct Parser* parser, struct Expr* left)
{
	// add
	struct Expr* expr = malloc(sizeof(struct BinaryExpr));
	if (expr != NULL)
	{
		BinaryExpr_init((struct BinaryExpr*)expr, left, TOKEN_PLUS,
			Parser_parseExpr(parser, 1));
	}
	return expr;
}

struct Expr*
led_minus(const struct Token* this, struct Parser* parser, struct Expr* left)
{
	// subtract
	struct Expr* expr = malloc(sizeof(struct BinaryExpr));
	if (expr != NULL)
	{
		BinaryExpr_init((struct BinaryExpr*)expr, left, TOKEN_MINUS,
			Parser_parseExpr(parser, 1));
	}
	return expr;
}

struct Expr*
led_asterisk(const struct Token* this, struct Parser* parser,
	struct Expr* left)
{
	// multiply
	struct Expr* expr = malloc(sizeof(struct BinaryExpr));
	if (expr != NULL)
	{
		BinaryExpr_init((struct BinaryExpr*)expr, left, TOKEN_ASTERISK,
			Parser_parseExpr(parser, 2));
	}
	return expr;
}

struct Expr*
led_slash(const struct Token* this, struct Parser* parser, struct Expr* left)
{
	// divide
	struct Expr* expr = malloc(sizeof(struct BinaryExpr));
	if (expr != NULL)
	{
		BinaryExpr_init((struct BinaryExpr*)expr, left, TOKEN_SLASH,
			Parser_parseExpr(parser, 2));
	}
	return expr;
}

struct Expr*
led_caret(const struct Token* this, struct Parser* parser, struct Expr* left)
{
	// exponentiate
	// right-associative, so the rbp passed in is one less than caret's lbp
	struct Expr* expr = malloc(sizeof(struct BinaryExpr));
	if (expr != NULL)
	{
		BinaryExpr_init((struct BinaryExpr*)expr, left, TOKEN_CARET,
			Parser_parseExpr(parser, 2));
	}
	return expr;
}

struct Expr*
led_integer(const struct Token* this, struct Parser* parser,
	struct Expr* left)
{
	fprintf(stderr, "error: found integer but expected an operator\n");
	struct Expr* expr = malloc(sizeof(struct NullExpr));
	if (expr != NULL)
	{
		NullExpr_init((struct NullExpr*)expr);
	}
	return expr;
}

struct Expr*
led_eof(const struct Token* this, struct Parser* parser, struct Expr* left)
{
	// return back the expr, since it found the end of file
	return left;
}

struct Expr*
led_invalid(const struct Token* this, struct Parser* parser,
	struct Expr* left)
{
	// pass - lexer already took care of that, or did it?
	return NULL; // placeholder
}
