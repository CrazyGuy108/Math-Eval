#include <stdio.h>
#include "../src/expr.h"

int
main()
{
	// same as the expression "10 + (-9)"
	struct IntExpr expr1;
	struct IntExpr expr2;
	struct UnaryExpr expr3;
	struct BinaryExpr expr;
	IntExpr_init(&expr1, 9);
	IntExpr_init(&expr2, 10);
	UnaryExpr_init(&expr3, TOKEN_MINUS, (struct Expr*)&expr1);
	BinaryExpr_init(&expr, (struct Expr*)&expr2, TOKEN_PLUS,
		(struct Expr*)&expr3);
	Expr_fprint((struct Expr*)&expr, stdout);
	Expr_dtor((struct Expr*)&expr);
}
