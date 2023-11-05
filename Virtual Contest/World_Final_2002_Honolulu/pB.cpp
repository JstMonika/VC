#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
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

tuple<bool, string, string, string> check(pair<string, string> now, string src) {
    
    // cout << "->\n";
    // cout << now.F << ' ' << now.S << ' ' << src << ' ';
    
    int size = now.F.size();
    now.F += src;
    
    for (int i = size; i < min(now.F.size(), now.S.size()); i++) {
        if (now.F[i] != now.S[i]) {
            // cout << "NO\n";
            return make_tuple(false, "", "", "");
        }
    }
    
    if (now.F.size() > now.S.size())
        swap(now.F, now.S);
    
    // cout << "YES\n";
    return make_tuple(true, now.F, now.S, now.S.substr(now.F.size()));
}

bool init(string a, string b) {
    for (int i = 0; i < min(a.size(), b.size()); i++)
        if (a[i] != b[i]) return false;
    
    return true;
}

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        vec<string> str(n);
        for (auto &i : str)
            cin >> i;
            
        using pss = pair<string, string>;
        
        auto cmp = [](pss a, pss b) { 
            if (a.S.size() != b.S.size()) 
                return a.S.size() > b.S.size(); 
            
            return a.S > b.S;
        };
        
        set<string> exist;
        priority_queue<pss, vec<pss>, decltype(cmp)> pq(cmp);
        
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < i; k++) {
                if (init(str[i], str[k])) {
                    if (str[i].size() > str[k].size())
                        pq.emplace(str[k], str[i]);
                    else
                        pq.emplace(str[i], str[k]);
                }
            }
        }
        
        while (!pq.empty()) {
            auto now = pq.top();
            pq.pop();
            
            exist.insert(now.S.substr(now.F.size()));
            
            if (now.F == now.S) {
                cout << "Code " << c++ << ": " << now.F.size() << " bits\n";
                
                for (int i = 0; i < now.F.size(); i++) {
                    if (i and  i % 20 == 0)
                        cout << endl;
                    
                    cout << now.F[i];
                }
                
                cout << endl << endl;
                break;
            }
            
            for (auto i : str) {
                bool good;
                string a, b, rest;
                
                tie(good, a, b, rest) = check(now, i);
                
                if (good) {
                    if (exist.find(rest) == exist.end())
                        pq.emplace(a, b);
                }
                
            }
        }
    }
}