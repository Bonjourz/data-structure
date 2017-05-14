#include <FL/Fl.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_Window.h>
#include "Simple_window.h"
#include "Graph.h"

#include <iostream>

using namespace std;

#define MAX(x,y)	 x > y ? x : y
int get_the_num(int l) {
	int num = 0;
	double input_num = double(l);
	while (true) {
		input_num = input_num / 4;
		int int_num = int(input_num);
		if (int_num == input_num)
			num++;
		else return num;
	}
}

void get_input(double& x, double& y, double& L, int& order) {
	cout << "Please input the x, y, L and order: ";
	cin >> x >> y >> L >> order;
	int num = get_the_num(L);
	if (num < order)
		for (int i = 0; i < order - num; i++)
			L *= 4;
	y = y + L;
}

void draw_square(const double& x, const double& y, const double& L, Simple_window& win) {
	Rectangle* rec = new Rectangle(Point(x, y - L), Point(x + L, y));
	win.attach(*rec);
}

void draw(const double& x, const double& y, const double& L, int order, Simple_window& win) {
	if (order > 0) {
		for (int i = 0; i < 4; i++)
			draw_square(x + i*(L / 4), y - i*(L / 4), L / 4, win);

		for (int j = 0; j < 4; j++)
			draw(x + j*(L / 4), y - j*(L / 4), L / 4, order - 1, win);
	}
}

int main()
{
	double x, y, L; 
	int order;
	get_input(x, y, L, order);
	Simple_window win(Point(0, 0), MAX(x, y - L) + L, MAX (x, y - L) + L, "Canvas");
	draw_square(x, y, L, win);
	draw(x, y, L, order, win);
	win.wait_for_button();
	return 0;
}
