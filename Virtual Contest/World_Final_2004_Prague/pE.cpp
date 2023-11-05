#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

string convert(int day) {
    int d = day % 100;
    int m = (day /= 100) % 100;
    int y = day /= 100;
    
    string ret = to_string(m) + '/' + to_string(d) + '/' + to_string(y);
    
    return ret;
}

int cal[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool first(pii prev, pii now) {
    if (prev.F == now.F) {
        if (prev.S == 1) return true;
        else return false;
    }
    
    return prev.F < now.F;
}

int prv(int day) {
    int d = day % 100;
    int m = (day /= 100) % 100;
    int y = day /= 100;
    
    d--;
    
    if (m == 3) {
        bool leap = ((y % 4 == 0) and (y % 100 != 0)) or (y % 400 == 0);
        
        if (leap and d < 1) {
            m--;
            d = 29;
        }
        else if (!leap and d < 1) {
            m--;
            d = 28;
        }
    } else {
        if (d < 1) {
            m--;
            
            if (m == 0) {
                m = 12;
                y--;
            }
            
            d = cal[m];
        }
    }
    
    return y * 10000 + m * 100 + d;
}

int nxt(int day) {
    int d = day % 100;
    int m = (day /= 100) % 100;
    int y = day /= 100;
    
    d++;
    
    if (m == 2) {
        bool leap = ((y % 4 == 0) and (y % 100 != 0)) or (y % 400 == 0);
        
        if (leap and d > 29) {
            m++;
            d = 1;
        }
        else if (!leap and d > 28) {
            m++;
            d = 1;
        }
       
    } else {
        if (d > cal[m]) {
            d = 1;
            m++;
            
            if (m > 12) {
                m = 1;
                y++;
            }
        }
    }
    
    return y * 10000 + m * 100 + d;
}

int main()
{
    yccc;
    
    int n, m, c = 1;
    while (cin >> n >> m) {
        if (n == 0 and m == 0) break;
            
        if (c != 1) cout << endl;
        
        vec<pii> prev(2*n), now(2*m);
        for (int i = 0; i < n; i++) {
            cin >> prev[i*2].F >> prev[i*2+1].F;
            prev[i*2].S = 1, prev[i*2+1].S = -1;
        }
        for (int i = 0; i < m; i++) {
            cin >> now[i*2].F >> now[i*2+1].F;
            now[i*2].S = 1, now[i*2+1].S = -1;
        }
        
        auto cmp = [](pii a, pii b) {
            if (a.F == b.F)
                return a.S > b.S;
            return a.F < b.F;
        };
        
        sort(al(prev), cmp);
        sort(al(now), cmp);
        
        int i = 0, k = 0, ci = 0, ck = 0, past = -1;
        
        vec<pii> ans;
        while (!(i == 2*n and k == 2*m)) {
            if (i == 2*n) goto flag_k;
            if (k == 2*m) goto flag_i;
            
            if (first(prev[i], now[k])) {
                flag_i:
                
                if (ck > 0 and ci == 0) {
                    if (past <= prv(prev[i].F))
                        ans.eb(past, prv(prev[i].F));
                    past = -1;
                }
                
                ci += prev[i].S;
                
                if (ck > 0 and ci == 0)
                    past = nxt(prev[i].F);
                    
                // cout << "i: " << ci << ' ' << ck << ' ' << prev[i].F << endl;
                i++;
            } else {
                flag_k:
                
                if (ck > 0 and ci == 0) {
                    if (past != -1) {
                        ans.eb(past, now[k].F);
                    }
                }
                
                ck += now[k].S;
                
                if (ck == 0)
                    past = -1;
                else if (ck > 0 and ci == 0)
                    past = now[k].F;
                
                // cout << "k: " << ci << ' ' << ck << ' ' << now[k].F << endl;
                k++;
            }
        }
        
        if (ans.size() != 0) {
            sort(al(ans));
            
            vec<pii> tmp = {ans[0]};
            for (int i = 1; i < ans.size(); i++) {
                if (prv(ans[i].F) <= tmp.back().S) {
                    tmp.back().S = max(ans[i].S, tmp.back().S);
                } else {
                    tmp.eb(ans[i]);
                }
            }
            
            cout << "Case " << c++ << ":\n";
            for (auto i : tmp) {
                if (i.F == i.S)
                    cout << "    " << convert(i.F) << endl;
                else
                    cout << "    " << convert(i.F) << " to " << convert(i.S) << endl;
            }
            
        } else {
            //* no need
            cout << "Case " << c++ << ":\n    No additional quotes are required.\n";
        }
    }
}