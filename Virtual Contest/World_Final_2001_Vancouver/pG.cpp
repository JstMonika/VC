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

vec<vec<pii>> G;
pair<bool, vec<int>> bellmanford(int s, int e) {
    vec<int> parent(e+1), cost(e+1, INF), exist(e+1);
    
    exist[s] = 1;
    parent[s] = s;
    cost[s] = 0;
    
    queue<int> que;
    que.emplace(s);
    
    while (!que.empty()) {
        auto now = que.front();
        que.pop();
        exist[now] = 0;
        
        for (int i = 0; i <= e; i++) {
            if (G[now][i].S and cost[now] + G[now][i].F < cost[i]) {
                parent[i] = now;
                cost[i] = cost[now] + G[now][i].F;
                
                if (!exist[i])
                    que.emplace(i);
            }
        }
    }
    // devec(cost);
    // devec(parent);
    
    if (cost[e] == INF)
        return make_pair(false, vec<int>());
    
    vec<int> path;
    path.eb(e);
    while (path.back() != s) {
        path.eb(parent[path.back()]);
    }
    
    reverse(al(path));
    // devec(path);
    
    return make_pair(true, path);
}

int main()
{
    yccc;
    
    int machine, task, c = 1;
    while (cin >> machine >> task) {
        if (!machine) break;
        
        int count = task;
        vec<vec<int>> idx(machine, vec<int>(task));
        for (int i = 0; i < machine; i++)
            for (int k = 0; k < task; k++)
                idx[i][k] = count++;
        
        int s = count++, e = count++;
        
        G.clear();
        G.resize(count);
        for (auto &i : G)
            i.resize(count);
        
        vec<vec<int>> time(task, vec<int>(machine, INF));
        
        vec<int> mem(machine);
        for (auto &i : mem)
            cin >> i;
        
        vec<vec<int>> need_time(task, vec<int>(machine, INF));
        for (int i = 0; i < task; i++) {
            int tmp;
            cin >> tmp;
            
            vec<pii> st(tmp);
            for (auto &k : st)
                cin >> k.F >> k.S;
            
            for (int k = 0; k < machine; k++) {
                if (st[0].F > mem[k])
                    continue;
                    
                for (int j = tmp-1; j >= 0; j--) {
                    if (st[j].F <= mem[k]) {
                        need_time[i][k] = st[j].S;
                        break;
                    }
                }
            }
        }
        
        for (int i = 0; i < machine; i++) {
            for (int k = 0; k < task; k++) {
                if (need_time[k][i] == INF)
                    continue;
                    
                for (int j = 0; j < task; j++) {
                    G[k][idx[i][j]] = make_pair(need_time[k][i] * (task-j), 1);
                    G[idx[i][j]][k] = make_pair(-need_time[k][i] * (task-j), 0);
                    // cout << k << ' ' << idx[i][j] << ' ' << need_time[k][i] * (j+1) << endl;
                }
                
                G[s][k] = make_pair(0, 1);
                // cout << s << ' ' << k << endl;
            }
        }
        
        for (int i = 0; i < machine; i++)
            for (int k = 0; k < task; k++) {
                G[idx[i][k]][e] = make_pair(0, 1);
                // cout << idx[i][k] << ' ' << e << endl;
            }
        
        while (true) {
            vec<int> path;
            bool good;
            // cout << "--\n";
            tie(good, path) = bellmanford(s, e);
            
            if (!good) break;
            
            for (int i = 0; i < path.size()-1; i++) {
                G[path[i]][path[i+1]].S = 0;
                G[path[i+1]][path[i]].S = 1;
            }
        }
        
        vec<vec<int>> task_list(machine);
        vec<pair<int, pair<int, int>>> ans(task);
        double aver = 0;
        
        for (int i = 0; i < machine; i++) {
            int sum = 0;
            for (int k = 0; k < task; k++) {
                for (int j = 0; j < task; j++) {
                    if (G[idx[i][k]][j].S == 1) {
                        task_list[i].eb(j+1);
                        ans[j] = make_pair(i+1, make_pair(sum, sum + G[idx[i][k]][j].F * -1 / (task-k)));
                        aver += sum + G[idx[i][k]][j].F * -1 / (task-k);
                        sum += G[idx[i][k]][j].F * -1 / (task-k);
                        // cout << "task " << j+1 << " at machine " << i << " and used " << G[idx[i][k]][j].F*-1 << " units.\n";
                    }
                }
            }
            
            // reverse(al(task_list[i]));
        }
        cout << "Case " << c++ << endl;
        cout << "Average turnaround time = " << fixed << setprecision(2) << aver / task << endl;
        
        for (int i = 0; i < ans.size(); i++) {
            cout << "Program " << i+1 << " runs in region " << ans[i].F << " from " << ans[i].S.F << " to " << ans[i].S.S << endl;
        }
        
        cout << endl;
        // devec2(task_list);
    }
}