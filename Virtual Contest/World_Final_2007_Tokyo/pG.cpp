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
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

struct Packet {
    int idx, st, ed;
    
    Packet() {}
};

istream& operator>>(istream& in, Packet& src) {
    in >> src.idx >> src.st >> src.ed;
    
    return in;
}

int main()
{
    yccc;
    
    int n, m, c = 1;
    while (cin >> n >> m) {
        if (!n) break;
        
        int r_ans = INF;
        vec<int> _list(n), order(n);
        vec<Packet> p_list(m);
        
        for (auto &i : _list)
            cin >> i;
        for (int i = 0; i < n; i++)
            order[i] = i+1;
        for (int i = 0; i < m; i++)
            cin >> p_list[i];
            
        do {
            int next = 0, nSize = 0, ans = 0;
            vec<int> now(n+1, 0);
            map<p<int>, int> _map;
            
            for (int i = 0; i < m; i++) {
                if (p_list[i].idx == order[next]) {
                    if (p_list[i].st == now[order[next]]+1) {
                        now[order[next]] = p_list[i].ed;
                        if (now[order[next]] == _list[order[next]-1]) next++;
                        
                        while (next < n and _map.find(make_pair(order[next], now[order[next]]+1)) != _map.end()) {
                            nSize -= _map[make_pair(order[next], now[order[next]]+1)] - now[order[next]];
                            now[order[next]] = _map[make_pair(order[next], now[order[next]]+1)];
                            if (now[order[next]] == _list[order[next]-1]) next++;
                        }
                    } else {
                        _map[make_pair(p_list[i].idx, p_list[i].st)] = p_list[i].ed;
                        nSize += p_list[i].ed - p_list[i].st + 1;
                    }
                } else {
                    _map[make_pair(p_list[i].idx, p_list[i].st)] = p_list[i].ed;
                    nSize += p_list[i].ed - p_list[i].st + 1;
                }
                
                devec(now);
                debug(nSize);
                ans = max(ans, nSize);
            }
            
            r_ans = min(r_ans, ans);
            // cout << "------\n";
        } while (next_permutation(al(order)));
        
        cout << "Case " << c++ << ": " << r_ans << endl << endl;
    }
}