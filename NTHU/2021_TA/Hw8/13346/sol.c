#include <stdio.h>

int w, h;
int idx = 0;
long long finalAns = 0;
char _DomoMaze[15][15];
long long cal[15][15];
int pW[3];
int pH[3];

long long DP(int sw, int sh, int fw, int fh)
{
    for (int i = sw; i <= fw; i++)
        for (int k = sh; k <= fh; k++)
            cal[i][k] = 0;
            
    _DomoMaze[fw][fh] = '0';  
    
    for (int i = sw; i <= fw; i++) if (_DomoMaze[i][sh] != '1') cal[i][sh] = 1;
    for (int i = sh; i <= fh; i++) if (_DomoMaze[sw][i] != '1') cal[sw][i] = 1;
    
    for (int i = sw+1; i <= fw; i++)
        for (int k = sh+1; k <= fh; k++)
            if (_DomoMaze[i][k] != '1')
                cal[i][k] = cal[i-1][k] + cal[i][k-1] + cal[i-1][k-1];
    
    return cal[fw][fh];
}

void solve()
{
    // 0 portal.
    finalAns += DP(0, 0, w-1, h-1);
    printf("%d\n", finalAns);
    int prev = finalAns;
    // 1 portal.
    for (int i = 0; i < idx; i++)
    {
        finalAns += DP(0, 0, pW[i], pH[i]) * DP(pW[i]-2, pH[i]-2, w-1, h-1);
        _DomoMaze[pW[i]][pH[i]] = '1';
    }
    printf("%d\n", finalAns - prev);
    
    prev = finalAns;
    
    if (idx == 2)
        for (int i = 0; i < 2; i++)
            if (pW[i]-2 <= pW[1-i] && pH[i]-2 <= pH[1-i])
            {
                finalAns += DP(0, 0, pW[i], pH[i]) * DP(pW[i]-2, pH[i]-2, pW[1-i], pH[1-i]) * DP(pW[1-i]-2, pH[1-i]-2, w-1, h-1);
                
                _DomoMaze[pW[0]][pH[0]] = '1';
                _DomoMaze[pW[1]][pH[1]] = '1';
            }
            
    printf("%lld\n", finalAns - prev);
}

int main()
{
    scanf("%d %d", &w, &h);
    
    for (int i = 0; i < w; i++)
        for (int k = 0; k < h; k++)
        {
            scanf(" %c", &_DomoMaze[i][k]);
            
            if (_DomoMaze[i][k] == '1')
            {
                pW[idx] = i;
                pH[idx] = k;
                
                idx++;
            }
        }
    
    solve();
}