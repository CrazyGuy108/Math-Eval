#include <stdio.h>
#include "../src/lexer.h"

int
main()
{
	struct Lexer lexer;
	// initialize lexer
	Lexer_init(&lexer, "(-1337) - 21");
	puts("Actual:");
	// print each individual token
	// the first token is printed without a comma
	struct Token token = Lexer_next(&lexer);
	printf("%s:%d", TokenType_toString(Token_getType(&token)),
		Token_getValue(&token));
	do
	{
		// all the rest are preceded by a comma
		token = Lexer_next(&lexer);
		printf(", %s:%d", TokenType_toString(Token_getType(&token)),
			Token_getValue(&token));
	}
	while (Token_getType(&token) != TOKEN_EOF);
	puts("\nExpected:\nlparen:0, minus:0, integer:1337, rparen:0, minus:0, integer:21, eof:0");
}
