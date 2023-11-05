#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
// #define endl '\n'
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

int main() {
    yccc;

    int n, des, r, j, c = 1;
    while (cin >> n) {
        if (n == -1)
            break;

        vec<vec<int>> edge(n+1, vec<int>(n+1, INF));

        cin >> des >> r;
        for (int i = 0; i < r; i++) {
            int s, e;
            cin >> s >> e;
            s--, e--;
            cin >> edge[s][e];
            edge[e][s] = edge[s][e];
        }

        cin >> j;
        vec<int> j_set(j);
        set<int> need;
        for (int i = 0; i < j; i++) {
            cin >> j_set[i];
            j_set[i]--;

            need.emplace(j_set[i]);
        }
        des--;
        need.emplace(des);

        auto it = need.begin();
        int idx = 0;

        map<int, int> to;
        for (int i = 0; i < n - need.size(); i++) {
            while (*it == idx) {
                idx++;
                it++;
            }

            to[i] = idx;
            idx++;   
        }
        
        bitset<25> per;
        int count = 0;
        
        deque<bool> mir(n);
        for (auto i : need)
            mir[i] = true;

        int ans_dis = INF, num_citys = INF;
        vec<int> ans_parent;

        do {
            bitset<25> per(count);
            int tmp_ans = 0;

            int l_cont = need.size();
            auto _list = mir;
            for (int i = 0; i < n - need.size(); i++) {

                _list[to[i]] =  per[i];
                l_cont++;
            }

            //* check.
            deq<bool> vis(n);
            vec<int> parent(n);
            vis[des] = true, parent[des] = -1;

            auto cmp = [&edge](p<int> a, p<int> b) { return edge[a.F][a.S] > edge[b.F][b.S]; };
            priority_queue<p<int>, vec<p<int>>, decltype(cmp)> pq(cmp);
            
            for (int i = 0; i < n; i++)
                if (edge[des][i] != INF) pq.emplace(i, des);
            
            int total = 1;
            while (!pq.empty()) {
                auto now = pq.top();
                pq.pop();

                if (!_list[now.F]) continue;
                if (vis[now.F]) continue;

                vis[now.F] = true, parent[now.F] = now.S;
                tmp_ans += edge[now.F][now.S];
                
                for (int i = 0; i < n; i++) {
                    if (edge[now.F][i] != INF and !vis[i]) pq.emplace(i, now.F);
                }

                total++;
            }

            if (total == l_cont) {
                if (tmp_ans < ans_dis or (tmp_ans == ans_dis and total < num_citys)) {
                    ans_dis = tmp_ans;
                    num_citys = total;

                    ans_parent = parent;
                }
            }

        } while (++count < (1<<(n-need.size())));

        cout << "Case " << c++ << ": distance = " << ans_dis << endl;

        for (int i = 0; i < j_set.size(); i++) {
            cout << "   ";

            int now = j_set[i];
            while (now != des) {
                cout << now+1 << '-';

                now = ans_parent[now];
            }
            cout << des+1 << endl;
        }

        cout << endl;
    }
}