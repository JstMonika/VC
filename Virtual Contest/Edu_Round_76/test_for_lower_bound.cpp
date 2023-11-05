#include <bits/stdc++.h>
using namespace std;

int main()
{
	int a[5] = {0, 1, 3, 5, 6};
	cout << *(lower_bound(&a[0], &a[0] + 5, 10)) << endl;
}