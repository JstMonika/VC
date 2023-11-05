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
#define REP(i, n) for (int i = 0; i < n; i++)
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

int main()
{
    yccc;
    
    int n, c = 1;
    string s, e;
    while (cin >> s) {
        if (s == ".") break;
        
        cin >> e >> n;
        
        set<p<string>> one;
        deq<p<string>> _list(n);
        for (int i = 0; i < n; i++) {
            cin >> _list[i].F >> _list[i].S;
            one.emplace(_list[i].F, _list[i].S);
        }
        _list.emplace_front(make_pair(s, e));
        
        map<p<string>, ll> cost;
        cost[make_pair(s, s)] = 0;
        cost[make_pair(e, e)] = 0;
        
        for (int l = 1; l <= s.size(); l++) {
            vec<string> now;
            
            for (auto i : _list) {
                if (i.F.size() >= l)
                    now.eb(i.F.substr(i.F.size() - l));
                if (i.S.size() >= l)
                    now.eb(i.S.substr(i.S.size() - l));
            }
            
            sort(al(now));
            now.resize(distance(now.begin(), unique(al(now))));
            
            // devec(now);
            
            vec<vec<ll>> G(205, vec<ll>(205, llINF));
            
            for (int i = 0; i < now.size(); i++)
                for (int k = 0; k < now.size(); k++) {
                    if (one.count(make_pair(now[i], now[k]))) {
                        // cout << now[i] << " -> " << now[k] << ": 1\n";
                        G[i][k] = 1;
                    }
                    else if (now[i][0] == now[k][0]) {
                        auto it = cost.find(make_pair(now[i].substr(1), now[k].substr(1)));
                        G[i][k] = (it == cost.end() ? llINF : it->S);
                    }
                }
            
            for (int r = 0; r < now.size(); r++) {
                for (int i = 0; i < now.size(); i++)
                    for (int k = 0; k < now.size(); k++)
                        G[i][k] = min(G[i][k], G[i][r] + G[r][k]);
            }
            
            for (int i = 0; i < now.size(); i++)
                for (int k = 0; k < now.size(); k++)
                    if (G[i][k] != llINF) {
                        cost[make_pair(now[i], now[k])] = G[i][k];
                        // cout << now[i] << ' ' << now[k] << ' ' << G[i][k] << endl;
                    }
        }
        
        cout << "Case " << c++ << ": ";
        if (cost.find(make_pair(s, e)) != cost.end())
            cout << cost[make_pair(s, e)] << endl;
        else
            cout << "No solution\n";
    }
}