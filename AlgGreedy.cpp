/*
Created by 卫昱阳
Copyright  2017年 卫昱阳. All rights reserved.
*/
#include<iostream>
#include<list>
#include<vector>
#include<cmath>
using namespace std;
struct point
{
	double x;
	double y;
};
list<int> circle;
vector<point>v;
int current_max;//当前圈中横坐标最大的点的标号
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
	}//将所有点存入v，按横坐标从小到大输入

	circle.push_back(0);
	circle.push_back(1);
	circle.push_back(2);
	circle.push_back(0);

	current_max = 2;//初始化圈

	for (int i = 3; i < num; i++)//当前添加的点为v[i]
	{
		
		list<int>::iterator it;
		
		for (it = circle.begin(); it != circle.end(); it++)
		{
			if (*it == current_max)
			{
				break;
			}
		}//it指针找到当前横坐标最大的点在list中的位置
		double delta1, delta2;//破圈后增加的量
		int L = *it;
		int M = *(++it);
		it--;
		int N = *(--it);
		it++;
		//对it和(it-1)进行计算
		double first1 = sqrt((v[i].x - v[L].x)*(v[i].x - v[L].x) + (v[i].y - v[L].y)*(v[i].y - v[L].y)) + sqrt((v[i].x - v[M].x)*(v[i].x - v[M].x) + (v[i].y - v[M].y)*(v[i].y - v[M].y));
		double second1 = sqrt((v[L].x-v[M].x)*(v[L].x - v[M].x)+(v[L].y-v[M].y)*(v[L].y - v[M].y));
		delta1 = first1 - second1;
		//对it和(it+1)进行计算
		double first2 = sqrt((v[i].x - v[L].x)*(v[i].x - v[L].x) + (v[i].y - v[L].y)*(v[i].y - v[L].y)) + sqrt((v[i].x - v[N].x)*(v[i].x - v[N].x) + (v[i].y - v[N].y)*(v[i].y - v[N].y));
		double second2 = sqrt((v[L].x - v[N].x)*(v[L].x - v[N].x) + (v[L].y - v[N].y)*(v[L].y - v[N].y));
		delta2 = first2 - second2;
		
		if (delta1 > delta2)//选delta2
		{
			circle.insert(it,i);
		}
		else
		{
			circle.insert(++it,i);
		}
		current_max = i;
	}

	list<int>::iterator re;
	double cost = 0;
	for (re = circle.begin(); re != circle.end(); re++)
	{
		cout << *(re) << " ";
		bool flag = false;
		if ((++re) != circle.end())
		{
			flag = true;
			re--;
			int p = *(re);
			int q = *(++re);
			re--;
			double new_cost = sqrt((v[p].x-v[q].x)*(v[p].x - v[q].x)+(v[p].y-v[q].y)*(v[p].y - v[q].y));
			cost += new_cost;
		}
		if (flag == false)
		{
			re--;
		}
	}
	cout << endl;
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
*/
