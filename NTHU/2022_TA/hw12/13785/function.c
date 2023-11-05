#include <stdio.h>
#include "function.h"

void Insert(Node** root, int src) {
    if (*root == NULL) {
        *root = (Node*) malloc(sizeof(Node));
        
        (*root)->val = src;
        return;
    } else {
        Node* now = *root;
        
        while (1) {
            if (src < now->val) {
                if (now->left == NULL) {
                    now->left = (Node*) malloc(sizeof(Node));
                    now->left->val = src;
                    
                    return;
                } else now = now->left;
            } else if (src > now->val) {
                if (now->right == NULL) {
                    now->right = (Node*) malloc(sizeof(Node));
                    now->right->val = src;
                    
                    return;
                } else now = now->right;
            } else return;
        }
    }
}

int first;
void print(Node* now) {
    if (now == NULL) return;
    
    if (first) {
        printf("%d", now->val);
        first = 0;
    } else printf(" %d", now->val);
    
    print(now->left);
    print(now->right);
}

void Print(Node* root) {
    first = 1;
    print(root);
    printf("\n");
}