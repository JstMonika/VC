#include <stdio.h>

int main()
{
    int c;
    scanf("%d", &c);
    
    while (c--)
    {
        int a[110], ans = 1, sum = 0, p;
        scanf("%d %d %d %d", &a[1], &a[2], &a[3], &p);
        
        while (1)
        {
            if (ans > 3)
                a[ans] = a[ans-1] + a[ans-3];
                
            sum += a[ans];
            
            if (sum >= p)
                break;
            
            ans++;
        }
        
        printf("%d\n", ans);
    }
}