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

const int MAX = 3000005;
ll mod;

ll fact[MAX], tcaf[MAX];

ll binpow(ll x, ll d) {
	if (d < 0) d += mod-1;
	
	ll y = 1;
	do {
		if (d & 1) (y *= x) %= mod;
		(x *= x) %= mod;
	} while (d >>= 1);
	
	return y;
}

void init(int n) {
	fact[0] = 1;
	for (int i = 1; i <= n; i++) {
		fact[i] = i * fact[i-1] % mod;
	}
	for (int i = n; i >= 0; i--) {
		tcaf[i] = binpow(fact[i], -1);
	}
}

ll nCr(int n, int r) {
	if (r < 0 or r > n) return 0;

	return fact[n] * tcaf[r] % mod * tcaf[n-r] % mod;
}

int main() {
    yccc;
    
    ll n;
    cin >> n >> mod;
	
	init(n+10);
    
    ll limit = (n+1) / 2, ans = 0;

	if ((n & 1) == 0) {
		ans += n * fact[n-2] % mod;
	}
	
	// cout << ans << endl;
    
    for (int i = 2; i <= limit; i++) {
		for (int k = 0; k <= i-2; k++) {
			// cout << "ik: " << i << ' ' << k << endl;
			ll count = (n & 1 ? i - 1 : i);
			
			// cout << limit-2 << ' ' << k << endl;
			// cout << n << ' ' << nCr(i-2, k) << ' ' << count << ' ' << fact[n-3-k] << endl;
			
			ans += n * nCr(i-2, k) % mod * count % mod * fact[n - 3 - k] % mod;
			ans %= mod;
		}
    }
	
	cout << ans << endl;
}