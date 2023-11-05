#include <stdio.h>

int n, k, s;
int visit[1010];
int _map[1010][1010];

void go(int now) {
    if (visit[now]) return;
    
    visit[now] = 1;
    
    for (int i = 1; i <= n; i++) {
        if (_map[now][i])
            go(i);
    }
}

int main()
{    
    scanf("%d %d %d", &n, &k, &s);
    
    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        
        _map[a][b] = 1;
    }
    
    go(s);
    
    int first = 1;
    for (int i = 1; i <= n; i++) {
        if (visit[i]) {
            if (first) {
                first = 0;
                printf("%d", i);
            }
            else printf(" %d", i);
        }
    }
    
    printf("\n");
}