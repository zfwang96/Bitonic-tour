#include <iostream>
#include <fstream>
#include <time.h>
#include <set>
using namespace std;

const int num = 10;

int main() {
	int time_count = 20;
	ofstream out_file("d://data.txt");
	srand((unsigned)time(0));
	while (time_count--) {
		cout << num << endl;
		out_file << num << endl;
		int *p = new int[num];
		//set<int> p_set;
		for (int i = 0; i < num; i++) {
			p[i] = rand() % 20;
			//p_set.insert(p[i]);
		}
		for (int i = 0; i < num; i++) {
			cout << i << " " << p[i] << endl;
			out_file << i << " " << p[i] << endl;
		}
		cout << endl;
		out_file << endl;
	}
	return 0;
}