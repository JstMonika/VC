#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

int main() {
	yccc;
	
	int n, s;
	cin >> n >> s;
	
	vec<int> _list(n);
	for (auto &i : _list)
		cin >> i;
	
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int k = i+1; k < n; k++) {
			if (_list[k] >= _list[i])
				for (int j = k+1; j < n; j++) {
					if (_list[j] >= _list[k])
						for (int l = j+1; l < n; l++) {
							if (_list[l] >= _list[j]) {
								if (_list[i] + _list[k] + _list[j] + _list[l] == s)
									ans++;
							}
						}
				}
		}
	}
	
	cout << ans << endl;
}