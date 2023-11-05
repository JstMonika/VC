#include <stdio.h>

int main()
{
    int L, R;
    scanf("%d%d", &L, &R);
    
    int ans = -1;
    int ansCount = 0;
    
    //* find prime
    int flag[101] = {0};
    int primeList[100];
    int primeCount = 0;
    
    for (int i = 2; i <= R; i++)
    {
        if (flag[i] == 0)  //* is prime
        {
            primeList[primeCount] = i;
            primeCount++;
            
            for (int k = i*i; k <= R; k += i)
                flag[k] = 1;
        }
    }
    
    for (int i = L; i <= R; i++)
    {
        int tmp = i;
        int factorCount = 1;
		
        
        for (int k = 0; k < primeCount; k++)
        {
			int count = 0;
			while (tmp % primeList[k] == 0)
			{
				count++;
				tmp /= primeList[k];
			}
			
			factorCount *= (count + 1);
        }
		
		if (factorCount >= ansCount)
		{
			ans = i;
			ansCount = factorCount;
		}
    }
	
	printf("%d", ans);
}