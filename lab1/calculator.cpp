#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <vector>

using namespace std;

struct result {
	bool flag;		// Is exisit the operator M?
	double expr;	// The result of the expression
};

double term();			// deal with numbers and parentese
result expression();	// deal with +, - and M
double primary();		// deal with *, /, and %


void keep_window_open() {
	cin.clear();
	cout << "Please input a chacrator to quit\n";
	char ch;
	cin >> ch;
	return;
}

void keep_window_open(string str) { // always keep the window open
}

struct ERROR : runtime_error {
	ERROR() :runtime_error("error") {}
};

void error(string str) { // manage the info of error
	throw runtime_error(str);
}

class Token {
public:
	char kind;
	double value;
	Token(char ch) : kind(ch), value(0){}
	Token(char ch, double val) :kind(ch), value(val) {}
};


class Token_stream {
public:
	Token_stream();			// make a Token_stream that reads from cin
	Token get();			// get a Token (get() is defined elsewhere)
	void putback(Token t);	// put a Token back
	void ignore(char c);
private:
	bool full;				// is there a Token in the buffer?
	Token buffer;			// here is where we keep a Token put back using putback()
};

Token_stream::Token_stream() :full(false), buffer(0) {}
// no Token in buffer

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
	while (cin >> ch) {
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
	cin >> ch;		// note that >> skips whitespace(space, newline, tab, etc.)

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
		cin.putback(ch);	// put digit back into the input stream
		double val;
		cin >> val;			// read a floating-point
		return Token('8', val);	// let '8' represent "a number";
	}
	default:
		error("Bad token");
	}
}

Token_stream ts;
int store = 0;		// The varible presenting the value used by M

/* This function manages the operator of '!' */
int factorial(double x) {
	int i = int(x);
	if (i != x || x < 0)
		error("error");
	if (x == 0)
		return 1;
	else
		return x * factorial(x - 1);
}

double primary() {
	Token t = ts.get();
	double value = 0;

	switch (t.kind) {
	case '(': {			// handle '(' expression ')'
		result res;
		res = expression();
		double d = res.expr;
		t = ts.get();
		if (t.kind != ')') {
			ts.putback(t);
			error("error");
		}
		
		t = ts.get();
		if (t.kind == '!')		// handle the operator of '!'
			d = factorial(d);
		else
			ts.putback(t);

		return d;
	}

	case '8':				// we use '8' to represent a number
		value = t.value;	// return the number's value
		t = ts.get();
		if (t.kind == '!')
			value = factorial(value);
		else 
			ts.putback(t);
		return value;

	case '-':
		return -primary();

	case '+':
		return primary();

	case 'R':
		return store;
	
	default:
		error("error");
	}
}

double term() {
	double left = primary();
	Token t = ts.get();		// get the next Token from the Token stream

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/': {
			double d = primary();
			if (d == 0) error("error");
			left /= d;
			t = ts.get();
			break;
		}
		case '%': {
			double d = primary();
			int i1 = int(left);
			if (i1 != left)
				error("error");
			int i2 = int(d);
			if (i2 != d)
				error("error");
			if (i2 == 0)
				error("error");
			left = i1 % i2;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);	// put t back into the Token stream
			return left;
		}
	}
}

result expression() {
	result res;
	double left = term();	// read and evaluate a Term
	Token t = ts.get();		// get the next Token from the Token stream

	while (true) {
		switch (t.kind) {
		case '+':
			left += term();	//evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left -= term();	// evaluate Term and subtract
			t = ts.get();
			break;
		case 'M': {
			res.flag = true;// don't print out the result
			store = left;
			return res;
		}
		default:
			ts.putback(t);	// put t back into the token stream
			res.expr = left;
			res.flag = false;
			return res;		// finally: no more + or -; return the answer
		}
	}
}

void clean_up_mess() {
	ts.ignore(';');
}

void calculate() {
	while (cin) {
		try {
			cout << ">";
			Token t = ts.get();
			while (t.kind == ';')	// first dicard all ';'
				t = ts.get();
			if (t.kind == 'q')		// quit
				return;
			ts.putback(t);

			result res = expression();
			if (res.flag == false) // Is the input uses operator of 'M'?
				cout << "=" << res.expr << endl;
		}
		
		catch(exception& e) {
			cerr << e.what() << endl;
			clean_up_mess();
		}
		
	}
}

int main() {
	try {
		calculate();
		keep_window_open();
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		keep_window_open("~~");
		return 1;
	}
	catch (...) {
		cerr << "error\n";
		keep_window_open("~~");
		return 2;
	}
	return 0;
}
