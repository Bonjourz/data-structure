/* Zhu Bojun
** 515030910298
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#define MAX 1024
using namespace std;

/* The struct of the point */
struct ELE {
	int x;
	int y;
};

/* Get the input */
vector<vector<int> > get_input(vector<vector<int> >& flag) {
	string filename;
	cout << "File name?(:q to quit) ";
	cin >> filename;
	if (filename == ":q")
		exit(0);
	fstream ifs;
	ifs.open(filename);
	int col, row;
	int ele;
	ifs >> row;
	ifs >> col;
	vector<vector<int> > maze;
	for (int i = 0; i < row; i++) {
		vector<int> vec;
		vector<int> flag_ele;
		for (int j = 0; j < col; j++) {
			ifs >> ele;
			vec.push_back(ele);
			flag_ele.push_back(0);
		}
		maze.push_back(vec);
		flag.push_back(flag_ele);
	}
	return maze;
}

/* Merge the path after the execution of dfs to choos the shortest path */
stack<ELE> get_path(vector<stack<ELE> >path_vec, stack<ELE> path) {
	int index = 0;
	int size = MAX;

	/* If there is no path to the exit */
	if (path_vec.size() == 0) {
		stack<ELE> empty;
		return empty;
	}
	
	/* Chose the shortest path */	
	for (int i = 0; i < path_vec.size(); i++) {
		if (path_vec[i].size() > 0 && path_vec[i].size() < size) {
			index = i;
			size = path_vec[i].size();
		}
	}

	/* If the length of path in the vector path_vec is 0,
	** in other words, there is no path to the exit */
	if (size == MAX) {
		stack<ELE> empty;
		return empty;
	}

	/* Merge the path */
	stack<ELE> stack_ele = path_vec[index];
	vector<ELE> vec;
	while(!stack_ele.empty()) {
		vec.push_back(stack_ele.top());
		stack_ele.pop();
	}

	while (!path.empty()) {
		vec.push_back(path.top());
		path.pop();
	}

	stack<ELE> result;
	for (int i = vec.size() - 1; i >= 0; i--) {
		result.push(vec[i]);
	}

	return result;
}


stack<ELE> dfs(int i, int j, vector<vector<int> >& maze,
	vector<vector<int> > flag) {
	flag[i][j] = 1;		/* Mark the point is visited */
	stack<ELE> path;
	ELE ele;
	ele.x = i;
	ele.y = j;
	path.push(ele);		/* Record the path of the point */

	/* If arrive at the point of exit */
	if (j == maze[0].size() - 1 && i == maze.size() - 1 && maze[i][j] == 0) {
		return path;
	}

	else {
		/* Find the path to the exit */
		int col = maze[0].size();
		int row = maze.size();
		vector<vector<int> >flag_c = flag;
		vector<stack<ELE> >path_vec;
		if (i - 1 >= 0 && maze[i - 1][j] == 0 && flag[i - 1][j] == 0) 
			path_vec.push_back(dfs(i - 1, j, maze, flag_c));
		if (j - 1 >= 0 && maze[i][j - 1] == 0 && flag[i][j - 1] == 0)
			path_vec.push_back(dfs(i, j - 1, maze, flag_c));
		if (i + 1 < row && maze[i + 1][j] == 0 && flag[i + 1][j] == 0)
			path_vec.push_back(dfs(i + 1, j, maze, flag_c));
		if (j + 1 < col && maze[i][j + 1] == 0 && flag[i][j + 1] == 0)
			path_vec.push_back(dfs(i, j + 1, maze, flag_c));
		
		/* Merge path to choose the shortest */
		return get_path(path_vec, path);
	}
}

/* Get the result of this problem */
void get_output(vector<vector<int> >& maze, vector<vector<int> >& flag) {
	stack<ELE> result = dfs(0, 0, maze, flag);
	while (!result.empty()) {
		ELE ele = result.top();
		result.pop();
		maze[ele.x][ele.y] = 2;
	}
}

int main()
{
	while (true) {
		vector<vector<int> > flag;
		vector<vector<int> > maze = get_input(flag);
		get_output(maze, flag);
		for (int i = 0; i < maze.size(); i++) {
			for (int j = 0; j < maze[i].size(); j++)
				cout << maze[i][j] << " ";
			cout << endl;
		}
	}
    return 0;
}

