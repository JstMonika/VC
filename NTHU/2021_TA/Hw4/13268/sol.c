#include <stdio.h>

int main()
{
    int N, L;
    scanf("%d %d", &N, &L);
    
    int _list[1010];
    for (int i = 0; i < N; i++)
        scanf("%d", &_list[i]);
    
    int domo = 1;
    
    for (int i = 0; i < N - L + 1; i++)
    {
        //* index -> i ~ i+L-1
        
        int good = 1;
        
        for (int k = i+1; k < i+L-1; k++)
            if (_list[k] <= _list[i] || _list[k] <= _list[i+L-1])
                good = 0;
        
        if (good)
        {
            domo = 0;
            printf("%d", _list[i]);
            
            for (int k = i+1; k <= i+L-1; k++)
                printf(" %d", _list[k]);
            
            printf("\n");
        }
    }
    
    if (domo)
        printf("Domo\n");
}