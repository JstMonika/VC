#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#ifdef dbg
#define endl '\n'
#endif

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

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
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

struct Ticket {
    int price;
    vec<int> li;

    Ticket() {}
    Ticket(int price, vec<int> src) : price(price), li(src) {}
};

int main()
{
    yccc;

    int n, c = 1;
    while (cin >> n) {
        if (!n)
            break;

        int p, tn;
        vec<Ticket> _list;
        
        set<int> rel;
        map<int, int> rem;

        for (int i = 0; i < n; i++) {
            cin >> p >> tn;
            vec<int> tmp(tn);
            for (auto &k : tmp) {
                cin >> k;
                rel.emplace(k);
            }
            
            _list.eb(p, tmp);
        }

        int idx = 0;
        for (auto it = rel.begin(); it != rel.end(); it++)
            rem[*it] = idx++;

        for (auto &i : _list) {
            for (auto &k : i.li)
                k = rem[k];
        }
        
        for (auto i : _list) {
            auto t = i.li;
            devec(t);
        }
        
        int q, qc = 1;
        cin >> q;

        while (q--) {
            
            int qn;
            cin >> qn;
            vec<int> route(qn);
            for (auto &i : route) {
                cin >> i;
                i = rem[i];
            }
            
            devec(route);
            
            vec<vec<int>> _map(rel.size() * qn + 1, vec<int>(rel.size() * qn + 1, INF));
            for (int i = 1; i < qn; i++) {
                for (int k = 0; k < rel.size(); k++) {
                    for (int r = 0; r < _list.size(); r++) {
                        if (_list[r].li[0] != k) continue;
                        
                        int cur = i;
                        for (int z = 1; z < _list[r].li.size(); z++) {
                            if (cur == qn) break;
                            if (_list[r].li[z] == route[cur])
                                cur++;
                            
                            cout << '(' << k << ", " << i << ')' << " ---> "
                                 << '(' << _list[r].li[z] << ", " << cur << ')' << " = " << _list[r].price << endl;
                            _map[i*(k+1)][cur*(_list[r].li[z]+1)] = _list[r].price;
                        }
                    }
                }
            }
            
            

            // devec2(_map);
            /*
            vec<int> ans;
            cout << "Case " << c << ", Trip " << qc++ << ": Cost = " << cost << endl;
            cout << "  Tickets used:";
            for (auto i : ans)
                cout << ' ' << i;
            cout << endl;
            */
        }
    }
}
