#include <stdio.h>

int n, x, d, cont;
int _list[1010], ans[1010];
int G[1001][1001];

int _abs(int a) {
    return (a < 0 ? -a : a);
}

int go(int now, int prev) {
    int sum = 0;
    
    for (int i = 1; i <= n; i++) {
        if (prev != i && G[now][i]) {
            sum += go(i, now);
        }
    }
    
    sum += _list[now-1];
    
    if (_abs(sum - x) < d) ans[cont++] = now;
    
    // cout << now << ": " << sum << endl;
    
    return sum;
}

int main()
{
    scanf("%d %d %d", &n, &x, &d);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &_list[i]);
    }
    
    for (int i = 0; i < n-1; i++) {
        int s, e;
        scanf("%d %d", &s, &e);
        
        G[s][e] = G[e][s] = 1;
    }
    
    go(1, -1);
    
    for (int i = 0; i < cont; i++) {
        for(int k = 0; k < cont-1; k++) {
            if (ans[k] > ans[k+1]) {
                int tmp = ans[k];
                ans[k] = ans[k+1];
                ans[k+1] = tmp;
            }
        }
    }
    
    for (int i = 0; i < cont; i++) {
        printf("%d%c", ans[i], " \n"[i == cont-1]);
    }
}