#include "token.h"

void
Token_init(struct Token* t, enum TokenType type, const char* begin, const char* end)
{
	t->type = type;
	t->begin = begin;
	t->end = end;
}

enum TokenType
Token_getType(struct Token* t)
{
	return t->type;
}

const char*
Token_getBegin(struct Token* t)
{
	return t->begin;
}

const char*
Token_getEnd(struct Token* t)
{
	return t->end;
}

const char*
TokenType_toString(enum TokenType type)
{
	switch (type)
	{
	case TOKEN_LPAREN:   return "token_lparen";
	case TOKEN_RPAREN:   return "token_rparen";
	case TOKEN_COMMA:    return "token_comma";
	case TOKEN_ASSIGN:   return "token_assign";
	case TOKEN_PLUS:     return "token_plus";
	case TOKEN_MINUS:    return "token_minus";
	case TOKEN_ASTERISK: return "token_asterisk";
	case TOKEN_SLASH:    return "token_slash";
	case TOKEN_CARET:    return "token_caret";
	case TOKEN_TILDE:    return "token_tilde";
	case TOKEN_BANG:     return "token_bang";
	case TOKEN_QUESTION: return "token_question";
	case TOKEN_COLON:    return "token_colon";
	case TOKEN_NAME:     return "token_name";
	case TOKEN_EOF:      return "token_eof";
	default:             return "token_invalid";
	}
}
