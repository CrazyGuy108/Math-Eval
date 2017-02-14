#include <stdio.h>
#include "../src/lexer.h"

static void
test(const char* input, const char* expected);

int
main()
{
	test("(-1337) - 21", "lparen:0, minus:0, integer:1337, rparen:0, minus:0, integer:21, eof:0");
}

void
test(const char* input, const char* expected)
{
	struct Lexer lexer;
	// initialize lexer
	Lexer_init(&lexer, input);
	puts("Input:");
	puts(input);
	puts("Actual Output:");
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
	// print the expected output
	puts("\nExpected Output:");
	puts(expected);
}
