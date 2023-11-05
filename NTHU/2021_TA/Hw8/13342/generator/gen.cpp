#include <bits/stdc++.h>
using namespace std;

ofstream fout;
const int cases = 6;
const int len = 10;
int _count;

void prefix()
{
    _count++;
    
    if (rand() % 10 < 5 or _count >= len)
        fout << rand() % 9 + 1 << ' ';
    else
    {
        switch (rand() % 4)
        {
            case 0:
                fout << '+' << ' ';
                break;
            case 1:
                fout << '-' << ' ';
                break;
            case 2:
                fout << '*' << ' ';
                break;
            case 3:
                fout << '/' << ' ';
                break;
        }
        
        prefix();
        prefix();
    }
}

int main()
{
    srand(time(NULL));
    
    for (int i = 0; i < cases; i++)
    {
        continue;
            
        fout.open("in" + to_string(i) + ".txt");
        
        prefix();
        
        fout.close();
    }
}