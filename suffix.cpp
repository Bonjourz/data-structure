/* Zhu Bojun 515030910298 */


#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_NUM 1024

using namespace std;

bool get_input(map<string, int>& suffix_map, map<string, vector<string>>& words_suffix) {
	fstream ifs;
	ifs.open("dictionary.txt");
	if (!ifs)
		exit(0);

	string words;
	string suffix;
	int num;

	cout << "Please input the num: ";
	cin >> num;
	while (ifs >> words) {
		if (words.size() < num)
			continue;

		suffix = words.substr(words.size() - num, num);
		suffix_map[suffix]++;
		words_suffix[suffix].push_back(words);
	}
	return true;
}

void get_result(const map<string, int>& suffix_map) {
	vector<pair<int, string>> vec;
	for (auto& p : suffix_map) {
		vec.push_back(make_pair(p.second, p.first));
	}
	sort(vec.begin(), vec.end());
	int size = vec.size();
	for (int i = 0; i < 10 && i < size; i++)
		cout << vec[size - 1 - i].second << " "
		<< vec[size - 1 - i].first  << endl;
}

void query(map<string, vector<string>>& words_suffix) {
	string suffix;
	while (true) {
		cout << "Please input the suffix: ";
		cin >> suffix;

		if (words_suffix.find(suffix) == words_suffix.end()) 
			cout << "Not exist!" << endl;


		vector<string> vec = words_suffix[suffix];
		sort(vec.begin(), vec.end());
		for (int i = vec.size() - 1; i > 0; i--) {
			cout << vec[i] << endl;
		}
	}
}

int main()
{
	map<string, int> suffix_map;
	map<string, vector<string>> words_suffix;
	while (!get_input(suffix_map, words_suffix));
	get_result(suffix_map);
	query(words_suffix);
    return 0;
}

