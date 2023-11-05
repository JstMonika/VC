#include "function.h"

void AddFront(Node** head, Node** back, int num) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    
    tmp->idx = num;
    tmp->next = (*head)->next;
    (*head)->next = tmp;
    
    if (*back == *head) {
        (*back) = (*head)->next;
    }
}

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

void Delete(Node** head, Node** back, int num) {
    Node* prev = (*head), *now = (*head)->next, *next;
    
    while (now != NULL) {
        next = now->next;
        
        if (now->idx == num) {
            prev->next = next;
            free(now);
            
            now = next;
        }
        else {
            prev = now;
            now = next;
        }
    }
    
    (*back) = prev;
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