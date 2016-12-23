#include "lexer.h"

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
		enum TokenType type = TokenType_punctuator(c);

		if (type == TOKEN_INVALID)
		{
			if (isalpha(c))
			{
				const char* begin = l->pos - 1;

				while (isalpha(*l->pos))
				{
					++l->pos;
				}

				Token_init(&t, TOKEN_NAME, begin, l->pos);
				return t;
			}
			
		}
		else
		{
			Token_init(&t, type, NULL, NULL);
			return t;
		}
	}
	while (c != '\0');

	Token_init(&t, TOKEN_EOF, NULL, NULL);
	return t;
}
