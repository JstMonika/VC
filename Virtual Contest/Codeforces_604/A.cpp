#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		string str;
		cin >> str;
		
		bool good = true;
		
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == '?')
				for (char ch = 'a'; ch != 'd'; ch++)
				{
					if (i and str[i-1] == ch and str[i-1] != '?')
						continue;
					
					if (i != str.size()-1 and str[i+1] == ch and str[i+1] != '?')
						continue;
					
					str[i] = ch;
					break;
				}
				
			if (i and str[i] == str[i-1])
			{
				good = false;
				break;
			}
		}
		
		if (good)
			cout << str << endl;
		else
			cout << -1 << endl;
	}
}