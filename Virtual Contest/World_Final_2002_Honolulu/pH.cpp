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

vec<int> _list, cont;
vec<int> s;

void track(int now, int p) {
    s.eb(now);
    
    if (_list[now] == p) {
        _list[now] = now;
        return;
    }
    
    track(_list[now], p);
    _list[now] = now;
}

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (!n) break;
        
        _list.resize(n);
        cont.clear();
        cont.resize(n);
        for (auto &i : _list) {
            cin >> i;
        }
        
        auto tmp = _list;
        sort(al(tmp));
        
        for (auto &i : _list) {
            i = distance(tmp.begin(), lower_bound(al(tmp), i));
        }
        
        // devec(_list);
        // cout << flush;
        
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            if (_list[i] != i) {
                s.clear();
                track(i, i);
                
                sort(al(s));
                // devec(s);
                if (!i) {
                    cont[s[0]] += s.size() - 1;
                    for (int k = 1; k < s.size(); k++)
                        cont[s[k]]++;
                } else {
                    ll Old = (s.size() - 1) * tmp[s[0]], New = (s.size() + 1) * tmp[0] + 2 * tmp[s[0]];
                    
                    if (Old < New) {
                        cont[s[0]] += s.size() - 1;
                        for (int k = 1; k < s.size(); k++)
                            cont[s[k]]++;
                    } else {
                        cont[0] += s.size() + 1;
                        for (int k = 0; k < s.size(); k++)
                            cont[s[k]]++;
                        cont[s[0]]++;
                    }
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            sum += cont[i] * tmp[i];
        }
            
        cout << "Case " << c++ << ": " << sum << endl << endl;
    }
}