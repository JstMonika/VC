#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[])
{
	int N, L;
    for (int k = 0; k < 6; k++)
    {
        ofstream fout;
        fout.open("in" + to_string(k) + ".txt");
        
        N = rnd.next(3, 1000);
        L = rnd.next(3, 10);
        
        fout << N << ' ' << L << endl;
        
        for (int i = 0; i < N; i++)
            fout << rnd.next(0, 1000) << " \n"[i == N-1];
    }
}