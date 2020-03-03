/*
 * tokenInput.h
 *
 */

#ifndef TOKENINPUT_H_
#define TOKENINPUT_H_

#include "list_tokens.h"

class GetToken {
	static bool	pushed_back;
	static Token	pushed_token;

public:
	static Token Get(istream& in, int& line) {
		if( pushed_back ) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBack(Token& t) {
		if( pushed_back ) {
			throw std::logic_error("Cannot push back more than one token!");
		}
		pushed_back = true;
		pushed_token = t;
	}
};

#endif /* TOKENINPUT_H_ */
