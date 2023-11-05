#include <bits/stdc++.h>
using namespace std;

int main()
{
    srand(time(NULL));
    
    for (int i = 0; i < 6; i++)
    {
        ofstream fout;
        fout.open("in" + to_string(i) + ".txt");
        
        if (i == 5) 
            fout << "1 100\n";
        else
            fout << rand() % 100 + 1 << ' ' << rand() % 100 + 1 << '\n';
    }
}