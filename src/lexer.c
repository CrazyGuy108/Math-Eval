#include "lexer.h"

// matches the current input against the lexer rules
static enum TokenType
match(char input);

void
Lexer_init(struct Lexer* this, const char* source)
{
	this->pos = source;
}

struct Token
Lexer_next(struct Lexer* this)
{
	struct Token token;
	char input;
	do
	{
		input = *this->pos++;
		enum TokenType type = match(input);
		if (type != TOKEN_INVALID)
		{
			int value;
			if (type == TOKEN_INTEGER)
			{
				value = strtol(this->pos - 1,
					(char**)&this->pos, 0);
			}
			else
			{
				value = 0;
			}
			Token_init(&token, type, value);
			return token;
		}
	}
	while (input != '\0');
	Token_init(&token, TOKEN_EOF, 0);
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
	case '\0': return TOKEN_EOF;
	default:   return isdigit(input) ? TOKEN_INTEGER : TOKEN_INVALID;
	}
}
