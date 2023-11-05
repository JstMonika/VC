#include <bits/stdc++.h>
using namespace std;

ofstream fout;
bool _list[10];
int front = 8;
int back = 8;

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
    int t = rand() % 4 + 1;
    fout << t << endl;
    
    for (int i = 0; i < t; i++)
    {
        int len = rand() % 4 + 1;
        vector<int> exist(26);
        
        for (int k = 0; k < len; k++)
        {
            int tmp;
            do
            {
                tmp = rand() % 26;
            } while (exist[tmp]);
            fout << char('a' + tmp);
            exist[tmp] = 1;
        }
        
        fout << endl;
    }
}