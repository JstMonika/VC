#include <stdio.h>
#include <string.h>

long long ans;

int len;
char str[26], origin[26], exist[26];
char tmp[26];

int find(int now)
{
    if (len == now)
    {
        if (strcmp(origin, tmp) == 0)
            return 1;
        else
        {
            ans++;
            return 0;
        }   
    }
    
    for (int i = 0; i < len; i++)
    {
        if (exist[i] == 0)
        {
            tmp[now] = str[i];
            exist[i] = 1;
            
            if (find(now+1))
                return 1;
                
            exist[i] = 0;
        }
    }
    
    return 0;
}

int main()
{
    int t;
    scanf("%d", &t);
    
    while (t--)
    {
        ans = 0;
        for (int i = 0; i < 26; i++) exist[i] = tmp[i] = 0;
        
        scanf("%s", str);
        strcpy(origin, str);
        
        len = strlen(str);
        for (int i = 0; i < len; i++)
            for (int k = i+1; k < len; k++)
                if (str[i] > str[k])
                {
                    char ch = str[i];
                    str[i] = str[k];
                    str[k] = ch;
                }
        
        find(0);
        
        printf("%lld\n", ans);
    }
}