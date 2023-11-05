#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back
#define endl '\n'

int main() {
    yccc;
	
	int t;
	cin >> t;

	while (t--) {
		int n;
		cin >> n;

		string str;
		cin >> str;

		bool good = false;
		unordered_set<string> _set;
        string test = "aa", prev;
		for (int i = 0; i < str.size()-1; i++) {
			test[0] = str[i];
			test[1] = str[i+1];
			
			if (_set.find(test) != _set.end())
				good = true;
			else {
				if (prev.size() != 0)
					_set.emplace(prev);
				prev = test;
			}
			
			// for (auto &i : _set)
			// 	cout << i << ' ';
			// cout << endl;
        }
		

		cout << (good ? "YES\n" : "NO\n");
	}
}
