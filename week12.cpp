/* Zhu Bojun 515030910298 */


#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_NUM 1024

using namespace std;

bool get_input(map<string, int>& suffix_map, map<string, vector<string>>& words_suffix);
void query(const const map<string, int>& suffix_map,
	const map<string, vector<string>>& words_suffix);
void display(const map<string, int>& suffix_map,
	const map<string, vector<string>>& words_suffix);
void get_result(map<string, int>& maneuver, map<int, vector<string>>& result);

bool get_input(map<string, int>& suffix_map, map<string, vector<string>>& words_suffix) {
	string file_name;
	int num;
	cout << "Please input the filename: ";
	cin >> file_name;
	cout << "Please input the num of the suffix: ";
	cin >> num;

	fstream ifs;
	ifs.open("dictionary.txt");
	string words;
	string suffix;
	while (ifs >> words) {
		if (words.size() >= num) {
			vector<string> vec;
			suffix = words.substr(words.size() - num, num);
			if (suffix_map.find(suffix) == suffix_map.end()) {
				suffix_map.insert(make_pair(suffix, 1));
				vec.push_back(words);
				words_suffix.insert(make_pair(suffix, vec));
			}

			else {
				int num_suffix = suffix_map.find(suffix)->second;
				num_suffix++;
				suffix_map.find(suffix)->second = num_suffix;
				vec = words_suffix.find(suffix)->second;
				vec.push_back(words);
				words_suffix.find(suffix)->second = vec;
			}
		}
	}
	return true;
}

void get_resultn(const map<string, int>& maneuver, map<int, vector<string>>& result) {
	for (auto ptr = maneuver.begin(); ptr != maneuver.end(); ptr++) {
		int num = ptr->second;
		vector<string> vec;
		if (result.find(num) != result.end()) {
			vec = result.find(num)->second;
			vec.push_back(ptr->first);
			result.find(num)->second = vec;
		}

		else {
			vec.push_back(ptr->first);
			result.insert(make_pair(num, vec));
		}
	}
}

void display(const map<string, int>& suffix_map, 
	const map<string, vector<string>>& words_suffix) {
	map<string, int> maneuver = suffix_map;
	map<int, vector<string>> result;
	//for (int i = 0; i < 10; i++) {
		get_resultn(maneuver, result);
	//}

	map<int, vector<string>>::reverse_iterator iter;
	int j = 0;
	for (iter = result.rbegin(); iter != result.rend() && j < 10; ++iter) {
		j++;
		vector<string> output = iter->second;
		int num = iter->first;
		for (int j = 0; j < output.size(); j++)
			cout << num << " " << output[j] << endl;
	}
	while (true) 
		query(suffix_map, words_suffix);
}

void get_result(map<string, int>& maneuver, map<int, vector<string>>& result) {
	int num = 0;
	vector<string> words;
	for (auto ptr = maneuver.begin(); ptr != maneuver.end(); ptr++) {
		if (num < ptr->second) {
			words.clear();
			words.push_back(ptr->first);
			num = ptr->second;
		}
		else if (num == ptr->second) {
			words.push_back(ptr->first);
		}
	}

	for (int i = 0; i < words.size(); i++) 
		maneuver.erase(words[i]);

	result.insert(make_pair(num, words));
}

void query(const const map<string, int>& suffix_map,
	const map<string, vector<string>>& words_suffix) {
	string suffix;
	cout << "Please input the suffix you want to query: ";
	cin >> suffix;
	auto ptr = suffix_map.find(suffix);
	if (ptr == suffix_map.end())
		cout << "The suffix you input in not int the dictionary!" << endl;
	else {
		cout << "The num is :" << ptr->second << endl;
		vector<string> vec = words_suffix.find(suffix)->second;
		int size = vec.size();
		//string str[MAX_NUM];
		//for (int i = 0; i < size; i++)
			//str[i] = vec[i];
		//sort(str, str + size);
		cout << "The words in dictionary contains suffix of " << suffix << " is: ";
		for (int i = size - 1; i > 0; i--)
			cout << vec[i] << endl;
	}
}

int main()
{
	map<string, int> suffix_map;
	map<string, vector<string>> words_suffix;
	while (!get_input(suffix_map, words_suffix));
	display(suffix_map, words_suffix);
    return 0;
}

