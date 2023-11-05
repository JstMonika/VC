#include <stdio.h>

int main()
{
    int len;
    scanf("%d", &len);
    getchar();
    
    int A[102];
    for (int i = 0; i < 102; i++) A[i] = 0;
    
    for (int i = len-1; i >= 0; i--)
        A[i] = getchar() - '0';
    
    int B;
    scanf("%d", &B);
    
    for (int i = 0; i < len; i++)
        A[i] *= B;
        
    for (int i = 0; i < 101; i++)
        if (A[i] >= 10)
        {
            A[i+1] += A[i] / 10;
            A[i] %= 10;
        }
    
    int first = 1;
    for (int i = 101; i >= 0; i--)
    {
        if (first && A[i] == 0)
            continue;
        else
        {
            printf("%d", A[i]);
            first = 0;
        }
    }
    
}