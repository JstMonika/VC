#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

ofstream fout;
bool _list[10];
int front = 5;
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

void solve()
{
    int N = rand() % 400 + 600, K = N + N/3;
    deque<deque<bool>> visit(N, deque<bool>(N));   
    
    fout << N << ' ' << K << ' ' << rand() % N + 1 << endl;
    
    for (int i = 0; i < K; i++) {
        
        int A = rand() % N;
        int B = rand() % N;
        
        while (A == B or visit[A][B]) {
            A = rand() % N;
            B = rand() % N;
        }
        
        fout << A+1 << ' ' << B+1 << endl;
        visit[A][B] = true;
    }
}