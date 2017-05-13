#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Token_stream.h"
#include <sstream>
#include <string>
using namespace std;

class Calculator
{
public:
	Calculator();
	string get_result(string str, bool isM);
private:
	Token_stream ts;
	double term();			// deal with numbers and parentese
	double expression();	// deal with +, - and M
	double primary();		// deal with *, /, and %
	int factorial(double x);
	double store;
	void error(string str);
};
#endif

