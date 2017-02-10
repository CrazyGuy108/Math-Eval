#include <stdio.h>
#include "../src/mathparser.h"

int
main()
{
	// should have the same output as expr-test
	struct Lexer lexer;
	struct Parser parser;
	Lexer_init(&lexer, "10 + (-9)");
	Parser_init(&parser, &lexer);

	struct Expr* expr = Parser_parseExpr(&parser, 0);
	Expr_fprint(expr, stdout);

	Parser_freeExpr(&expr);
	Parser_dtor((struct Parser*)&parser);
}
