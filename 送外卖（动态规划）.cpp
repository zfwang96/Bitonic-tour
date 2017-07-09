/*************************************************************************
> File Name: Դ.cpp
> Author: Wang Zhifu
> Mail: 151220117@smail.nju.edu.cn
> Creation Time: 2017-07-09 13:36
> Description:
************************************************************************/

#include <iostream>
#include <assert.h>
#include <cmath>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

//#define DEBUG

struct point
{
	double x;
	double y;
};

vector<point>v;

double dis(point a, point b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

int main()
{
	int num;//the number of points
	cin >> num;

	for (int i = 0; i < num; i++)
	{
		point temp;
		double temp_x, temp_y;
		cin >> temp_x;
		cin >> temp_y;
		temp.x = temp_x;
		temp.y = temp_y;
		v.push_back(temp);
	}

	double **d = new double*[num + 1];
	int **no_list = new int*[num + 1];

	
	for (int i = 1; i <= num; i++) {
		d[i] = new double[num + 1];
	}
	
	for (int i = 1; i <= num; i++) {
		no_list[i] = new int[num + 1];
	}

	for (int i = 1; i <= num; i++) {
		for (int j = 1; j <= num; j++) {
			no_list[i][j] = -1;
		}
	}
	for (int i = 1; i <= num; i++) {
		for (int j = 1; j <= num; j++) {
			d[i][j] = 0;
		}
	}
	d[1][2] = dis(v[0], v[1]);
	for (int i = 1; i <= num; i++) {
		for (int j = i + 1; j <= num; j++) {
			if (i < j - 1) {
				d[i][j] = d[i][j - 1] + dis(v[j - 2], v[j - 1]);
			}
			else if (i == j - 1) {
				double min_dis = d[1][j - 1] + dis(v[0], v[j - 1]);
				int no = 1;
				for (int k = 2; k < j - 1; k++) {
					double tmp_dis = dis(v[k - 1], v[j - 1]);
					if (d[k][j - 1] + tmp_dis < min_dis) {
						min_dis = d[k][j - 1] + dis(v[k - 1], v[j - 1]);
						no = k;
					}
				}
				d[i][j] = min_dis;
				no_list[i][j] = no;
#ifdef DEBUG
				cout << "j->k:" << j << "->" << no << endl;
				cout << "i:" << i << " " << "j:" << j << " k: " << no << endl;
#endif // DEBUG
				
			}
#ifdef DEBUG
			else {
				assert(0);
			}
#endif // DEBUG
			
		}
	}

#ifdef DEBUG
	for (int i = 1; i <= num; i++) {
		for (int j = 1; j <= num; j++) {
			cout << d[i][j] << " ";
		}
		cout << endl;
	}
#endif // DEBUG

#ifdef DEBUG
	for (int i = 1; i <= num; i++) {
		for (int j = 1; j <= num; j++) {
			cout << no_list[i][j] << " ";
		}
		cout << endl;
	}
#endif // DEBUG

	
	double cost = 0;
	cost = d[num - 1][num] + dis(v[num - 2], v[num - 1]);
	
	set<int> s1;
	set<int> s2;
	for (int i = 0; i < num; i++) {
		s1.insert(i);
	}
	int i = num - 1, j = num;
	s1.erase(num - 1);
	s2.insert(num - 1);
	while (no_list[i][j] != -1) {
		s1.erase(no_list[i][j] - 1);
		s2.insert(no_list[i][j] - 1);
		i = no_list[i][j] < i ? no_list[i][j] : i;
		j = no_list[i][j] >= i ? no_list[i][j] : i;
	}
	
	set<int>::iterator it = s1.find(1);
	set<int>::reverse_iterator itr;
	s1.insert(0);
	s2.insert(0);
	if (it == s1.end()) {

#ifdef DEBUG
		cout << "1 in set2" << endl;
#endif // DEBUG

		for (it = s2.begin(); it != s2.end(); it++)
		{
			cout << *it << " ";
		}
		//cout << endl;
		for (itr = s1.rbegin(); itr != s1.rend(); itr++)
		{
			cout << *itr << " ";
		}
		cout << endl;
	}
	else {

#ifdef DEBUG
		cout << "1 in set1" << endl;
#endif // DEBUG

		
		for (it = s1.begin(); it != s1.end(); it++)
		{
			cout << *it << " ";
		}
		//cout << endl;
		for (itr = s2.rbegin(); itr != s2.rend(); itr++)
		{
			cout << *itr << " ";
		}
		cout << endl;
	}

	
	cout << "The cost is: " << cost << endl;
	return 0;
}
/*
test case:
4
1 1
1 5
4 5
4 9

4
1 1
2 2
3 3
4 3
*/
/*
0 1 3 2 0
18

0 1 2 3 0
The cost is: 7.43398
*/