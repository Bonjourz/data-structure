/*	Zhu Bojun
** 515030910298
** For this part, I add an extra feature
** the pdf mentions, if you want to test the 
** extra feature, you should replace the function 
** of the "" and "get_ladder" at the end
** of this file. */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <sstream>
#include <cstdlib>

using namespace std;

bool isnum(string s, int& num);
bool get_file(vector<string>& words);
int get_num();
map<vector<string>, vector<string> > initialize(const vector<string>& words,
	const int& num);
int get_output_num(const int& num);
void get_result(const int& num,
	const map<vector<string>, vector<string> >& window, const int& rand_num);
string get_ele(const vector<string>& vec);
void update_vec(vector<string>& key, string tmp);

/* Convert string to int */
int str2num(string str) {
	stringstream ss;
	ss << str;
	int num;
	ss >> num;
	return num;
}

/* Determine whether the type of the input is legal */
bool isnum(string s, int& num) {
	stringstream sin(s);
	char p;
	if (!(sin >> num))
		return false;

	if (sin >> p)
		return false;
	else
		return true;
}

/* Get the input of the file */
bool get_file(vector<string>& words) {
	fstream ifs;
	while (true) {
		string file_name;
		cout << "Input file name? ";
		cin >> file_name;
		ifs.open(file_name);
		if (!ifs)
			cout << "Unable to open that file.  Try again." << endl;

		else
			break;
	}
	string word;
	while (ifs >> word)
		words.push_back(word);
	return true;
}

/* Initialize the map(key is the preffix and value is the word after the preffix),
** accordding to the n (n-gram) */
map<vector<string>, vector<string> > initialize(const vector<string>& words,
	const int& num) {
	map<vector<string>, vector<string> > model;
	for (int i = 0; i < words.size(); i++) {
		vector<string> key;
		vector<string> value;
		for (int j = 0; j < num; j++)
			key.push_back(words[(i + j) % (words.size() - 1)]);

		if (model.find(key) == model.end()) {
			value.push_back(words[(i + num) % (words.size() - 1)]);
			model.insert(make_pair(key, value));
		}

		else {
			auto itt = model.find(key);
			value = itt->second;
			value.push_back(words[(i + num) % (words.size() - 1)]);
			model.find(key)->second = value;
		}
	}
	return model;
}

/* Get the length n of N-gram */
int get_num() {
	string input;
	int num;
	while (true) {
		cout << "Value of N? ";
		cin >> input;
		if (!isnum(input, num))
			cout << "Illegal integer format.Try again.\n";

		else {
			if (num < 2)
				cout << "N must be 2 or greater.\n";
			else
				return num;
		}
	}
}

/* Get the number of the words user want to write */
int get_output_num(const int& n) {
	string input;
	int num;
	while (true) {
		cout << endl;
		cout << "# of random words to generate (0 to quit)? ";
		cin >> input;

		/* Check whether the input is legal */
		if (!isnum(input, num))
			cout << "Illegal integer format. Try again.\n";

		else {
			if (num == 0) {
				cout << "Exiting.\n";
				exit(0);
			}

			else if (num < n)
				cout << "Must be at least " << n << " words.\n";

			else
				return num;
		}
	}

	return num;
}

/* Get the output */
void get_result(const int& num,
	const map<vector<string>, vector<string> >& window, const int& rand_num) {
	string result, tmp;
	vector<string> key;
	vector<string> value;
	int count = 0;

	/* Randomly choose the first one */
	auto ptr = window.begin();
	for (int i = 0; i < rand_num; i++)
		ptr++;

	/* Get the N of "N-gram" */
	int size = window.begin()->first.size();

	while (count < num) {
		/* At first, simple put the key into the ouput text,
		** and then randomly choose the suffix of the key */
		if (count == 0) {
			key = ptr->first;
			value = ptr->second;
			for (int i = 0; i < key.size(); i++) {
				result = result + key[i] + " ";
			}
			tmp = get_ele(value);
			result += (tmp + " ");
			count += (size + 1);
		}
		else {
			value = window.find(key)->second;
			tmp = get_ele(value);
			result += (tmp + " ");
			count++;
		}

		/* Add the chosen word to the key, and simply drop the first one */
		update_vec(key, tmp);
	}
	cout << "... " << result << "..." << endl;
}

/* Randomly get the element from the input vector */
string get_ele(const vector<string>& vec) {
	int size = vec.size();
	if (size == 1)
		return vec[0];
	string str;
	str = vec[rand() % (size - 1)];
	return str;
}

/* Upadate the suffix after every write of a word */
void update_vec(vector<string>& key, string tmp) {
	vector<string> new_key;

	/* Drop the first word of the vector */
	for (int i = 1; i < key.size(); i++)
		new_key.push_back(key[i]);

	new_key.push_back(tmp);
	key = new_key;
}

int main()
{
	vector<string> words;
	/* Get the input file */
	get_file(words);
	int num;
	num = get_num();
	map<vector<string>, vector<string> > window;
	window = initialize(words, num - 1);
	/* The number of words user wants to write */
	int output_num;
	srand((unsigned)time(0));
	int rand_num;
	while (output_num = get_output_num(num)) {
		/* Randomly choose where to begin */
		rand_num = ((rand() % window.size()) + 
			(rand() % (window.size() / 5))) % window.size();
		get_result(output_num, window, rand_num);
	}

	return 0;
}

// The followings are the codes for the extra feature */
/*
void get_result(const int& num,
	const map<vector<string>, vector<string> >& window, const int& rand_num) {
	string result, tmp;
	vector<string> key;
	vector<string> value;
	int count = 0;

	auto ptr = window.begin();
	for (int i = 0; i < rand_num; i++)
		ptr++;

	vector<string> key_tmp;
	while (true) {
		key_tmp = ptr->first;
		char ch = key_tmp[0][0];
		if (!isupper(ch)) {
			ptr++;
			if (ptr == window.end())
				ptr = window.begin();
		}

		else break;
	}

	int size = window.begin()->first.size();

	bool flag = true;
	while (count < num || flag) {
		if (count == 0) {
			key = ptr->first;
			value = ptr->second;
			for (int i = 0; i < key.size(); i++) {
				result = result + key[i] + " ";
			}
			tmp = get_ele(value);
			result += (tmp + " ");
			count += (size + 1);
		}
		else {
			value = window.find(key)->second;
			tmp = get_ele(value);
			result += (tmp + " ");
			count++;
			if (count >= num) {
				if (tmp.find(".") != string::npos)
					flag = false;
			}
		}

		update_vec(key, tmp);
	}
	cout << "... " << result << "..." << endl;
}
*/

