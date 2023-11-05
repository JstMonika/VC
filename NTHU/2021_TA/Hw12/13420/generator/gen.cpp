#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

ofstream fout;
bool _list[10];
int front = 0;
int back = 7;

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

bool exist[100][100];

void solve()
{
    int N = rand() % 100 + 1;
    
    int K = rand() % (N);
    
    fout << N << ' ' << K << endl;
    
    for (int i = 0; i < K; i++) {
        int a, b;
        do {
            a = rand() % N;
            b = rand() % N;
        } while (a == b or exist[a][b]);
        
        exist[a][b] = true;
        exist[b][a] = true;
        
        fout << a << ' ' << b << endl;
    }
}