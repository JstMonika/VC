#include <bits/stdc++.h>
using namespace std;

bool bad = false;

bool prefix()
{
    char str;
    if (!(cin >> str))
        return false;
        
    cin.get();
    
    if (isdigit(str))
        return true;
    else
    {
        return prefix() && prefix();
    }
}

int main()
{
    char test;
    bool result = prefix();
    
    if (cin >> test)
        cout << 0;
    else
        cout << result;
}