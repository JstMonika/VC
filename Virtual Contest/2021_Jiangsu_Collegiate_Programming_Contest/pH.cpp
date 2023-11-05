#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

// #define dbg

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

#ifndef dbg
#define endl '\n'
#define debug(x) ;
#define devec(v) ;
#define devec2(v) ;
#else
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
#endif

const int INF = 1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-6;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-6) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

const ll prime = 1073676287;

vec<ll> h_front, h_back, h_base;

void init_hash(string str, ll mod_prime = 0xdefaced) {
    int n = str.size();
    h_front.resize(n+1);
    h_back.resize(n+1);
    h_base.resize(n+1);
    
    h_front[0] = h_back[0] = 0;
    h_base[0] = 1;
    
    for (int i = 0; i < n; i++) {
        h_front[i+1] = (h_front[i] * prime + str[i]) % mod_prime;
        h_back[i+1] = (h_back[i] * prime + str[n-i-1]) % mod_prime;
        h_base[i+1] = (h_base[i] * prime) % mod_prime;
    }
}

string str;
ll get_hash(int s, int l, int dis) {
    int s_idx = str.size() - l, len = dis - s + 1;
    ll mod_prime = 0xdefaced;
    
    if (dis <= l) {
        //* s ~ dis
        
        return (h_back[s_idx+len] - (h_back[s_idx] * h_base[len] % mod_prime) + mod_prime) % mod_prime;
    } else {
        ll lLen = l - s + 1;
        
        ll f = (h_back[s_idx+lLen] - (h_back[s_idx] * h_base[lLen] % mod_prime) + mod_prime) % mod_prime;
        ll s = (h_front[dis+1] - (h_front[l] * h_base[dis-l+1] % mod_prime) + mod_prime) % mod_prime;
        
        return (f + s + mod_prime) % mod_prime;
    }
}

int main()
{
    yccc;
    
    int c;
    cin >> c;
    
    while (c--) {
        cin >> str;
        
        string tmp = str;
        sort(al(tmp));
        
        int idx = 0;
        while (idx < str.size()) {
            if (tmp[idx] != str[idx]) break;
            idx++;
        }
        
        if (idx == str.size())
            cout << str << endl;
        else {
            // reverse(al(str));
            init_hash(str);
            
            ll best = 0;
            for (int i = 1; i + idx < str.size(); i++) {
                //* 0 ~ idx-1, idx ~ idx+i, idx+i+1 ~ str.size()-1;
                
                int L = idx, R = str.size()-1, right = idx-1;
                while (L <= R) {
                    int M = (L + R) / 2;
                    
                    if (get_hash(idx, idx+best, M) == get_hash(idx, idx+i, M)) {
                        right = M;
                        L = M+1;
                    } else R = M-1;
                }
                
                if (right+1 < str.size()) {
                    char b = (right+1 > idx+best ? str[right+1] : str[idx+best + idx - (right+1)]);
                    char now = (right+1 > idx+i ? str[right+1] : str[idx+i + idx - (right+1)]);
                    
                    if (now < b)
                        best = i;
                }
            }
            
            for (int i = 0; i < (best+1)/2; i++) {
                swap(str[idx+i], str[idx+best-i]);
            }
            
            cout << best << endl;
            cout << str << endl;
        }
    }
}