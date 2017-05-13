#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H
#include "Token.h"
#include <string>
#include <sstream>

using namespace std;

class Token_stream {
public:
	Token_stream();
	Token_stream(string str);			// make a Token_stream that reads from cin
	Token get();			// get a Token (get() is defined elsewhere)
	void putback(Token t);	// put a Token back
	void ignore(char c);
	void set_stream(string str);
private:
	bool full;				// is there a Token in the buffer?
	Token buffer;			// here is where we keep a Token put back using putback()
	stringstream str_stream;
	void error(string str);
};
#endif