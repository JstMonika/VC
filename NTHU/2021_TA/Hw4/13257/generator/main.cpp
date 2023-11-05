#include <bits/stdc++.h>
using namespace std;

const int cases = 6;

int main()
{
    srand(time(NULL));
    
    for (int i = 0; i < cases; i++)
    {
        int digit = rand() % 100 + 1;
        int B = rand() % 20 + 1;
        
        vector<int> A(digit);
        for (auto &i : A)
            i = rand() % 10;
        A[0] = rand() % 9 + 1;
        
        ofstream fout;
        fout.open("in" + to_string(i) + ".txt");
        
        fout << digit << endl;
        for (auto i : A)
            fout << i;
        fout << endl << B << endl;
    }
}