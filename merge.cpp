#include <iostream>
#include <assert.h>
#include <cmath>
#include <queue>
#include <set>
#include <list>
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

double calculate_cost_dp(int num);
double calculate_cost_greedy(int num);

int main()
{
    int num;//the number of points
    double hit_ratio;
    int total = 0;
    //cin >> total;
    int a, b;
    cin >> total >> a >> b;
    int hit = 0;
    double delta_sum = 0;
    double delta_average = 0;
    while (cin >> num) {
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
        double result1 = calculate_cost_dp(num);
        double result2 = calculate_cost_greedy(num);
        double delta = (result2 - result1) / result2 * 100;
        delta_sum += delta;
        cout << (result1 == result2) << "\t" << result1 << "\t" << result2 << "\t" << delta << "%" << endl;
        if (result1 == result2) {
            hit++;
        }
        v.clear();
    }
    hit_ratio = (double) hit / total;
    delta_average = delta_sum / total;
    cout << "num_of_points:" << num << ", hit:" << hit << ", total:" << total << ", hit_ratio:" << hit_ratio << ", delta_average:" << delta_average << "%" << endl;
    return 0;
}

double calculate_cost_dp(int num)
{
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

#endif // DEBUG

    }
    else {

#ifdef DEBUG
        cout << "1 in set1" << endl;

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

#endif // DEBUG
    }

    return cost;
}

double calculate_cost_greedy(int num)
{
    list<int> circle;
    circle.clear();
    circle.push_back(0);
    circle.push_back(1);
    circle.push_back(2);
    circle.push_back(0);
    int current_max;//当前圈中横坐标最大的点的标号
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
        double second1 = sqrt((v[L].x - v[M].x)*(v[L].x - v[M].x) + (v[L].y - v[M].y)*(v[L].y - v[M].y));
        delta1 = first1 - second1;
        //对it和(it+1)进行计算
        double first2 = sqrt((v[i].x - v[L].x)*(v[i].x - v[L].x) + (v[i].y - v[L].y)*(v[i].y - v[L].y)) + sqrt((v[i].x - v[N].x)*(v[i].x - v[N].x) + (v[i].y - v[N].y)*(v[i].y - v[N].y));
        double second2 = sqrt((v[L].x - v[N].x)*(v[L].x - v[N].x) + (v[L].y - v[N].y)*(v[L].y - v[N].y));
        delta2 = first2 - second2;

        if (delta1 > delta2)//选delta2
        {
            circle.insert(it, i);
        }
        else
        {
            circle.insert(++it, i);
        }
        current_max = i;
    }

    list<int>::iterator re;
    double cost = 0;
    for (re = circle.begin(); re != circle.end(); re++)
    {
        //cout << *(re) << " ";
        bool flag = false;
        if ((++re) != circle.end())
        {
            flag = true;
            re--;
            int p = *(re);
            int q = *(++re);
            re--;
            double new_cost = sqrt((v[p].x - v[q].x)*(v[p].x - v[q].x) + (v[p].y - v[q].y)*(v[p].y - v[q].y));
            cost += new_cost;
        }
        if (flag == false)
        {
            re--;
        }
    }
    //cout << endl;
    return cost;
}
