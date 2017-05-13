#ifndef LINES_WINDOW_H
#define LINES_WINDOW_H

#include <iostream>
#include <string>
#include <cctype>
#include <FL/Fl.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_Window.h>
#include "Simple_window.h"
#include "Graph.h"
#include "Calculator.h"

class Lines_window : Window {
public:
	Lines_window(Point xy, int w, int h, const string& title);

private:
	bool flush;		/* Whether the string in the box should be flushed */
	string str_r;
	double ans;

	Calculator cal;
	string input_str;	/* The input string */
	string output_str;	/* The string of result */
	string ele;			/* The element determined by pressing button */
	double result;
	double store;		/* The value stored in R */

	Out_box output;
	Out_box input;
	Out_box output_r;

	Button button_quit;
	/* The button of number */
	Button button0;
	Button button1;
	Button button2;
	Button button3;
	Button button4;
	Button button5;
	Button button6;
	Button button7;
	Button button8;
	Button button9;
	Button button_point;
	/* The button of operator */
	Button button_left;
	Button button_right;
	Button button_m;
	Button button_r;
	Button button_add;
	Button button_minus;
	Button button_multipy;
	Button button_fac;
	Button button_divide;
	Button button_modulo;
	Button button_equal;
	Button button_ans;
	Button button_back;
	Button button_ac;


	Button button_cal;
	Button button_funcion;

	/* The events triggered by pressing the button */
	static void cb_quit(Address, Address);
	void quit();
	static void cb_f0(Address, Address);
	void f0();
	static void cb_f1(Address, Address);
	void f1();
	static void cb_f2(Address, Address);
	void f2();
	static void cb_f3(Address, Address);
	void f3();
	static void cb_f4(Address, Address);
	void f4();
	static void cb_f5(Address, Address);
	void f5();
	static void cb_f6(Address, Address);
	void f6();
	static void cb_f7(Address, Address);
	void f7();
	static void cb_f8(Address, Address);
	void f8();
	static void cb_f9(Address, Address);
	void f9();
	static void cb_point(Address, Address);
	void point();
	static void cb_m(Address, Address);
	static void cb_r(Address, Address);
	void r();
	static void cb_add(Address, Address);
	void add();
	static void cb_minus(Address, Address);
	void minus();
	static void cb_multipy(Address, Address);
	void multipy();
	static void cb_divide(Address, Address);
	void divide();
	static void cb_fac(Address, Address);
	void fac();
	static void cb_modulo(Address, Address);
	void modulo();
	static void cb_equal(Address, Address);
	void equal(bool modify);
	static void cb_back(Address, Address);
	void back();
	static void cb_ac(Address, Address);
	void ac();
	static void cb_ans(Address, Address);
	void get_ans();
	static void cb_left(Address, Address);
	void left();
	static void cb_right(Address, Address);
	void right();

	void fresh();


	static void cb_function(Address, Address);
	void draw_function();
	static void cb_cal(Address, Address);
	void calculator();
};


#endif
