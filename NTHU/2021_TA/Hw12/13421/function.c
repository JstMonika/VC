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

void DeleteRange(Node** head, Node** back, int from, int to) {
    from--;
    to--;
    
    if (from < 0)
        return;
    
    Node* db = (*head), *df = (*head);
    
    for (int i = 0; i < from; i++) {
        db = db->next;
        df = db;
        
        if (db == NULL)
            return;
    }
    
    for (int i = from; i < to+2; i++) {
        if (df == NULL)
            return;
            
        df = df->next;
    }
    
    Node* tmp = db->next;
    
    while (tmp != df) {
        Node* del = tmp;
        
        tmp = tmp->next;
        free(del);
    }
    
    db->next = df;
    
    if (df == NULL)
        (*back) = db;
}