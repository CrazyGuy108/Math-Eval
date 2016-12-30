#include <stdio.h>
#include "../src/lexer.h"

int
main()
{
	struct Lexer lexer;
	struct Token token;
	Lexer_init(&lexer, "(-1337) - 21");
	do
	{
		token = Lexer_next(&lexer);
		printf("%s: %d\n", TokenType_toString(Token_getType(&token)),
			Token_getValue(&token));
	}
	while (Token_getType(&token) != TOKEN_EOF);
}
