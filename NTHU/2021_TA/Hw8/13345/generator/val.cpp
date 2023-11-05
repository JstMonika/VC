#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    
    if (cin >> T)
    {
        cin.get();
        
        for (int c = 0; c < T; c++)
        {
            string str;
            cin >> str;
            cin.get();
            
            vector<int> _list(26);
            for (int i = 0; i < str.size(); i++)
            {
                if (_list[str[i] - 'a'])
                    cout << 0 << endl;
                else
                    _list[str[i] - 'a']++;
            }
        }
    }
    else cout << -1 << endl;
    
    char s;
    if (cin >> s)
        cout << -2 << endl;
}