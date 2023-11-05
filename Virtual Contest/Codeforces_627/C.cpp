#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	cin.get();
	
	while (c--)
	{
		int count = 0, MAX = 0;
		char tmp;
		while ((tmp = cin.get()) != '\n')
		{
			if (tmp == 'L')
				MAX = (MAX > (++count)) ? MAX : count;
			else
				count = 0;
		}
		
		cout << MAX+1 << endl;
	}
}