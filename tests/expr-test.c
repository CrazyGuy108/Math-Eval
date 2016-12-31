#include <stdio.h>
#include "../src/expr.h"

int
main()
{
	// same as the expression "10 + (-9)"
	struct IntExpr* expr1 = malloc(sizeof(struct IntExpr));
	struct IntExpr* expr2 = malloc(sizeof(struct IntExpr));
	IntExpr_init(expr1, 10);
	IntExpr_init(expr2, 9);

	struct UnaryExpr* expr3 = malloc(sizeof(struct UnaryExpr));
	UnaryExpr_init(expr3, TOKEN_MINUS, (struct Expr*)expr2);

	struct BinaryExpr* expr = malloc(sizeof(struct BinaryExpr));
	BinaryExpr_init(expr, (struct Expr*)expr1, TOKEN_PLUS,
		(struct Expr*)expr3);

	Expr_fprint((struct Expr*)expr, stdout);

	Expr_dtor((struct Expr*)expr);
	free(expr);
}
