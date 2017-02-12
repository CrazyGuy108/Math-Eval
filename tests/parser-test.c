#include <stdio.h>
#include "../src/expr.h"
#include "../src/lexer.h"
#include "../src/parser.h"

int
main()
{
	struct Lexer lexer;
	struct Parser parser;
	// initialize the lexer and parser
	Lexer_init(&lexer, "10+(-9)");
	Parser_init(&parser, &lexer);
	puts("Actual:");
	// parse the expression and print it
	struct Expr* expr = Parser_parse(&parser, BP_MIN);
	Expr_fprint(expr, stdout);
	// expected output
	puts("\nExpected:\n(plus (int 10) (minus (int 9)))");
	// destroy the expression so it doesn't take up anymore memory
	Parser_free(expr);
}
