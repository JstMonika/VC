// EK 1825ms
#include <cstdio>
#include <cstring>
#include <iostream>
#define m(s) memset(s, 0, sizeof s);
#define EF                                                                     \
    if (ch == EOF) return x;
using namespace std;
const int N = 100;
const int M = N * N << 2;
struct edge {
    int st, v, next, cap, cost;
} e[M];

int tot = 1, head[N];
int n, cas, A, B, ans, S, T, rd[N], cd[N], dis[N], pre[N], q[N + M];
bool vis[N];
int sum, hav, maxflow, maxcost;
char s[N][N];

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        EF;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

void add(int x, int y, int z, int cost = 0) {
    e[++tot].v = y;
    e[tot].st = x;
    e[tot].cap = z;
    e[tot].cost = cost;
    e[tot].next = head[x];
    head[x] = tot;
    e[++tot].v = x;
    e[tot].st = y;
    e[tot].cap = 0;
    e[tot].cost = -cost;
    e[tot].next = head[y];
    head[y] = tot;
}

bool spfa() {
    memset(vis, 0, sizeof vis);
    memset(dis, 0x3f, sizeof dis);
    unsigned short h = 0, t = 1;
    q[t] = S;
    dis[S] = 0;
    vis[S] = 1;
    while (h != t) {
        int x = q[++h];
        vis[x] = 0;
        for (int i = head[x]; i; i = e[i].next) {
            if (e[i].cap && dis[e[i].v] > dis[x] + e[i].cost) {
                dis[e[i].v] = dis[x] + e[i].cost;
                pre[e[i].v] = i;
                if (!vis[e[i].v]) {
                    vis[e[i].v] = 1;
                    q[++t] = e[i].v;
                }
            }
        }
    }
    return dis[T] < 0x3f3f3f3f;
}

void augment() {
    int flow = 0x3f3f3f3f;
    for (int i = T; i != S; i = e[pre[i] ^ 1].v)
        flow = min(flow, e[pre[i]].cap);
    for (int i = T; i != S; i = e[pre[i] ^ 1].v) {
        e[pre[i]].cap -= flow;
        e[pre[i] ^ 1].cap += flow;
    }
    maxflow += flow;
    maxcost += dis[T] * flow;
}

int main() {
    while (1) {
        n = read();
        A = read();
        B = read();
        
        if (!n) return 0;
        
        
        printf("Case %d: ", ++cas);
        
        
        S = 0, T = n << 1 | 1;
        sum = 0;
        hav = 0;
        ans = -1;
        
        m(rd);
        m(cd);
        
        for (int i = 1; i <= n; i++) {
            scanf("%s", s[i] + 1);
            for (int j = 1; j <= n; j++) {
                if (s[i][j] == 'C' || s[i][j] == '.') {
                    sum++;
                    cd[i]++, rd[j]++;
                    if (s[i][j] == 'C') hav++;
                }
            }
        }
        for (int maxt = 0; maxt <= n; maxt++) {
            tot = 1;
            m(head);
            for (int i = 1; i <= n; i++) {
                add(S, i, cd[i]);
                add(i, i + n, maxt);
                add(i + n, T, rd[i]);
                for (int j = 1; j <= n; j++) {
                    if (s[i][j] == '.') add(i, j + n, 1, 1);
                }
            }
            
            // if (maxt == 2) {
            //     for (int i = 2; i <= tot; i+=2) {
            //         printf("%d %d %d %d\n", e[i].st, e[i].v, e[i].cap, e[i].cost);
            //     }
            // }
            
            maxflow = maxcost = 0;
            while (spfa())
                augment();
                for (int i = 2; i <= tot; i++) {
                    printf("%d %d %d %d\n", e[i].st, e[i].v, e[i].cap, e[i].cost);
                }
                printf("===\n");
            printf("%d %d\n", maxflow, sum);
            if (maxflow == sum && (maxflow - maxcost) * A >= maxt * B) {
                printf(": %d %d\n", maxflow, maxcost);
                ans = max(ans, maxflow - maxcost);
                
            }
        }
        if (~ans)
            printf("%d\n", ans - hav);
        else
            puts("impossible");
    }
    return 0;
}
