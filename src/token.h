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
	TOKEN_COMMA,
	TOKEN_ASSIGN,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_ASTERISK,
	TOKEN_SLASH,
	TOKEN_CARET,
	TOKEN_TILDE,
	TOKEN_BANG,
	TOKEN_QUESTION,
	TOKEN_COLON,
	TOKEN_NAME,
	TOKEN_EOF,
	TOKEN_INVALID
};

// represents a single immutable lexer token
// use the provided functions instead of the struct members
struct Token
{
	enum TokenType type;
	const char* begin;
	const char* end;
};

// initializes a Token
void
Token_init(struct Token* t, enum TokenType type, const char* begin, const char* end);

// getter for type
enum TokenType
Token_getType(struct Token* t);

// getter for begin
const char*
Token_getBegin(struct Token* t);

// getter for end
const char*
Token_getEnd(struct Token* t);

// converts a TokenType to a string
const char*
TokenType_toString(enum TokenType type);

// converts a punctuation character into a TokenType
// includes symbols and operators but not names
enum TokenType
TokenType_punctuator(char c);

#ifdef __cplusplus
}
#endif

#endif // TOKEN_H
