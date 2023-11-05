#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
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

double fcmp(double a, double b) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int n, m, k, c = 1;
vec<int> _list;
vec<pair<vec<int>, int>> intersect;

deq<bool> selectList, Rlist;
int Rans;

void dfs(int i, int last) {
    if (last == 0) {
        
        int ans = 0;
        for (int k = 0; k < m; k++) {
            for (int z = 0; z < intersect[k].F.size(); z++)
                if (selectList[intersect[k].F[z]]) {
                    ans += intersect[k].S;
                    break;
                }
        }
        
        for (int k = 1; k <= n; k++)
            if (selectList[k])
                ans += _list[k];
            
        if (ans > Rans) {
            // devec(selectList);
            Rlist = selectList;
            Rans = ans;
        }
        
        return;
    }
    
    if (i == n+1)
        return;
        
    selectList[i] = true;
    dfs(i+1, last-1);
    selectList[i] = false;
    dfs(i+1, last);
}


int main()
{
    yccc;
    
    while (cin >> n >> k) {
        if (!n)
            break;
        
        Rans = 0;
        _list.resize(n+1);
        
        selectList.clear();
        selectList.resize(n+1, false);
        for (int i = 1; i <= n; i++)
            cin >> _list[i];
            
        cin >> m;
        
        intersect.resize(m);
        for (int i = 0; i < m; i++) {
            int s;
            cin >> s;
            intersect[i].F.resize(s);
            
            for (int k = 0; k < s; k++) {
                cin >> intersect[i].F[k];
            }
            
            cin >> intersect[i].S;
            for (auto k : intersect[i].F)
                _list[k] -= intersect[i].S;
        }
        
        // for (int i = 0; i < m; i++) cout << intersect[i].S << ' ';
        // cout << endl;
        
        // devec(_list);
        dfs(1, k);
        
        cout << "Case Number  " << c++ << endl;
        cout << "Number of Customers: " << Rans << endl;
        cout << "Locations recommended:";
        for (int i = 1; i <= n; i++)
            if (Rlist[i]) cout << ' ' << i;
        cout << endl << endl;
    }
}