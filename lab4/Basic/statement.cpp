/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

void Statement::set_next_line(const int & line_num) {
	next_line = line_num;
}

int Statement::get_next_line() {
	return next_line;
}

/* Implementation of the letStmt class */

letStmt::letStmt(TokenScanner & scanner) {
	if (!scanner.hasMoreTokens())
		error("SYNTAX ERROR");

	string var = scanner.nextToken();
	TokenType type = scanner.getTokenType(var);

	/* If the name of variable is in the key words */
	if (var == "LET")
		error("SYNTAX ERROR");
	
	if (type != WORD)
		error("SYNTAX ERROR");

	name = new IdentifierExp(var);

	if (!scanner.hasMoreTokens())
		error("SYNTAX ERROR");

	string opt = scanner.nextToken();
	if (opt != "=")
		error("SYNTAX ERROR");

	value = readE(scanner);
}

letStmt::~letStmt() {
	delete name;
	delete value;
}

void letStmt::execute(EvalState & state) {
	state.setValue(name->getName(), value->eval(state));
}

/* Implementation of the printStmt class */

printStmt::printStmt(TokenScanner & scanner) {
	if (!scanner.hasMoreTokens())
		error("SYNTAX ERROR");

	value = readE(scanner);
}

printStmt::~printStmt() {
	delete value;
}

void printStmt::execute(EvalState & state) {
	cout << value->eval(state) << endl;
}

/* Implementation of the remStmt class */
remStmt::remStmt(TokenScanner & scanner) {
	/* Empty */
}

remStmt::~remStmt() {
	/* Empty */
}

void remStmt::execute(EvalState & state) {
	/* Empty */
}

ifStmt::ifStmt(TokenScanner & scanner) {
	if (!scanner.hasMoreTokens())
		error("SYNTAX ERROR");

	/* Get the expression of left variable */
	left = readE(scanner);

	if (!scanner.hasMoreTokens())
		error("SYNTAX ERROR");

	opt = scanner.nextToken();

	if (opt != "=" && opt != "<" && opt != ">")
		error("SYNTAX ERROR");

	if (!scanner.hasMoreTokens())
		error("SYNTAX ERROR");

	/* Get the expression of right variable */
	right = readE(scanner);

	if (scanner.nextToken() != "THEN")
		error("SYNTAX ERROR");

	stringstream ss;
	string num_str = scanner.nextToken();
	ss << num_str;
	/* If the line is not a number */
	if (!(ss >> line_num))
		error("SYNTAX ERROR");

	if (line_num < 0)
		error("SYNTAX ERROR");
}

ifStmt::~ifStmt() {
	delete left;
	delete right;
}

void ifStmt::execute(EvalState & state) {
	int left_val = left->eval(state);
	int right_val = right->eval(state);
	
	bool flag;
	if (opt == "<") 
		flag = (left_val < right_val);

	else if (opt == ">") 
		flag = (left_val > right_val);

	else if (opt == "=")
		flag = (left_val == right_val);

	/* If the flag is true, set the next line number */
	if (flag)
		next_line = line_num;
}

/* Implementation of the class inputStmt */
inputStmt::inputStmt(TokenScanner & scanner) {
	if (!scanner.hasMoreTokens())
		error("SYNTAX ERROR");

	var_name = scanner.nextToken();
	if (scanner.getTokenType(var_name) != WORD)
		error("SYNTAX ERROR");
}

inputStmt::~inputStmt() {
	/* Empty */
}

void inputStmt::execute(EvalState & state) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();

	Expression *exp;
	int value;
	bool flag = true;
	/* Whether the variable input is negative */
	bool negative = false;
	do {
		cout << " ? ";
		scanner.setInput(getLine());
		string num_str = scanner.nextToken();

		/* If the variable is negative */
		if (num_str == "-") {
			num_str = scanner.nextToken();
			negative = true;
		}

		stringstream ss;
		ss << num_str;
		if (ss >> value) {
			flag = false;
			char ch;
			/* If there is still some charactor cannot transfer to number */
			if (ss >> ch) {
				flag = true;
				cout << "INVALID NUMBER" << endl;
				continue;
			}

			if (scanner.hasMoreTokens()) {
				flag = true;
				cout << "INVALID NUMBER" << endl;
			}
		}

		else 
			cout << "INVALID NUMBER" << endl;

	} while (flag);
	
	/* If the number is negative */
	if (negative)
		value = -value;
	
	state.setValue(var_name, value);
}

endStmt::endStmt(TokenScanner & token) {
	/* Empty */
}

endStmt::~endStmt() {
	/* Empty */
}

void endStmt::execute(EvalState & state) {
	/* Set the line number */
	next_line = -1;
}

/* Implementation of the class gotoStmt */
gotoStmt::gotoStmt(TokenScanner & token) {
	string line_num_str = token.nextToken();
	stringstream ss;
	ss << line_num_str;
	if (!(ss >> line_num)) 
		error("SYNTAX ERROR");

	if (line_num < 0)
		error("SYNTAX ERROR");
}

gotoStmt::~gotoStmt() {
	/* Empty */
}

void gotoStmt::execute(EvalState & state) {
	/* Set the line number */
	next_line = line_num;
}


