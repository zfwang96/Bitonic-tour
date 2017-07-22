#include <iostream>
#include <time.h>
#include <set>
using namespace std;

int main (int argc, char* argv[]) {
    int time_count = 0;//atoi(argv[1]);
    int num = 0;//atoi(argv[2]);
    int range = 0;//atoi(argv[3]);
    cin >> time_count >> num >> range;
    cout << time_count << " " << num << " " << range << endl;
    //ofstream out_file("d://data.txt");
    srand((unsigned)time(0));
    while (time_count--) {
        cout << num << endl;
        //out_file << num << endl;
        int *p = new int[num];
        //set<int> p_set;
        for (int i = 0; i < num; i++) {
            p[i] = rand() % range;
            //p_set.insert(p[i]);
        }
        for (int i = 0; i < num; i++) {
            cout << i << " " << p[i] << endl;
            //out_file << i << " " << p[i] << endl;
        }
        cout << endl;
        //out_file << endl;
    }
    return 0;
}
