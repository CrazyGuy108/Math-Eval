#include <stdio.h>
#include "../src/mathparser.h"

int
main()
{
	// should have the same output as expr-test
	struct Lexer lexer;
	struct MathParser parser;
	Lexer_init(&lexer, "10 + (-9)");
	MathParser_init(&parser, &lexer);

	struct Expr* expr = Parser_parseExpr((struct Parser*)&parser, 0);
	Expr_fprint(expr, stdout);

	Parser_freeExpr(&expr);
	Parser_dtor((struct Parser*)&parser);
}
