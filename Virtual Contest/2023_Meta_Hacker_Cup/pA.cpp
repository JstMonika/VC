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
		
		vec<int> _list(n);
		for (auto &i : _list)
			cin >> i;
			
		sort(al(_list));
		
		// cout << _list[0] << ' ' << _list[1] << ' ' << _list[n-2] << ' ' << _list[n-1] << endl;
		
		double ans;
		ans = ((_list[n-1] + _list[n-2]-(_list[1] + _list[0])) / 2.);
		
		if (n == 5) {
			ans = max(((_list[n-1] + _list[n-2]) - (_list[2] + _list[0])) / 2., ((_list[n-1] + _list[n-3]) - (_list[1] + _list[0]) ) / 2.);
		}

		cout << "Case #" << t++ << ": " << fixed << setprecision(15) << ans << endl;
	}
}