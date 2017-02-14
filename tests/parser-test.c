#include <stdio.h>
#include "../src/expr.h"
#include "../src/lexer.h"
#include "../src/parser.h"

static void
test(const char* input, const char* expected);

int
main()
{
	test("10+-9", "(plus (int 10) (minus (int 9)))");
}

void
test(const char* input, const char* expected)
{
	struct Lexer lexer;
	struct Parser parser;
	// initialize the lexer and parser
	Lexer_init(&lexer, text);
	Parser_init(&parser, &lexer);
	puts("Input:");
	puts(input);
	puts("Actual Output:");
	// parse the expression and print it
	struct Expr* expr = Parser_parse(&parser, BP_MIN);
	Expr_fprint(expr, stdout);
	// expected output
	puts("\nExpected Output:");
	puts(expected);
	// destroy the expression so it doesn't take up anymore memory
	Parser_free(expr);
}
