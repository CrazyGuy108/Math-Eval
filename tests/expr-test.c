#include <stdio.h>
#include "../src/expr.h"

int
main()
{
	// initialize the integers 10 and 9
	struct Expr* expr1 = malloc(sizeof(struct IntExpr));
	struct Expr* expr2 = malloc(sizeof(struct IntExpr));
	IntExpr_init((struct IntExpr*)expr1, 10);
	IntExpr_init((struct IntExpr*)expr2, 9);
	// apply a unary minus to the 9
	struct Expr* expr3 = malloc(sizeof(struct UnaryExpr));
	UnaryExpr_init((struct UnaryExpr*)expr3, TOKEN_MINUS, expr2);
	// apply a binary plus to 10 and -9
	struct Expr* expr = malloc(sizeof(struct BinaryExpr));
	BinaryExpr_init((struct BinaryExpr*)expr, expr1, TOKEN_PLUS, expr3);
	// evaluate the expression
	printf("Actual:\n%d\nExpected:\n1\n", Expr_eval(expr));
	// destroy the expression so it doesnt take up anymore memory
	Expr_dtor(expr);
	free(expr);
}
