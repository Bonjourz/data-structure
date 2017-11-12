/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h


#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
#include "evalstate.h"
#include "parser.h"
#include "exp.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

	Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;

   /* Get the next line of this statement */
   int get_next_line();

   /* Set the next line of this statement */
   void set_next_line(const int & next_line);

protected:
	int next_line;
};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

/* Class for LET statement */
class letStmt : public Statement {
public:
	letStmt(TokenScanner & token);
	virtual ~letStmt();
	virtual void execute(EvalState & state);

private:
	IdentifierExp *name;
	Expression *value;
};


/* Class for PRINT statement */
class printStmt : public Statement {
public:
	printStmt(TokenScanner & token);
	virtual ~printStmt();
	virtual void execute(EvalState & state);

private:
	Expression *value;
};


/* Class for IF...THEN... statement */
class ifStmt : public Statement {
public:
	ifStmt(TokenScanner & token);
	virtual ~ifStmt();
	virtual void execute(EvalState & state);

private:
	string opt;
	int line_num;
	Expression *left;
	Expression *right;
};

/* Class for GOTO statement */
class gotoStmt : public Statement {
public:
	gotoStmt(TokenScanner & token);
	virtual ~gotoStmt();
	virtual void execute(EvalState & state);
private:
	int line_num;
};

/* Class for REM statement */
class remStmt : public Statement {
public:
	remStmt(TokenScanner & token);
	~remStmt();
	virtual void execute(EvalState & state);
};

/* Class for INPUT statement */
class inputStmt : public Statement {
public:
	inputStmt(TokenScanner & token);
	virtual ~inputStmt();
	virtual void execute(EvalState & state);

private:
	string var_name;
};

/* Class for END statement */
class endStmt : public Statement {
public:
	endStmt(TokenScanner & token);
	virtual ~endStmt();
	virtual void execute(EvalState & state);
};

#endif
