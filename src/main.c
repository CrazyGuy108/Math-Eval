#include <stdio.h>
#include <string.h>
#include "parser.h"

int
main()
{
	char input[256];
	while (1)
	{
		fputs(">", stdout);
		fgets(input, sizeof(input), stdin);
		if (input[0] == '\n')
		{
			break;
		}
		fseek(stdin, 0, SEEK_END);

		struct Lexer lexer;
		struct Parser parser;
		Lexer_init(&lexer, input);
		Parser_init(&parser, &lexer);
		struct Expr* expr =
			Parser_parseExpr((struct Parser*)&parser, 0);
		printf("%d\n", Expr_eval(expr));
		Parser_freeExpr(&expr);
	}
}
