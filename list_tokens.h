/*
 * tokens.h
 *
 */

#ifndef LIST_TOKENS_H_
#define LIST_TOKENS_H_

#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;

enum TokenType {
		// keywords
	PRINT,
	SET,
	IF,
	LOOP,
	BEGIN,
	END,

		// an identifier
	ID,

		// an integer and string constant
	ICONST,
	SCONST,

		// the operators, parens, semicolon, newline
	PLUS,      // a +
	MINUS,     // a -
	STAR,      // a *
	SLASH,     // a /
	LPAREN,    // a (
	RPAREN,    // a )
	SC,        // a semicolon
	NL,        // a newline

		// any error returns this token
	ERR,

		// when completed (EOF), return this token
	DONE
};

class Token {
	TokenType	tt;
	string		lexeme;
	int			lnum;

public:
	Token() {
		tt = ERR;
		lnum = -1;
	}
	Token(TokenType tt, string lexeme, int line) {
		this->tt = tt;
		this->lexeme = lexeme;
		this->lnum = line;
	}

	bool operator==(const TokenType tt) const { return this->tt == tt; }
	bool operator!=(const TokenType tt) const { return this->tt != tt; }

	TokenType	GetTokenType() const { return tt; }
	string		GetLexeme() const { return lexeme; }
	int		GetLinenum() const { return lnum; }
};

extern ostream& operator<<(ostream& out, const Token& tok);

extern Token getNextToken(istream& in, int& linenum);


#endif /* LIST_TOKENS_H_ */
