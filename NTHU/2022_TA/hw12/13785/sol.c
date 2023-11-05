#include <stdio.h>
#include <string.h>
#include "function.h"

int main() {
    
    char str[50];
    
    Node* root = NULL;
    
    while (scanf("%s", str) != EOF) {
        if (!strcmp(str, "Insert")) {
            int num;
            scanf("%d", &num);
            
            Insert(&root, num);
        } else if (!strcmp(str, "Print")){
            Print(root);
        }
    }
}