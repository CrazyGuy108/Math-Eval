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

		if (type == TOKEN_NAME && isalpha(c))
		{
			const char* begin = l->pos - 1;

			while (isalpha(*l->pos))
			{
				++l->pos;
			}

			Token_init(&t, TOKEN_NAME, begin, l->pos);
			return t;
			
		}
		else if (type != TOKEN_INVALID)
		{
			Token_init(&t, type, NULL, NULL);
			return t;
		}
	}
	while (c != '\0');

	Token_init(&t, TOKEN_EOF, NULL, NULL);
	return t;
}

static enum TokenType
match(char c)
{
	switch (c)
	{
	case '(':  return TOKEN_LPAREN;
	case ')':  return TOKEN_RPAREN;
	case ',':  return TOKEN_COMMA;
	case '=':  return TOKEN_ASSIGN;
	case '+':  return TOKEN_PLUS;
	case '-':  return TOKEN_MINUS;
	case '*':  return TOKEN_ASTERISK;
	case '/':  return TOKEN_SLASH;
	case '^':  return TOKEN_CARET;
	case '~':  return TOKEN_TILDE;
	case '!':  return TOKEN_BANG;
	case '?':  return TOKEN_QUESTION;
	case ':':  return TOKEN_COLON;
	case '\0': return TOKEN_EOF;
	default:
		if (isalpha(c))
			return TOKEN_NAME;
		else
			return TOKEN_INVALID;
	}
}
