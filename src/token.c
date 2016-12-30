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
	case TOKEN_LPAREN:   return "token_lparen";
	case TOKEN_RPAREN:   return "token_rparen";
	case TOKEN_PLUS:     return "token_plus";
	case TOKEN_MINUS:    return "token_minus";
	case TOKEN_ASTERISK: return "token_asterisk";
	case TOKEN_SLASH:    return "token_slash";
	case TOKEN_CARET:    return "token_caret";
	case TOKEN_INTEGER:  return "token_integer";
	case TOKEN_EOF:      return "token_eof";
	default:             return "token_invalid";
	}
}
