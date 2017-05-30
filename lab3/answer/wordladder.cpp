/*	Zhu Bojun
** 515030910298
** For this part, I add some extra features
** the pdf describes, if you want to test the 
** extra features, you should replace the function 
** of the "get_input" and "get_ladder" at the end
** of this file. */

#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <set>
#include <cctype>
using namespace std;

void read_file(set<string> &english);
bool get_input(string& start, string& end, const set<string>& dic);
bool get_ladder(const string& start, const string& end, 
	const set<string>& dic, vector<string>& result);
void display(const vector<string>& result);

/* Get the file and initialize the dictionary */
void read_file(set<string> &dic) {
	ifstream ifs;
	while (true) {
		string filename;
		cout << "Dictionary file name ? ";
		cin >> filename;
		ifs.open(filename);

		if (!ifs)
			cout << "Unable to open that file.  Try again." << endl;
		else
			break;
	}

	string word;
	/* Insert words into the ditionary */
	while (getline(ifs, word))
		dic.insert(word);
}

/* Get the input of the word */
bool get_input(string& start, string& end, const set<string>& dic) {
char ch1, ch2;
	string str_s, str_e;
	/* When input the filename, charactetr '\n' is added into the input stream */
 	char ch = cin.get();

	cout << "Word #1 (or Enter to quit): ";
	ch = cin.peek();
	/* Determine if users enter '\n' ? */
	if (ch == '\n') {
		cout << "Have a nice day." << endl;
		exit(0);
	}

	cin >> str_s;

	cout << "Word #2 (or Enter to quit): ";
	ch = cin.get();
	ch = cin.peek();
	/* Determine if users enter '\n' ? */
	if (ch == '\n') {
		cout << "Have a nice day." << endl;
		exit(0);
	}

	cin >> str_e;

	/* Check whether lengths of two words are the same */
	if (str_s.size() != str_e.size()) {
		cout << "The two words must be the same length.\n";
		return false;
	}
	
	/* Check whether two words are different */
	if (str_s == str_e) {
		cout << "The two words must be different.\n";
		return false;
	}

	for (int i = 0; i < str_s.size(); i++) {
		ch1 = str_s[i];
		ch2 = str_e[i];
		ch1 = tolower(ch1);
		ch2 = tolower(ch2);
		str_s[i] = ch1;
		str_e[i] = ch2;
	}

	/* Whether the words are in the dictionary */
	if (dic.find(str_s) == dic.end() || dic.find(str_e) == dic.end()) {
		cout << "The two words must be found in the dictionary." << endl;
		return false;
	}

	start = str_s;
	end = str_e;
	return true;
	
}

bool get_ladder(const string& start, const string& end, const set<string>& dic, vector<string>& result) {
	set<string> used;		/* Mark the used word */
	vector<string> vec;
	used.insert(start);
	vec.push_back(start);
	queue<vector<string> > queue_l;
	queue_l.push(vec);
	while (!queue_l.empty()) {
		/* Get the vector at first of the queue */
		vector<string> vec_tmp = queue_l.front();
		queue_l.pop();

		/* Get the last word of the vector */
		string str_ele = vec_tmp[vec_tmp.size() - 1];
		for (int i = 0; i < str_ele.size(); i++) {
			/* Change every character */
			for (char ch = 'a'; ch <= 'z'; ch++) {
				if (ch == str_ele[i])
					continue;

				vector<string> new_vec = vec_tmp;
				string str_change = str_ele;
				str_change[i] = ch;
				/* If get the answer */
				if (str_change == end) {
					new_vec.push_back(end);
					result = new_vec;
					return true;
				}
				/* If the new word is not in the dictionary */
				if (dic.find(str_change) == dic.end() || used.find(str_change) != used.end())
					continue;

				/* Insert the word into the vector and push the vector into the queue,
				** and then insert the word into the set which records words used */
				used.insert(str_change);
				new_vec.push_back(str_change);
				queue_l.push(new_vec);
			}
			
		}
	}

	/* If no word ladder is found, return false */
	return false;
}

/* Display the word ladder on the screen */
void display(const vector<string>& result) {
	for (int i = result.size() - 1; i >= 0; i--)
		cout << result[i] << " ";

	cout << endl << endl;
}


int main()
{
	set<string> dic;
	read_file(dic);
	cout << endl;

	string start, end;
	while (true) {
		/* Get input */
		if (!get_input(start, end, dic))
			continue;

		vector<string> result;
		/* Find word ladder */
		if (get_ladder(start, end, dic, result)) {
			cout << "A ladder from " << end << " back to "
				<< start << ":" << endl;
			display(result);
		}
		else
			cout << "No word ladder found from "
			<< end << " back to " << start << "." << endl << endl;
	}
    return 0;
}

// The two funtions feature one
/* 
bool get_input(string& start, string& end, const set<string>& dic) {
char ch1, ch2;
	string str_s, str_e;
	char ch = cin.get();

	cout << "Word #1 (or Enter to quit): ";
	ch = cin.peek();
	if (ch == '\n') {
		cout << "Have a nice day." << endl;
		exit(0);
	}

	cin >> str_s;

	cout << "Word #2 (or Enter to quit): ";
	ch = cin.get();
	ch = cin.peek();
	if (ch == '\n') {
		cout << "Have a nice day." << endl;
		exit(0);
	}

	cin >> str_e;

	if (str_s.size() != str_e.size()) {
		cout << "The two words must be the same length.\n";
		return false;
	}
	
	if (str_s == str_e) {
		cout << "The two words must be different.\n";
		return false;
	}

	for (int i = 0; i < str_s.size(); i++) {
		ch1 = str_s[i];
		ch2 = str_e[i];
		ch1 = tolower(ch1);
		ch2 = tolower(ch2);
		str_s[i] = ch1;
		str_e[i] = ch2;
	}

	if (dic.find(str_s) == dic.end()) {
		cout << "The first word must be found in the dictionary." << endl;
		return false;
	}

	start = str_s;
	end = str_e;
	return true;
	
} 


bool get_ladder(const string& start, const string& end, const set<string>& dic, vector<string>& result) {
	set<string> used;
	vector<string> vec;
	used.insert(start);
	vec.push_back(start);
	queue<vector<string> > queue_l;
	queue_l.push(vec);
	while (!queue_l.empty()) {
		vector<string> vec_tmp = queue_l.front();
		queue_l.pop();

		string str_ele = vec_tmp[vec_tmp.size() - 1];
		for (int i = 0; i < str_ele.size(); i++) {
			for (char ch = 'a'; ch <= 'z'; ch++) {
				if (ch == str_ele[i])
					continue;

				vector<string> new_vec = vec_tmp;
				string str_change = str_ele;
				str_change[i] = ch;
				if (str_change == end) {
					new_vec.push_back(end);
					result = new_vec;
					return true;
				}
				if (dic.find(str_change) == dic.end() || used.find(str_change) != used.end())
					continue;

				used.insert(str_change);
				new_vec.push_back(str_change);
				queue_l.push(new_vec);
			}
			
		}
	}

	return false;
}
*/



// The two function of feature two
/*
bool get_input(string& start, string& end, const set<string>& dic) {
	char ch1, ch2;
	string str_s, str_e;
	char ch = cin.get();

	cout << "Word #1 (or Enter to quit): ";
	ch = cin.peek();
	if (ch == '\n') {
		cout << "Have a nice day." << endl;
		exit(0);
	}

	cin >> str_s;

	cout << "Word #2 (or Enter to quit): ";
	ch = cin.get();
	ch = cin.peek();
	if (ch == '\n') {
		cout << "Have a nice day." << endl;
		exit(0);
	}

	cin >> str_e;

	if (str_s == str_e) {
		cout << "The two words must be different.\n";
		return false;
	}

	for (int i = 0; i < str_s.size(); i++) {
		ch1 = str_s[i];
		ch2 = str_e[i];
		ch1 = tolower(ch1);
		ch2 = tolower(ch2);
		str_s[i] = ch1;
		str_e[i] = ch2;
	}

	if (dic.find(str_s) == dic.end() || dic.find(str_e) == dic.end()) {
		cout << "The two words must be found in the dictionary." << endl;
		return false;
	}

	start = str_s;
	end = str_e;
	return true;

}

bool get_ladder(const string& start, const string& end, const set<string>& dic, vector<string>& result) {
	set<string> used;
	vector<string> vec;
	used.insert(start);
	vec.push_back(start);
	queue<vector<string> > queue_l;
	queue_l.push(vec);
	while (!queue_l.empty()) {
		vector<string> vec_tmp = queue_l.front();
		queue_l.pop();

		string str_ele = vec_tmp[vec_tmp.size() - 1];
		

		//else {
			for (int i = 0; i < str_ele.size(); i++) {
				for (char ch = 'a'; ch <= 'z'; ch++) {
					if (ch == str_ele[i])
						continue;

					vector<string> new_vec = vec_tmp;
					string str_change = str_ele;
					str_change[i] = ch;
					if (str_change == end) {
						new_vec.push_back(end);
						result = new_vec;
						return true;
					}
					if (dic.find(str_change) == dic.end() || used.find(str_change) != used.end())
						continue;

					used.insert(str_change);
					new_vec.push_back(str_change);
					queue_l.push(new_vec);
				}
		}
		//}
			if (str_ele.size() < end.size()) {
				for (int i = 0; i < str_ele.size(); i++) {
					for (char ch = 'a'; ch <= 'z'; ch++) {
						string str_change = str_ele.substr(0, i) + ch +
							str_ele.substr(i, str_ele.size() - i);

						vector<string> new_vec = vec_tmp;
						if (str_change == end) {
							new_vec.push_back(end);
							result = new_vec;
							return true;
						}
						if (dic.find(str_change) == dic.end() || used.find(str_change) != used.end())
							continue;

						used.insert(str_change);
						new_vec.push_back(str_change);
						queue_l.push(new_vec);
					}
				}
			}

			else if (str_ele.size() > end.size()) {
				for (int i = 0; i < str_ele.size(); i++) {
					string str_change = str_ele.substr(0, i) + str_ele.substr(i + 1, str_ele.size() - i - 1);

					vector<string> new_vec = vec_tmp;
					if (str_change == end) {
						new_vec.push_back(end);
						result = new_vec;
						return true;
					}
					if (dic.find(str_change) == dic.end() || used.find(str_change) != used.end())
						continue;

					used.insert(str_change);
					new_vec.push_back(str_change);
					queue_l.push(new_vec);
				}
			}
	}

	return false;
}

*/





