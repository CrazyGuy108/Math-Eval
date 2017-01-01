#ifndef TOKEN_H
#define TOKEN_H

#ifdef __cplusplus
extern "C" {
#endif

// the type of token that a Token can represent
enum TokenType
{
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_ASTERISK,
	TOKEN_SLASH,
	TOKEN_CARET,
	TOKEN_INTEGER,
	TOKEN_EOF,
	TOKEN_INVALID
};

// represents a single immutable lexer token
// the value member is for integer types
struct Token
{
	enum TokenType type;
	int value;
};

// Token constructor
void
Token_init(struct Token* this, enum TokenType type, int value);

// getter for type
enum TokenType
Token_getType(const struct Token* this);

// getter for value
int
Token_getValue(const struct Token* this);

// converts a TokenType to a string
const char*
TokenType_toString(enum TokenType type);

#ifdef __cplusplus
}
#endif

#endif // TOKEN_H
