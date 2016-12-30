#include "mathparser.h"

// operator precedences
enum Precedence
{
	PRECEDENCE_EXPONENT = 4,
	PRECEDENCE_PREFIX = 3,
	PRECEDENCE_PRODUCT = 2,
	PRECEDENCE_QUOTIENT = 2,
	PRECEDENCE_SUM = 1,
	PRECEDENCE_DIFFERENCE = 1
};

// holds all the parselets for the MathParser
struct MathParselets
{
	// prefix
	struct GroupParselet group;
	struct IntParselet integer;
	struct UnaryParselet unary_minus;

	// infix
	struct BinaryParselet exponent;
	struct BinaryParselet product;
	struct BinaryParselet quotient;
	struct BinaryParselet sum;
	struct BinaryParselet difference;
};

// MathParselets constructor
static inline void
MathParselets_init(struct MathParselets* this);

// MathParselets destructor
static inline void
MathParselets_dtor(struct MathParselets* this);

void
MathParser_init(struct MathParser* this, struct Lexer* lexer)
{
	Parser_init(&this->super, lexer);
	this->super.vtable = &MathParser_vtable;
	this->parselets = malloc(sizeof(struct MathParselets));
	if (this->parselets != NULL)
	{
		MathParselets_init(this->parselets);
	}
}

void
MathParser_v_dtor(struct MathParser* this)
{
	Parser_v_dtor(&this->super);
	MathParselets_dtor(this->parselets);
	free(this->parselets);
}

struct PrefixParselet*
MathParser_v_prefix(struct MathParser* this, enum TokenType type)
{
	switch (type)
	{
	case TOKEN_LPAREN:  return (struct PrefixParselet*)
		&this->parselets->group;
	case TOKEN_INTEGER: return (struct PrefixParselet*)
		&this->parselets->integer;
	case TOKEN_MINUS:   return (struct PrefixParselet*)
		&this->parselets->unary_minus;
	default:
		return NULL;
	}
}

struct InfixParselet*
MathParser_v_infix(struct MathParser* this, enum TokenType type)
{
	switch (type)
	{
	case TOKEN_CARET:    return (struct InfixParselet*)
		&this->parselets->exponent;
	case TOKEN_ASTERISK: return (struct InfixParselet*)
		&this->parselets->product;
	case TOKEN_SLASH:    return (struct InfixParselet*)
		&this->parselets->quotient;
	case TOKEN_PLUS:     return (struct InfixParselet*)
		&this->parselets->sum;
	case TOKEN_MINUS:    return (struct InfixParselet*)
		&this->parselets->difference;
	default:             return NULL;
	}
}

const struct Parser_vtable MathParser_vtable =
{
	(Parser_dtor_t)&MathParser_v_dtor,
	(Parser_prefix_t)&MathParser_v_prefix,
	(Parser_infix_t)&MathParser_v_infix
};

void
MathParselets_init(struct MathParselets* this)
{
	GroupParselet_init(&this->group);
	IntParselet_init(&this->integer);
	UnaryParselet_init(&this->unary_minus, PRECEDENCE_PREFIX);

	BinaryParselet_init(&this->exponent, PRECEDENCE_EXPONENT, true);
	BinaryParselet_init(&this->product, PRECEDENCE_PRODUCT, false);
	BinaryParselet_init(&this->quotient, PRECEDENCE_QUOTIENT, false);
	BinaryParselet_init(&this->sum, PRECEDENCE_SUM, false);
	BinaryParselet_init(&this->difference, PRECEDENCE_DIFFERENCE, false);
}

void
MathParselets_dtor(struct MathParselets* this)
{
	PrefixParselet_dtor((struct PrefixParselet*)&this->group);
	PrefixParselet_dtor((struct PrefixParselet*)&this->integer);
	PrefixParselet_dtor((struct PrefixParselet*)&this->unary_minus);

	InfixParselet_dtor((struct InfixParselet*)&this->exponent);
	InfixParselet_dtor((struct InfixParselet*)&this->product);
	InfixParselet_dtor((struct InfixParselet*)&this->quotient);
	InfixParselet_dtor((struct InfixParselet*)&this->sum);
	InfixParselet_dtor((struct InfixParselet*)&this->difference);
}
