#include <stdio.h>

int main() {
    int n, r;
    scanf("%d %d", &n, &r);
    
    int arr[10][10000], idx[10] = {0};
    
    int now = 0, add = 1;
    for (int i = 1; i <= n; i++) {
        arr[now][idx[now]] = i;
        idx[now]++;
        
        if (add) {
            now++;
            
            if (now == r-1) add = 0;
        } else {
            now--;
            
            if (now == 0) add = 1;
        }
    }
    
    int first = 1;
    for (int i = 0; i < r; i++) {
        for (int k = 0; k < idx[i]; k++) {
            printf("%d", arr[i][k]);
            
            if (i == r-1 && k == idx[i]-1) printf("\n");
            else printf(" ");
        }
    }
}