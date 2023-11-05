#include <stdio.h>

int main()
{
    int c;
    scanf("%d", &c);
    
    while (c--)
    {
        int a[4], ans = 0, sum = 0, p;
        scanf("%d %d %d %d", &a[0], &a[1], &a[2], &p);
        
        while (sum < p)
        {
            if (ans < 3)
                sum += a[ans];
            else
            {
                a[3] = a[0] + a[2];
                sum += a[3];
                
                a[0] = a[1];
                a[1] = a[2];
                a[2] = a[3];
            }
            
            ans++;
        }
        
        printf("%d\n", ans);
    }
}