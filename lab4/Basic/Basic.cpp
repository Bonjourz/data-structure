/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */
void doWithImmLine(const string & command, EvalState & state,
	Program & program, TokenScanner & scanner);
void doWithExecuteLine(const int & num, Program & program, TokenScanner & scanner);
void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cout << ex.getMessage() << endl;
      }
   }
   return 0;
}

void doWithImmLine(const string & command, EvalState & state,
	Program & program, TokenScanner & scanner) {
	/* Run the program according the command */
	if (command == "RUN") {
		program.run(state);
	}

	else if (command == "LIST") {
		program.list();
	}

	else if (command == "CLEAR") {
		program.clear();
		state.clear();
	}

	else if (command == "QUIT") {
		exit(0);
	}

	else if (command == "HELP") {
		/* Empty */
	}

	else if (command == "INPUT") {
		inputStmt inputStmt(scanner);
		inputStmt.execute(state);
	}

	else if (command == "PRINT") {
		printStmt printStmt(scanner);
		printStmt.execute(state);
	}

	else if (command == "LET") {
		letStmt letStmt(scanner);
		letStmt.execute(state);
	}

	else
		error("SYNTAX ERROR");
}

void doWithExecuteLine(const int & num, Program & program, TokenScanner & scanner) {
	ostringstream ss;
	char ch;
	while ((ch = scanner.getChar()) != EOF) {
		ss.put(ch);
	}
	
	/* Add the source line to the program */
	program.addSourceLine(num, ss.str());
}

/*
* Function: processLine
* Usage: processLine(line, program, state);
* -----------------------------------------
* Processes a single line entered by the user.  In this version,
* the implementation does exactly what the interpreter program
* does in Chapter 19: read a line, parse it as an expression,
* and then print the result.  In your implementation, you will
* need to replace this method with one that can respond correctly
* when the user enters a program line (which begins with a number)
* or one of the BASIC commands, such as LIST or RUN.
*/
void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   if (!scanner.hasMoreTokens())
	   return;

   string num_str = scanner.nextToken();
   int num;

   stringstream ss(num_str);

   /* If the line is the source line */
   if (!(ss >> num))
	   doWithImmLine(num_str, state, program, scanner);

   /* If the line cannot execute immediately */
   else
	   doWithExecuteLine(num, program, scanner);
}
