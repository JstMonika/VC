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

vec<int> go(vec<int> _list) {
	ll sum = 0;
	for (auto i : _list) sum += i;
	
	if (sum == 41) return _list;
	
	for (int i = 0; i < _list.size(); i++) {
		for (int k = i+1; k < _list.size(); k++) {
			auto tmp = _list;
			tmp[i] = tmp[i] * tmp[k];
			tmp[k] = tmp.back();
			tmp.pop_back();
			
			ll check = 0;
			for (auto i : _list) check += i;
			
			if (sum > 41) continue;
			
			auto ret = go(tmp);
			
			if (ret.size() != 0) return ret;
		}
	}
	
	return vec<int>();
}

int main() {
	yccc;
	
	int c, t = 1;
	cin >> c;
	
	while (c--) {
		
		ll n;
		cin >> n;
		
		map<int, int> _map;
		
		ll sum = 0;
		for (int i = 2; i * i <= n; i++) {
			while (n % i == 0) {
				_map[i]++;
				n /= i;
				
				sum += i;
			}
		}
		
		if (n != 1) {
			_map[n]++;
			sum += n;
		}
		
		if (sum > 41) cout << "Case #" << t++ << ": " << -1 << endl;
		else {
			sum = 0;
			
			vec<int> _list;
			for (auto i : _map) {
				// cout << i.first << ' ' << i.second << endl;
				while (i.second--) {
					_list.eb(i.first);
					sum += i.first;
				}
			}
			
			while (sum != 41) {
				_list.eb(1);
				sum++;
			}
			
			cout << "Case #" << t++ << ": " << _list.size();
			for (auto i : _list)
				cout << ' ' << i;
			cout << endl;
		}
	}
}