#include "token.h"

void
Token_init(struct Token* t, enum TokenType type, long int value)
{
	t->type = type;
	t->value = value;
}

enum TokenType
Token_getType(struct Token* t)
{
	return t->type;
}

int
Token_getValue(struct Token* t)
{
	return t->value;
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
