#include "token.h"

void
Token_init(struct Token* this, enum TokenType type, long int value)
{
	this->type = type;
	this->value = value;
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
