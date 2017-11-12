/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
   /* Empty */
}

Program::~Program() {
  /* Empty */
}

void Program::clear() {
	lines.clear();
	parsedstat.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
	lines[lineNumber] = line;
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string key = scanner.nextToken();
	Statement * stmt = NULL;
	/* Initialize the statement using tokenscanner
	 * according to the key word */
	if (key == "LET")
		stmt = new letStmt(scanner);

	else if (key == "PRINT")
		stmt = new printStmt(scanner);

	else if (key == "INPUT")
		stmt = new inputStmt(scanner);

	else if (key == "IF")
		stmt = new ifStmt(scanner);

	else if (key == "GOTO")
		stmt = new gotoStmt(scanner);

	else if (key == "END")
		stmt = new endStmt(scanner);

	else if (key == "REM")
		stmt = new remStmt(scanner);

	parsedstat[lineNumber] = stmt;
}

void Program::removeSourceLine(int lineNumber) {
	/* This BASIC interpreter doesn't use this function */
}

string Program::getSourceLine(int lineNumber) {
	if (lines.find(lineNumber) != lines.end()) {
		return lines[lineNumber];
	}
	else 
		return ""; 
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
	parsedstat[lineNumber] = stmt;
}

Statement *Program::getParsedStatement(int lineNumber) {
	if (parsedstat.find(lineNumber) != parsedstat.end()) {
		return parsedstat[lineNumber]; 
	}
	else return NULL;
}

int Program::getFirstLineNumber() {
	map<int, string>::iterator ptr = lines.begin();
	if (ptr == lines.end()) {
		return -1;
	}
	return ptr->first;
}

int Program::getNextLineNumber(int lineNumber) {
	map<int, string>::iterator ptr = lines.find(lineNumber);
	if (ptr == lines.end()) {
		return -1;
	}

	ptr++;
	if (ptr == lines.end()) {
		return -1;
	}
	return ptr->first;
}

void Program::list() {
	for (map<int, string>::iterator ptr = lines.begin(); ptr != lines.end(); ptr++) {
		/* If the source line is empty, don't output the line number */
		if (ptr->second != "")
			cout << ptr->first << ptr->second << endl;
	}
}

void Program::run(EvalState & state) {
	int line_num = getFirstLineNumber();
	if (line_num < 0)
		return;

	Statement * stmt = getParsedStatement(line_num);
	
	do {
		/* Firs set the expected next line */
		stmt->set_next_line(getNextLineNumber(line_num));
		stmt->execute(state);

		/* If the next line number is changed */
		int next_line = stmt->get_next_line();
		stmt = getParsedStatement(next_line);
		line_num = next_line;

		/* Line number error */
		if (stmt == NULL && next_line > 0)
			error("LINE NUMBER ERROR");
	} while (stmt != NULL);
}
