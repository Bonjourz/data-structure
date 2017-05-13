#include "Calculator.h"
#include "Token_stream.h"
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

Calculator::Calculator(){
}

void Calculator::error(string str) {
	throw runtime_error(str);
}

string Calculator::get_result(string input, bool isM) {
	ts.set_stream(input);
	ostringstream os;
	try {
		double output = expression();
		os << output;
		if (ts.get().kind != ';')
			return "error";
		/*else {
			result = os.str();
			if (result[0] < '0' || result[0] > '9')
				if (result[0] != '-')
					return "error";
		}*/
		if (isM)
			store = output;
		return os.str();
	}
	catch (exception& e) {
		return e.what();
	}
}

int Calculator::factorial(double x) {
	int i = int(x);
	if (i != x || x < 0)
		error("error");
	if (x == 0)
		return 1;
	else
		return x * factorial(x - 1);
}

double Calculator::primary() {
	Token t = ts.get();
	double value = 0;

	switch (t.kind) {
	case '(': {			// handle '(' expression ')'
		value = expression();
		t = ts.get();
		if (t.kind != ')') {
			ts.putback(t);
			error("error");
		}

		t = ts.get();
		if (t.kind == '!')		// handle the operator of '!'
			value = factorial(value);
		else
			ts.putback(t);

		return value;
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

double Calculator::term() {
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
			if (d == 0) error("divide by 0!");
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

double Calculator::expression() {
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
		default:
			ts.putback(t);	// put t back into the token stream
			return left;		// finally: no more + or -; return the answer
		}
	}
}