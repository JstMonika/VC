#include <stdlib.h>

typedef struct node {
    int idx;
    struct node* next;
} Node;

void AddFront(Node** head, Node** back, int num);
void Delete(Node** head, Node** back, int num);
void DeleteRange(Node** head, Node** back, int from, int to);