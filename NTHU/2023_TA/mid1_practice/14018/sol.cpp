#include <stdio.h>
#include <string.h>

int isdigit(char ch) {
    return ch >= '0' && ch <= '9';
}

int isalpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int main() {
    char str[1001], ans[1000000];
    
    while (scanf("%s", str) != EOF) {
        int len = strlen(str);
        int now = 0;
        
        int good = 1;
        for (int i = 0; i < len;) {
            if (!isdigit(str[i])) {
                good = 0;
                break;
            } else {
                int sum = 0;
                
                while (i < len && isdigit(str[i])) {
                    sum *= 10;
                    sum += (str[i] - '0');
                    
                    i++;
                }
                
                if (sum == 0) {
                    good = 0;
                    break;
                }
                
                if (i >= len) {
                    good = 0;
                    break;
                } else if (str[i] == '\'') {
                    if (i+2 >= len) {
                        good = 0;
                        break;
                    } else if (!(isdigit(str[i+1]) && str[i+2] == '\'')) {
                        good = 0;
                        break;
                    } else {
                        for (int z = 0; z < sum; z++) {
                            ans[now++] = str[i+1];
                        }
                        i += 3;
                    }
                } else if (isalpha(str[i])) {
                    for (int z = 0; z < sum; z++)
                        ans[now++] = str[i];
                    i++;
                } else {
                    good = 0;
                    break;
                }
            }
        }
        
        if (!good) {
            printf("Domo cannot crack this computer\n");
        } else {
            ans[now++] = 0;
            printf("%s\n", ans);
        }
    }
}