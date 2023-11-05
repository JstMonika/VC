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

const ll MOD = 1000000007;

struct Node {
	ll _max, _min, maxidx = 0, minidx = 0;
};

// struct SegTree {
// 	vec<Node> seg, _list;

// 	SegTree(vec<ll> _list, int n) : _list(_list), n(n) {
// 		seg.resize(n);
		
// 		build(0, n-1, 1);
// 	}
	
// 	void build(int l, int r, int idx) {
// 		if (l == r) {
// 			seg[idx].val = _list[l];
			
// 			seg[idx]._max = seg[idx]._min = seg[idx].val;
// 			seg[idx].tag = 0;
// 			return;
// 		}
		
// 		int m = (l + r) / 2;
// 		build(l, m, idx * 2);
// 		build(m+1, r, idx * 2 + 1);
// 	}
	
// 	void pull(int idx) {
// 		;
// 	}
	
// };



int main() {
	yccc;
	
	int c, t = 1;
	cin >> c;
	
	while (c--) {
		int n;
		cin >> n;
		
		vec<ll> _list(n);
		for (auto &i : _list)
			cin >> i;
			
		int s = sqrt(n);
		if (s * s < n) s++;
		
		// cout << s << endl;
		
		vec<Node> block(s);
		for (int i = 0; i < n; i++) {
			if (_list[i] < block[i/s]._min) {
				block[i/s]._min = _list[i];
				block[i/s].minidx = i;
			}
			
			if (_list[i] > block[i/s]._max) {
				block[i/s]._max = _list[i];
				block[i/s].maxidx = i;
			}
		}
		
		// for (auto i : block) {
		// 	if (i.maxidx < 0) cout << i.maxidx << ' ';
		// 	if (i.minidx < 0) cout << i.minidx << ' ';
		// }
		
		// cout << endl;
		
		
		
		ll q, ans = 0;
		cin >> q;
		
		while (q--) {
			
			int S, E;
			cin >> S >> E;
			
			S--, E--;
			int sblock = S / s, eblock = E / s;
			
			sblock++, eblock--;
			
			// cout << S << ' ' << E << ' ' << s << endl;
			for (int i = S; (!(i % s == 0 and i != S)) and i < n; i++) {
				// cout << "S: " << i << endl;
				_list[i] *= -1;
				if (_list[i] < 0) _list[i] += MOD;
			}
			
			int now = S / s;
			block[now]._max = -1e10;
			block[now]._min = 1e10;
			for (int i = S / s * s; i < (S/s+1) * s and i < n; i++) {
				if (_list[i] < block[i/s]._min) {
					block[i/s]._min = _list[i];
					block[i/s].minidx = i;
				}
				
				if (_list[i] > block[i/s]._max) {
					block[i/s]._max = _list[i];
					block[i/s].maxidx = i;
				}
			}
			
			if (E / s != S / s) {
				for (int i = E; (!((i+1) % s == 0 and i != E)) and i >= 0; i--) {
					// cout << "E: " << i << endl;
					_list[i] *= -1;
					if (_list[i] < 0) _list[i] += MOD;
				}
				
				int now = E / s;
				block[now]._max = -1e10;
				block[now]._min = 1e10;
				for (int i = E / s * s; i < (E/s+1) * s and i < n; i++) {
					if (_list[i] < block[i/s]._min) {
						block[i/s]._min = _list[i];
						block[i/s].minidx = i;
					}
					
					if (_list[i] > block[i/s]._max) {
						block[i/s]._max = _list[i];
						block[i/s].maxidx = i;
					}
				}
			}
			
			for (int i = sblock; i <= eblock; i++) {
				// cout << "block: " << i << endl;
				ll neg = (block[i]._max * -1) + MOD;
				block[i]._max = (block[i]._min * -1) + MOD;
				block[i]._min = neg;
				// if (block[i].maxidx < 0) cout << block[i].maxidx << endl;
				swap(block[i].maxidx, block[i].minidx);
				// if (block[i].maxidx < 0) cout << block[i].maxidx << endl;
			}
			
			ll maxval = -1e10, idx = -1;
			for (int i = 0; i < block.size(); i++) {
				// cout << i << ' ' << block[i]._max << ' ' << block[i].maxidx << ' ' << block[i]._min << ' ' << block[i].minidx << endl;
				if (block[i]._max > maxval) {
					maxval = block[i]._max;
					idx = block[i].maxidx;
				}
			}
			
			// cout << idx + 1 << endl;
			ans += idx + 1;
		}
		
		cout << "Case #" << t++ << ": " << ans << endl;
	}
}