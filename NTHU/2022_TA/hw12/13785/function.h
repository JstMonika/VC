#include <stdlib.h>

typedef struct node {
    int val;
    struct node *left, *right;
} Node;

void Insert(Node** root, int src);
void Print(Node* root);