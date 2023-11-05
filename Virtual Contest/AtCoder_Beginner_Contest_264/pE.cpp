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

    vec<int> pset, sum, setSize;
    int ans;
    int n, m;

    void initSet(int s) {
        pset.resize(s);
        sum.resize(s);
        setSize.resize(s);
        for (int i = 0; i < s; i++) {
            pset[i] = i;
            sum[i] = (i >= n);
            setSize[i] = 1;
        }
    }

    int findSet(int i) {
        return (pset[i] != i ? pset[i] = findSet(pset[i]) : i);
    }

    void unionSet(int i, int k) {
        if (findSet(i) != findSet(k)) {
            if (sum[findSet(i)] and !sum[findSet(k)]) {
                ans += setSize[findSet(k)];
            } else if (!sum[findSet(i)] and sum[findSet(k)]) {
                ans += setSize[findSet(i)];
            }
            
            sum[findSet(i)] += sum[findSet(k)];
            setSize[findSet(i)] += setSize[findSet(k)];
            pset[findSet(k)] = findSet(i);
        }   
    }

    int main()
    {
        yccc;
        
        int e;
        cin >> n >> m >> e;
        
        vec<p<int>> E(e);
        for (auto &i : E) {
            cin >> i.F >> i.S;
            i.F--, i.S--;
        }
        
        int q;
        cin >> q;
        vec<int> query(q);
        for (auto &i : query) {
            cin >> i;
            i--;
        }
        
        ans = m;
        reverse(al(query));
        
        initSet(n+m);
        
        auto tmp = query;
        sort(al(tmp));
        
        deque<bool> use(E.size());
        for (auto i : query)
            use[i] = true;
        
        for (int i = 0; i < E.size(); i++)
            if (!use[i]) unionSet(E[i].F, E[i].S);
            
        // int idx = 0, now = 0;
        // while (idx < tmp.size()) {
        //     for (int i = now; i < tmp[idx]; i++) {
        //         unionSet(E[i].F, E[i].S);
        //     }
            
        //     now = tmp[idx]+1;
        //     idx++;
        // }
        
        vec<int> pans;
        for (auto i : query) {
            pans.eb(ans - m);
            unionSet(E[i].F, E[i].S);
        }
        
        reverse(al(pans));
        for (auto i : pans)
            cout << i << endl;
    }