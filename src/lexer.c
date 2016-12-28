#include "lexer.h"

// matches the current input against the lexer rules
static enum TokenType
match(char c);

void
Lexer_init(struct Lexer* l, const char* source)
{
	l->pos = source;
}

struct Token
Lexer_next(struct Lexer* l)
{
	struct Token t;
	char c;
	do
	{
		c = *l->pos++;
		enum TokenType type = match(c);
		if (type != TOKEN_INVALID)
		{
			int value;
			if (type == TOKEN_INTEGER)
			{
				value = strtol(l->pos - 1, (char**)&l->pos, 0);
			}
			else
			{
				value = 0;
			}
			Token_init(&t, type, value);
			return t;
		}
	}
	while (c != '\0');
	Token_init(&t, TOKEN_EOF, 0);
	return t;
}

static enum TokenType
match(char c)
{
	switch (c)
	{
	case '(':  return TOKEN_LPAREN;
	case ')':  return TOKEN_RPAREN;
	case '+':  return TOKEN_PLUS;
	case '-':  return TOKEN_MINUS;
	case '*':  return TOKEN_ASTERISK;
	case '/':  return TOKEN_SLASH;
	case '^':  return TOKEN_CARET;
	case '\0': return TOKEN_EOF;
	default:   return isdigit(c) ? TOKEN_INTEGER : TOKEN_INVALID;
	}
}
