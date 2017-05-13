#include "Token_stream.h"
#include <iostream>
#include <stdexcept>
#include "Token_stream.h"
#include <string>
#include <sstream>

using namespace std;

void Token_stream::set_stream(string str) {
	full = false;
	str_stream.clear();
	str_stream.str("");
	str += ";";
	str_stream << str;
}

Token_stream::Token_stream() :full(false), buffer(0) {
}

Token_stream::Token_stream(string str) :full(false), buffer(0) {
	set_stream(str);
}


void Token_stream::putback(Token t) {
	if (full)
		error("putback() into a full buffer");
	buffer = t;		// copy t to buffer
	full = true;	// buffer is now full
}

void Token_stream::ignore(char c)
// c represents the kind of Token
{
	if (full && c == buffer.kind) { // first look in buffer
		full = false;
		return;
	}

	full = false;

	char ch = 0;
	while (str_stream >> ch) {
		if (ch == c)
			return;
	}
}

Token Token_stream::get() {
	if (full) {		// do we already have a Token ready?
		full = false;	// remove Token from buffer
		return buffer;
	}

	char ch;
	str_stream >> ch;		// note that >> skips whitespace(space, newline, tab, etc.)

	switch (ch) {
	case ';':
	case 'q':
	case '(':case')':case'+':case'-':case'*':
	case '/':case'!':case'%':case'M':case'R':
		return Token(ch);	// let each character represent itself
	case '.':
	case '0':case'1':case '2':case'3':case '4':
	case '5':case'6':case '7':case'8':case '9':
	{
		str_stream.putback(ch);	// put digit back into the input stream
		double val;
		str_stream >> val;			// read a floating-point
		return Token('8', val);	// let '8' represent "a number";
	}
	default:
		error("Bad taken");
	}
}

void Token_stream::error(string str) { // manage the info of error
	throw runtime_error(str);
}