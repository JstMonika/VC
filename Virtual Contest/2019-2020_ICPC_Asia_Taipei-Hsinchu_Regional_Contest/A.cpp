#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define eb emplace_back
#define endl '\n'
#define F first
#define S second
#define al(a) a.begin(),a.end()

char ch(int num) {
	return 'a' + num;
}

int idx(int r, int c) {
	return r * 6 + c;
}

bool goal(string str) {
	return (str[idx(2, 4)] == ch(1) and str[idx(2, 5)] == ch(1));
}

bool valid(string str, int car, int type) {
	vec<p<int>> _list;
	vec<int> val;
	for (int i = 0; i < 6; i++) {
		for (int k = 0; k < 6; k++) {
			if (str[idx(i, k)] == ch(car)) {
				_list.eb(i, k);
				val.eb(idx(i, k));
			}
		}
	}
	
	if (val.size() == 0) return false;

	if (abs(val[0] - val[1]) == 1) { // hori.
		int sub = (type ? 1 : -1);

		for (auto i : _list) {
			if (i.S + sub >= 6 or i.S + sub < 0) return false;

			char chr = str[idx(i.F, i.S+sub)];
			if (chr != ch(0) and chr != ch(car))
				return false;
		}
		
		return true;
	} else { // vertical
		int sub = (type ? 1 : -1);

		for (auto i : _list) {
			if (i.F + sub >= 6 or i.F + sub < 0) return false;

			char chr = str[idx(i.F+sub, i.S)];
			if (chr != ch(0) and chr != ch(car))
				return false;
		}
		
		return true;
	}
}

string go(string str, int car, int type) {
	vec<p<int>> _list;
	vec<int> val;
	for (int i = 0; i < 6; i++) {
		for (int k = 0; k < 6; k++) {
			if (str[idx(i, k)] == ch(car)) {
				_list.eb(i, k);
				val.eb(idx(i, k));
			}
		}
	}

	for(auto i : _list) {
		str[idx(i.F, i.S)] = ch(0);
	}

	if (abs(val[0] - val[1]) == 1) { // hori.
		int sub = (type ? 1 : -1);

		for (auto i : _list) {
			str[idx(i.F, i.S+sub)] = ch(car);
		}
		
		return str;
	} else { // vertical
		int sub = (type ? 1 : -1);

		for (auto i : _list) {
			str[idx(i.F+sub, i.S)] = ch(car);
		}
		
		return str;
	}
}

int main() {
	yccc;

	string str(36, ' ');
	for (int i = 0; i < 36; i++) {
		int num;
		cin >> num;

		str[i] = 'a' + num;
	}

	set<string> _set;

	queue<string> que;
	que.emplace(str);
	_set.emplace(str);
	
	int count = 0;
	while (!que.empty() and count <= 8) {
		int n = que.size();
		for (int i = 0; i < n; i++) {
			auto now = que.front();
			que.pop();

			if (goal(now)) {
				cout << count + 2;
				/*
				for (int i = 0; i < 6; i++) {
					for (int k = 0; k < 6; k++) {
					cout << now[i*6+k] - 'a' << ' ';
					}
					cout << endl;
				}
				*/
				return 0;
			}
			
			for (int k = 1; k <= 10; k++) {
				string ret;
				if (valid(now, k, 0)) {
					ret = go(now, k, 0);

					if (_set.find(ret) == _set.end()) {
						_set.emplace(ret);
						que.emplace(ret);
					}
				}

				if (valid(now, k, 1)) {
					ret = go(now, k, 1);

					if (_set.find(ret) == _set.end()) {
						que.emplace(ret);
						_set.emplace(ret);
					}
				}
			}
		}
		count++;
	}

	cout << -1;
}
