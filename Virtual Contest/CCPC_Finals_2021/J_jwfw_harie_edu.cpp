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

const int INF = 0x3f3f3f3f;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

int n;

vec<set<char>> answer(10);
vec<pair<string, int>> _list;

ll ans = 0;

void go(int now, vec<int> score) {
    if (now == n) {
        ll ret = 1;
        
        for (auto i : answer) ret *= i.size();
        ans += ret;
        
        return;
    }
    
    int last = 0;
    vec<int> problem;
    for (int i = 0; i < 10; i++) 
        if (answer[i].size() != 1)  {
            problem.eb(i);
            last++;
        }
    
    // cout << _list[now].S - score[now] << ' ' << last - _list[now].S + score[now] << endl << flush;
    string choose = string(_list[now].S - score[now], '1') + string(last - _list[now].S + score[now], '0');
    
    
    auto tmp = answer;
    auto tmpScore = score;
    do {
        // cout << choose << endl;
        
        for (int i = 0; i < problem.size(); i++) {
            if (choose[i] == '1') {
                answer[problem[i]].clear();
                answer[problem[i]].emplace(_list[now].F[problem[i]]);
            } else {
                answer[problem[i]].erase(_list[now].F[problem[i]]);
            }
            
            if (answer[problem[i]].size() == 1) {
                for (int k = 0; k < n; k++) {
                    if (*(answer[problem[i]].begin()) == _list[k].F[problem[i]])
                        score[k]++;
                }
            }
        }
        
        int rest = 0;
        for (int i = 0; i < 10; i++) {
            if (answer[i].size() != 1) rest++;
        }
        
        bool good = true;
        for (int i = 0; i < n; i++) {
            if (score[i] + rest < _list[i].S) good = false;
            if (score[i] > _list[i].S) good = false;
        }
        
        // for (auto i : answer) {
        //     cout << i.size() << ' ';
        // }
        // cout << endl;
        
        if (good) {
            go(now+1, score);
        }
        
        score = tmpScore;
        answer = tmp;
    } while (prev_permutation(al(choose)));
}

int main()
{
    yccc;
    
    int t;
    cin >> t;
    
    while (t--) {
        ans = 0;

        cin >> n;
        _list.resize(n);
        
        
        for (auto &i : _list) {
            cin >> i.F >> i.S;
            i.S /= 10;
        }
        
        for (int i = 0; i < 10; i++) {
            answer[i].emplace('A');
            answer[i].emplace('B');
            answer[i].emplace('C');
            answer[i].emplace('D');
        }
        
        vec<int> score(n);
        go(0, score);
        
        cout << ans << endl;
    }
}
/*

int n;
string str = "AAAAA";

struct hasher {
    size_t operator() (const vec<int>& c) const {
        size_t seed = c.size();
        
        for (auto i : c) {
            i = ((i >> 16) ^ i) * 0x45d9f3b;
            i = ((i >> 16) ^ i) * 0x45d9f3b;
            i = (i >> 16) ^ i;
            
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        
        return seed;
    }
};

vec<pair<string, int>> _list;
unordered_map<vec<int>, ll, hasher> _map;

ll ans = 0;

void go(int now, bool type) {
    if (now == 5) {
        if (type) {
            vec<int> point(n);
            for (int i = 0; i < n; i++)
                for (int k = 0; k < 5; k++)
                    if (_list[i].F[k] == str[k]) point[i]++;
            
            _map[point]++;
        } else {
            vec<int> point(n);
            for (int i = 0; i < n; i++) {
                point[i] = _list[i].S / 10;
                
                for (int k = 0; k < 5; k++) {
                    if (_list[i].F[k+5] == str[k]) point[i]--;
                }
            }
            
            ans += _map[point];
        }
        
        return;
    }
    
    for (int i = 0; i < 4; i++) {
        str[now] = 'A' + i;
        go(now+1, type);
    }
}

int main()
{
    yccc;
    
    int t;
    cin >> t;
    
    while (t--) {
        ans = 0;

        cin >> n;
        _list.resize(n);
        
        _map.clear();
        
        for (auto &i : _list) {
            cin >> i.F >> i.S;
        }
        
        go(0, true);
        go(0, false);
        
        cout << ans << endl;
    }
}

*/