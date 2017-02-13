#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "lexer.h"

static int
Lexer_parseInt(struct Lexer* this);

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
	if (*this->src != '\0')
	{
		char input;
		enum TokenType type;
		do
		{
			input = *this->src++;
			++this->pos;
			type = match(input);
			if (type != TOKEN_INVALID)
			{
				int value = type != TOKEN_INTEGER ? 0
					: Lexer_parseInt(this);
				Token_init(&token, type, value, this->pos);
				return token;
			}
		}
		while (type != TOKEN_EOF);
	}
	Token_init(&token, TOKEN_EOF, 0, this->pos);
	return token;
}

int
Lexer_parseInt(struct Lexer* this)
{
	errno = 0;
	char* endp;
	long value = strtol(this->src - 1, &endp, 0);
	if (this->src - 1 == endp) // should never happen
	{
		fprintf(stderr, "error(%d): could not parse integer\n",
			this->pos);
	}
	else if (errno == ERANGE || value < INT_MIN || value > INT_MAX)
	{
		fprintf(stderr, "error(%d): integer too large\n",
			this->pos);
	}
	this->pos += endp - this->src;
	this->src = (const char*)endp;
	return (int)value;
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
	case '%':  return TOKEN_MODULO;
	case '^':  return TOKEN_CARET;
	case '\r': case '\n': case '\0': return TOKEN_EOF;
	default:   return isdigit(input) ? TOKEN_INTEGER : TOKEN_INVALID;
	}
}
