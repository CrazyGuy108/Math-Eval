#include <ctype.h>
#include "lexer.h"

// matches the current input against the lexer rules
static enum TokenType
match(char input);

void
Lexer_init(struct Lexer* this, const char* src)
{
	this->src = src;
	this->pos = 0;
}

struct Token
Lexer_next(struct Lexer* this)
{
	struct Token token;
	char input;
	enum TokenType type;
	do
	{
		input = *this->src++;
		++this->pos;
		type = match(input);
		if (type != TOKEN_INVALID)
		{
			int value;
			if (type == TOKEN_INTEGER)
			{
				value = strtol(this->src - 1,
					(char**)&this->src, 0);
			}
			else
			{
				value = 0;
			}
			Token_init(&token, type, value, this->pos);
			return token;
		}
	}
	while (type != TOKEN_EOF);
	Token_init(&token, TOKEN_EOF, 0, this->pos);
	return token;
}

static enum TokenType
match(char input)
{
	switch (input)
	{
	case '(':  return TOKEN_LPAREN;
	case ')':  return TOKEN_RPAREN;
	case '+':  return TOKEN_PLUS;
	case '-':  return TOKEN_MINUS;
	case '*':  return TOKEN_ASTERISK;
	case '/':  return TOKEN_SLASH;
	case '^':  return TOKEN_CARET;
	case '\r': case '\n': case '\0': return TOKEN_EOF;
	default:   return isdigit(input) ? TOKEN_INTEGER : TOKEN_INVALID;
	}
}
