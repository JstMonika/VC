#include <bits/stdc++.h>
using namespace std;

ofstream fout;
bool _list[10];
int front = 4;
int back = 5;

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

void solve()
{
    int W = rand() % 15 + 1;
    int H = rand() % 15 + 1;
    
    fout << W << ' ' << H << endl;
    
    for (int i = 0; i < W; i++)
    {
        for (int k = 0; k < H; k++)
            fout << 0;
        fout << endl;
    }
}