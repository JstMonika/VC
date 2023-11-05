
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T> using vec = vector<T>;
template<typename T> using p = pair<T, T>;
template<typename T> using deq = deque<T>;

#define endl '\n'
#define F first
#define S second
#define eb emplace_back
#define al(a) a.begin(),a.end()


deq<bool> exi(1000005);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
	int n;

/*
*/
    while (cin >> n) {
        if (!n) break;
    
    fill(al(exi), false);

	map<int, bool> multi;
	map<int, int> _map;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;

		exi[num] = true;

		_map[num]++;
	}

	for (auto i : _map) {
		bool good = false;

		for (int k = i.F * 2; k <= 1000000; k += i.F) {
			if (exi[k]) {
				good = true;
				break;
			}
		}

		multi[i.F] = good;
	}
	
	vec<int> mul, not_mul;
	for (auto i : _map) {
		if (multi[i.F])
			mul.eb(i.S);
		else
			not_mul.eb(i.S);
	}
	
	sort(al(mul));
	sort(al(not_mul));

	vec<int> _list;
    
	// for (auto i : mul)
	// 	cout << i << ' ';
	// cout << endl;

	// for (auto i : not_mul)
	// 	cout << i << ' ';
	// cout << endl;

	int idx = 0, idx2 = 2;
	if (not_mul.size() >= 2) {
		while (idx < mul.size() and mul[idx] < not_mul[0] + not_mul[1]) {
			_list.eb(mul[idx++]);
		}

		_list.eb(not_mul[0] + not_mul[1]);

		while (idx < mul.size() and idx2 < not_mul.size()) {
			if (mul[idx] <= not_mul[idx2])
				_list.eb(mul[idx++]);
			else _list.eb(not_mul[idx2++]);
		}

		while (idx < mul.size()) _list.eb(mul[idx++]);
		while (idx2 < not_mul.size()) _list.eb(not_mul[idx2++]);
	} else {
		_list = mul;
	}

	// for (auto i : _list)
	// 	cout << i << ' ';
	// cout << endl;
    
	for (int i = 1; i < _list.size(); i++) {
		_list[i] += _list[i-1];
	}
	/*
	*/
	cout << _map.size();
	for (int i = 1; i < n; i++) {
		auto ans = distance(_list.begin(), upper_bound(al(_list), i));
//		cout << ans << endl;
		cout << ' ' << _map.size() - ans;
	}
	cout << ' ' << 1;
    
    cout << '\n';
}
}
