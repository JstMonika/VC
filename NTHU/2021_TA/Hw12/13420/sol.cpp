#include <stdio.h>

int n, k;
int visit[100];
int _map[100][100];

void dfs(int now) {
    visit[now] = 1;
    
    for (int i = 0; i < n; i++) {
        if (_map[now][i] && !visit[i])
            dfs(i);
    }
}

int main() { 
   
    scanf("%d %d", &n, &k);
    
    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        
        _map[a][b] = _map[b][a] = 1;
    }
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!visit[i]) {
            count++;
            
            dfs(i);
        }
    }
    
    printf("%d\n", count-1);
}