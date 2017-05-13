#include "Lines_window.h"

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window(xy, w, h, title),
	button0(Point(0, y_max() - 80), 80, 80, "0", cb_f0),
	button1(Point(0, y_max() - 160), 80, 80, "1", cb_f1),
	button2(Point(80, y_max() - 160), 80, 80, "2", cb_f2),
	button3(Point(160, y_max() - 160), 80, 80, "3", cb_f3),
	button4(Point(0, y_max() - 240), 80, 80, "4", cb_f4),
	button5(Point(80, y_max() - 240), 80, 80, "5", cb_f5),
	button6(Point(160, y_max() - 240), 80, 80, "6", cb_f6),
	button7(Point(0, y_max() - 320), 80, 80, "7", cb_f7),
	button8(Point(80, y_max() - 320), 80, 80, "8", cb_f8),
	button9(Point(160, y_max() - 320), 80, 80, "9", cb_f9),
	button_point(Point(80, y_max() - 80), 80, 80, ".", cb_point),
	button_left(Point(0, y_max() - 400), 80, 80, "(", cb_left),
	button_right(Point(80, y_max() - 400), 80, 80, ")", cb_right),
	button_add(Point(240, y_max() - 160), 80, 40, "+", cb_add),
	button_minus(Point(240, y_max() - 120), 80, 40, "-", cb_minus),
	button_multipy(Point(240, y_max() - 80), 80, 40, "*", cb_multipy),
	button_divide(Point(240, y_max() - 40), 80, 40, "/", cb_divide),
	button_fac(Point(240, y_max() - 200), 80, 40, "!", cb_fac),
	button_equal(Point(160, y_max() - 80), 80, 80, "=", cb_equal),
	button_m(Point(240, y_max() - 320), 80, 40, "M", cb_m),
	button_r(Point(240, y_max() - 280), 80, 40, "R", cb_r),
	button_quit(Point(x_max() - 80, 0), 80, 20, "Quit", cb_quit),
	button_ans(Point(160, y_max() - 400), 80, 80, "ANS", cb_ans),
	button_modulo(Point(240, y_max() - 240), 80, 40, "%", cb_modulo),
	button_back(Point(240, x_max() - 360), 80, 40, "<-", cb_back),
	button_ac(Point(240, x_max() - 400), 80, 40, "AC", cb_ac),
	input(Point(100, y_max() - 520), 220, 40, "Please input:"),
	output(Point(140, y_max() - 470), 140, 40, "result:"),
	output_r(Point(30, y_max() - 470), 50, 40, "R:"),
	input_str(""), output_str("0"), result(0),
	button_cal(Point(x_max() - 80, 20), 80, 20, "calculator", cb_cal),
	button_funcion(Point(x_max() - 80, 40), 80, 20, "function", cb_function),
	store(0), str_r("0"), flush(true), ans(0)
{
	/* Display the button */
	attach(button0);
	attach(button1);
	attach(button2);
	attach(button3);
	attach(button4);
	attach(button5);
	attach(button6);
	attach(button7);
	attach(button8);
	attach(button9);
	attach(button_point);
	attach(button_left);
	attach(button_right);
	attach(button_add);
	attach(button_minus);
	attach(button_multipy);
	attach(button_divide);
	attach(button_fac);
	attach(button_equal);
	attach(button_modulo);
	attach(button_m);
	attach(button_r);
	attach(button_quit);
	attach(button_ac);
	attach(button_back);
	attach(button_ans);
	attach(output);
	attach(output_r);
	attach(input);
	attach(button_cal);
	output.put(output_str);
	output_r.put(str_r);
	calculator();
}

void Lines_window::cb_f0(Address, Address pw) {
	reference_to<Lines_window>(pw).f0();
}

void Lines_window::f0() {
	ele = "0";
	fresh();
}

void Lines_window::cb_f1(Address, Address pw) {
	reference_to<Lines_window>(pw).f1();
}

void Lines_window::f1() {
	ele = "1";
	fresh();
}

void Lines_window::cb_f2(Address, Address pw) {
	reference_to<Lines_window>(pw).f2();
}

void Lines_window::f2() {
	ele = "2";
	fresh();
}

void Lines_window::cb_f3(Address, Address pw) {
	reference_to<Lines_window>(pw).f3();
}

void Lines_window::f3() {
	ele = "3";
	fresh();
}

void Lines_window::cb_f4(Address, Address pw) {
	reference_to<Lines_window>(pw).f4();
}

void Lines_window::f4() {
	ele = "4";
	fresh();
}

void Lines_window::cb_f5(Address, Address pw) {
	reference_to<Lines_window>(pw).f5();
}

void Lines_window::f5() {
	ele = "5";
	fresh();
}


void Lines_window::cb_f6(Address, Address pw) {
	reference_to<Lines_window>(pw).f6();
}

void Lines_window::f6() {
	ele = "6";
	fresh();
}

void Lines_window::cb_f7(Address, Address pw) {
	reference_to<Lines_window>(pw).f7();
}

void Lines_window::f7() {
	ele = "7";
	fresh();
}


void Lines_window::cb_f8(Address, Address pw) {
	reference_to<Lines_window>(pw).f8();
}

void Lines_window::f8() {
	ele = "8";
	fresh();
}

void Lines_window::cb_f9(Address, Address pw) {
	reference_to<Lines_window>(pw).f9();
}

void Lines_window::f9() {
	ele = "9";
	fresh();
}

void Lines_window::cb_point(Address, Address pw) {
	reference_to<Lines_window>(pw).point();
}

void Lines_window::point() {
	ele = ".";
	fresh();
}

void Lines_window::cb_add(Address, Address pw) {
	reference_to<Lines_window>(pw).add();
}

void Lines_window::add() {
	ele = "+";
	fresh();
}

void Lines_window::cb_minus(Address, Address pw) {
	reference_to<Lines_window>(pw).minus();
}

void Lines_window::minus() {
	ele = "-";
	fresh();
}

void Lines_window::cb_multipy(Address, Address pw) {
	reference_to<Lines_window>(pw).multipy();
}

void Lines_window::multipy() {
	ele = "*";
	fresh();
}

void Lines_window::cb_divide(Address, Address pw) {
	reference_to<Lines_window>(pw).divide();
}

void Lines_window::divide() {
	ele = "/";
	fresh();
}

void Lines_window::cb_fac(Address, Address pw) {
	reference_to<Lines_window>(pw).fac();
}

void Lines_window::fac() {
	ele = "!";
	fresh();
}

void Lines_window::cb_modulo(Address, Address pw) {
	reference_to<Lines_window>(pw).modulo();
}

void Lines_window::modulo() {
	ele = "%";
	fresh();
}

void Lines_window::cb_equal(Address, Address pw) {
	reference_to<Lines_window>(pw).equal(false);
}

void Lines_window::equal(bool modify) {
	bool err = false;
	size_t index;
	string input_str_cpy = input_str;
	/* Determin whether the "ans" exitst in the expression */
	if ((index = input_str.find("ans")) != string::npos) {
		stringstream ss;
		ss << ans;
		string str = ss.str();
		input_str_cpy = input_str.substr(0, index) + str +
			input_str.substr(index + 3, input_str.size() - (index + 3) + 1);
	}

	/* Get the result */
	output_str = cal.get_result(input_str_cpy, modify);
	flush = true;

	/* If the result is not number */
	if ((output_str[0] >= '0' && output_str[0] <= '9') || output_str[0] == '-') {
		stringstream ss;
		ss << output_str;
		ss >> ans;
	}

	else
		err = true;

	if (!err && modify) {
		output_r.put(output_str);
	}
	output.put(output_str);
}

void Lines_window::cb_left(Address, Address pw) {
	reference_to<Lines_window>(pw).left();
}

void Lines_window::left() {
	ele = "(";
	fresh();
}

void Lines_window::cb_right(Address, Address pw) {
	reference_to<Lines_window>(pw).right();
}

void Lines_window::right() {
	ele = ")";
	fresh();
}

void Lines_window::cb_m(Address, Address pw) {
	reference_to<Lines_window>(pw).equal(true);
}

void Lines_window::cb_r(Address, Address pw) {
	reference_to<Lines_window>(pw).r();
}

void Lines_window::r() {
	ele = "R";
	fresh();
}

void Lines_window::cb_back(Address, Address pw)
{
	reference_to<Lines_window>(pw).back();
}

void Lines_window::back() {
	input_str = input_str.substr(0, input_str.size() - 1);
	input.put(input_str);
}

void Lines_window::cb_ac(Address, Address pw) {
	reference_to<Lines_window>(pw).ac();
}

void Lines_window::ac() {
	input_str = "";
	input.put(input_str);
}

void Lines_window::cb_ans(Address, Address pw) {
	reference_to<Lines_window>(pw).get_ans();
}

void Lines_window::get_ans() {
	ele = "ans";
	fresh();
}

void Lines_window::cb_quit(Address, Address pw)
{
	reference_to<Lines_window>(pw).quit();
}

void Lines_window::quit() {
	hide();
}

void Lines_window::fresh() {
	if (flush) {
		flush = false;
		input_str = "";
	}
	input_str += ele;
	ele = "";
	input.put(input_str);
}

void Lines_window::cb_function(Address, Address pw) {
	reference_to<Lines_window>(pw).draw_function();
}

void  Lines_window::draw_function() {

}

void Lines_window::cb_cal(Address, Address pw) {
	reference_to<Lines_window>(pw).calculator();
}

void Lines_window::calculator() {

}