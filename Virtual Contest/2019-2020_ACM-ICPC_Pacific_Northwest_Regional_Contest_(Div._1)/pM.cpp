#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> using vec = vector<T>;
template <typename T> using deq = deque<T>;
template <typename T> using p = pair<T, T>;

#define endl '\n'
#define F first
#define S second
#define eb emplace_back
#define al(a) a.begin(),a.end()
#define yccc ios_base::sync_with_stdio(false),cin.tie(0)

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (abs(a-b) < eps) return 0;
    return a-b;
}

const double PI = acos(-1);

int cont = 0;
map<p<int>, int> _map;

int siz;
vec<int> pset, setSize;
void initSet(int n) {
    pset.resize(n);
    setSize.resize(n);
    for (int i = 0; i < n; i++) {
        pset[i] = i;
        setSize[i] = 1;
    }
    
    siz = n;
}

int findSet(int i) {
    return (pset[i] == i) ? i : pset[i] = findSet(pset[i]);
}

void unionSet(int i, int k) {
    if (findSet(i) != findSet(k)) {
        if (setSize[findSet(i)] < setSize[findSet(k)]) {
            pset[findSet(i)] = findSet(k);
            setSize[findSet(k)] += setSize[findSet(i)];
        } else {
            pset[findSet(k)] = findSet(i);
            setSize[findSet(i)] += setSize[findSet(k)];
        }
        
        siz--;
    }
}

int n, m;

void check(p<int>& src) {
    if (src.F < 0 or src.F >= 2*n-1) {
        src = make_pair(-1, -1);
        return;
    }
    
    if (src.S < 0 or src.S >= 2*m-1) {
        src = make_pair(-1, -1);
        return;
    }
    
    return;
}

void link(p<int> a, p<int> b) {
    // cout << a.F << ' ' << a.S << " and " << b.F << ' ' << b.S << endl;
    check(a);
    check(b);
    // cout << a.F << ' ' << a.S << " and " << b.F << ' ' << b.S << endl;
    
    int idxA, idxB;
    if (_map.find(a) != _map.end()) idxA = _map[a];
    else {
        // cout << "???\n";
        idxA = _map[a] = cont++;
    }
    
    if (_map.find(b) != _map.end()) idxB = _map[b];
    else {
        // cout << "???\n";
        idxB = _map[b] = cont++;
    }
    
    // cout << idxA << ' ' << idxB << ' ' << cont << endl;
    
    unionSet(idxA, idxB);
}

int main() {
    yccc;
    
    cin >> n >> m;
    
    vec<vec<char>> _list(n, vec<char>(m));
    vec<p<int>> dot;
    int first_slash = -1;
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            cin >> _list[i][k];
            
            if (_list[i][k] != '.') {
                first_slash = (_list[i][k] == '/') ? ((i + k) % 2 == 0) : ((i + k) % 2 == 1);
            } else {
                dot.emplace_back(i, k);
            }
        }
    }
    
    if (first_slash == -1) {
        cout << 0 << endl;
        return 0;
    }
    
    ll num = (first_slash ? (n/2) * (m/2) + ((n-1) / 2) * ((m-1) / 2) : ((n-1) / 2) * (m / 2) + ((m-1) / 2) * (n / 2));
    
    // cout << num << endl;
    
    initSet(num+1);
    for (auto i : dot) {
        // cout << "dot: " << i.F << ' ' << i.S << endl;
        auto tr = make_pair(i.F*2-1, i.S*2+1);
        auto tl = make_pair(i.F*2-1, i.S*2-1);
        auto br = make_pair(i.F*2+1, i.S*2+1);
        auto bl = make_pair(i.F*2+1, i.S*2-1);
        
        if (first_slash == 1) {
            if ((i.F + i.S) % 2) { //* tr and bl
                link(tr, bl);
            } else {
                link(tl, br);
            }
        } else {
            if ((i.F + i.S) % 2) {
                link(tl, br);
            } else {
                link(tr, bl);
            }
        }
    }
    
    cout << siz-1 << endl;
}