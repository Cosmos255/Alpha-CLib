#include <stdlib.h>
#include <stdio.h>

#include "../alfa/epsilon.h"

//no stack var everythign including the list should be on heap

typedef struct Node {
    void *data;
    //struct Node *tail;
    struct Node *next;
    struct Node *prev;
}Node;

void node_push(Node **head, void *value){
    if(head == NULL) return;
    Node *current = (*head == NULL) ? NULL : *head;
    if(current != NULL) 
        while(current->next != NULL) current = current->next;

    Node *nd = malloc(sizeof(*nd));
    *nd = (Node){
        .data = value,
        .next = NULL,
        .prev = current,
    };
    if(current == NULL) *head = nd;
    else current->next = nd;
}

void node_push_front(Node **head, void *value){
    if(head == NULL) return;
    Node *current = (*head == NULL) ? NULL : *head;
    if(current != NULL) 
        while(current->prev != NULL) current = current->prev;

    Node *nd = malloc(sizeof(*nd));
    *nd = (Node){
        .data = value,
        .next = current,
        .prev = NULL,
    };
    if(current != NULL) current->prev = nd;
    *head = nd;
}


void node_insert_back(Node **head, void *value){
    if(head == NULL) return;
    if(*head == NULL) node_push_front(head, value);
    else if((*head)->next == NULL) node_push(head, value);
    else{
        Node *nd = malloc(sizeof(*nd));
        *nd = (Node){
            .data = value,
            .next = (*head)->next,
            .prev = *head,
        };
        (*head)->next->prev = nd;
        (*head)->next = nd;
    }
}



void node_inset_front(Node **head, void *value){
    if(head == NULL) return;
    if(*head == NULL) node_push_front(head, value);
    else if((*head)->next == NULL) node_push(head, value);
    else{
        Node *nd = malloc(sizeof(*nd));
        *nd = (Node){
            .data = value,
            .next = *head,
            .prev = (*head)->prev,
        };
        (*head)->prev->next = nd;
        (*head)->prev = nd;
    }
}

void *node_remove(Node **node){
    if(*node == NULL) return NULL;
    void *result = (*node)->data;
    
    Node *prev = (*node)->prev;
    Node *next = (*node)->next;

    free(*node);
    if(prev == NULL && next == NULL) *node = NULL;
    if(prev != NULL && next != NULL) {
        *node = prev;
        prev->next = next;
        next->prev = prev;
    }else{
        *node = (prev == NULL) ? next : prev;
        if(next != NULL) next->prev = prev;
        if(prev != NULL) prev->next = next; 
    }
    return result;
}

void *node_pop(Node **head){
    if(head == NULL || *head == NULL) return NULL;
    Node *current = *head;
    while(current->next != NULL) current = current->next;

    void  *result = node_remove(&current);
    
    if(current == NULL) *head = NULL;
    else{
        if(current->prev == NULL) *head = current;
    }
    return result;
}

void *node_pop_front(Node **head){
    if(head == NULL || *head == NULL) return NULL;
    Node *current = *head;
    while(current->prev != NULL) current = current->prev;

    void  *result = node_remove(&current);
    *head = current;
    return result;
}


//also i didnt add a destructor so scheize
//maybe add negative offset mode so it goes back it would be interesting 



