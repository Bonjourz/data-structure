#include <iostream>

using namespace std;

int get_result(const int& num) {
	if (num <= 2)
		return num;
	else
		return get_result(num - 1) + get_result(num - 2);
}

int main() {
	int num;
	while (true) {
		cout << "Please input (-1 to quit):";
		cin >> num;
		if (num < 0)
			break;
		else 
			cout << get_result(num) << endl;
	}
	return 0;
} 