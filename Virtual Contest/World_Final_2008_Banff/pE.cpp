#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define dbg

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

vec<ll> _list(200);
vec<ll> last(200);
vec<int> hMax(200);

ll ans = 0;

vec<p<int>> que;
vec<int> status;

void go(int now) {
    cout << now << ' ' << _list[que[now].F/2] << ' ' << last[que[now].F/2] << endl;
    devec(status);
    if (now == que.size()) {
        ans++;
        return;
    }
    cout << _list[que[now].F/2] << ' ' << last[que[now].F/2] << endl;
    if (_list[que[now].F/2] != last[que[now].F/2]) {
        int val = last[que[now].F/2];

        if (val >= hMax[que[now].S] and val <= hMax[que[now].S-1]) {
            int tmp = hMax[que[now].S];
            hMax[que[now].S] = val;
            
            last[que[now].F] = val;
            status[now] = val;
            go(now+1);

            hMax[que[now].S] = tmp;
        }
    } else {
        for (int val = hMax[que[now].S]; val <= hMax[que[now].S-1]; val++) {
            int tmp = hMax[que[now].S];
            hMax[que[now].S] = val;
            
            last[que[now].F] = val;
            _list[que[now].F] = val;
            
            last[que[now].F/2] -= val;
            
            status[now] = val;
            go(now+1);

            last[que[now].F/2] += val;
            hMax[que[now].S] = tmp;
        }
    }
}

int level(int i) {
    int ret = 0;
    while (i >> ret) ret++;

    return ret;
}

int main()
{
    yccc;

    int n;
    while (cin >> n) {
        if (!n) break;
        
        ans = 0;

        vec<string> str(n);
        for (auto &i : str)
            cin >> i;

        fill(al(_list), -1);
        fill(al(hMax), 1);
        hMax[0] = 100;
        que.clear();

        for (auto i : str) {
            int now = 1;
            _list[now] = 100;
            for (auto k : i) {
                (now *= 2) += (k == '1');
                _list[now] = 0;
            }
        }
        
        for (int i = 0; i < 200; i++) {
            if (_list[i] != -1) {
                cout << i << ' ' << level(i) << endl;
                que.eb(i, level(i));
            }
        }

        status.resize(que.size(), 0);
        hMax[1] = 100;
        last[1] = 100;
        go(1);
        
        cout << ans << endl;
    }
}
