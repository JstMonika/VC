#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

ofstream fout;
bool _list[10];
int front = 6;
int back = 6;

void solve();

int main()
{
    for (int i = 0; i < 10; i++) _list[i] = ((i >= front and i <= back) ? 1 : 0);
    srand(time(NULL));
    
    for (int i = 0; i <= back; i++)
    {
        if (!_list[i])
            continue;
            
        fout.open("in" + to_string(i) + ".txt");
        
        solve();
        
        fout.close();
    }
}

// TLE, MLE.

void solve()
{
    int ins = 100000, _max = 100;
    
    int pro[5] = {5, 5, 1, 2, 0};
    for (int i = 1; i < 5; i++) pro[i] += pro[i-1];
    
    for (int i = 0; i < ins; i++) {
        int now = rand() % pro[4];
        
        int num = rand() % _max;
        if (now < pro[0]) {
            fout << "AddFront " << num << endl;
        }
        else if (now < pro[1]) {
            fout << "AddBack " << num << endl;
        }
        else if (now < pro[2]) {
            fout << "Delete " << num << endl;
        }
        else if (now < pro[3]) {
            fout << "DeleteFront" << endl;
        }
        else {
            fout << "DeleteBack" << endl;
        }
    }
}