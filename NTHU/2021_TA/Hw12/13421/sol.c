#include <stdio.h>
#include <string.h>
#include "function.h"

void AddBack(Node** head, Node** back, int num) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    
    tmp->idx = num;
    tmp->next = NULL;
    
    (*back)->next = tmp;
    (*back) = tmp;
}

void DeleteFront(Node** head, Node** back) {
    if ((*head)->next == NULL)
        return;
    
    Node* del = (*head)->next;
    (*head)->next = del->next;
    
    free(del);
    
    if ((*head)->next == NULL)
        *back = *head;
}

void Swap(Node** head, Node** back) {
    Node* prev = NULL, *now = (*head)->next, *next;
    
    if ((*head)->next != NULL)
        (*back) = (*head)->next;
    
    while (now != NULL) {
        next = now->next;
        now->next = prev;
        
        prev = now;
        now = next;
    }
    
    (*head)->next = prev;
}

int main()
{
    char str[50];
    
    Node* head = (Node*) malloc(sizeof(Node));
    Node* back = head;
    // initialize the dummy head
    
    // we'll append the element after this dummy head to avoid runtime error.
    head->idx = -1;
    head->next = NULL;
    
    while (scanf("%s", str) != EOF) {
        
        int num;
        
        if (!strcmp(str, "AddFront")) {
            scanf("%d", &num);
            AddFront(&head, &back, num);
        }
        else if (!strcmp(str, "AddBack")) {
            scanf("%d", &num);
            AddBack(&head, &back, num);
        }
        else if (!strcmp(str, "DeleteFront")) {
            DeleteFront(&head, &back);
        }
        else if (!strcmp(str, "Delete")) {
            scanf("%d", &num);
            Delete(&head, &back, num);
        }
        else if (!strcmp(str, "DeleteRange")) {
            int from, to;
            scanf("%d %d", &from, &to);
            DeleteRange(&head, &back, from, to);
        }
        else if (!strcmp(str, "Swap")) {
            Swap(&head, &back);
        }
        else if (!strcmp(str, "Print")) {
            Node* print = head;
         
            if (head->next == NULL) printf("empty\n");
            
            while (print != NULL) {
                if (print->idx != -1)
                    printf("%d%c", print->idx, (print->next == NULL ? '\n' : ' '));
                
                print = print->next;
            }
        }
    }
    
    // print all the element except the dummy head and free them.
    Node* print = head;
         
    while (print != NULL) {
        if (print->idx != -1)
            printf("%d%c", print->idx, (print->next == NULL ? '\n' : ' '));
        
        Node* del = print;
        print = print->next;
        free(del);
    }
}