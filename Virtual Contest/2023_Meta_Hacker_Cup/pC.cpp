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
	
	int c, t = 1;
	cin >> c;
	
	while (c--) {
		int n;
		cin >> n;
		
		string str;
		cin >> str;
		
		vec<bool> _list(n+1);
		vec<bool> push(n+1);
		for (int i = 1; i <= n; i++) {
			if (str[i-1] == '1') _list[i] = true;
		}
		
		for (int i = 1; i <= n; i++) {
			if (_list[i]) {
				for (int k = i; k <= n; k += i) {
					_list[k] = !_list[k];
				}
				
				push[i] = true;
			}
		}
		
		int q, ss = 0;
		ll ans = 0;
		cin >> q;
		
		for (int i = 0; i < q; i++) {
			int tmp;
			cin >> tmp;
			
			push[tmp] = !push[tmp];
			
		}
		
		for (int i = 1; i <= n; i++) {
			ans += push[i];
		}
		
		
		cout << "Case #" << t++ << ": " << ans << endl;
	}
}