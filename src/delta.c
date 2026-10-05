#include <stdlib.h>
#include <stdio.h>

#include "../alfa/epsilon.h"
#include "../alfa/delta.h"

typedef struct Node {
    void *data;
    struct Node *next;
   struct  Node *prev;
}Node;


struct LinkedList {
    Node *head;
    Node *tail;
    int size;
};

//PS add a macro so they can easly cast

typedef LinkedList ll;

LinkedList *LinkedList_create(){
    ll *list = malloc(sizeof(LinkedList));
    *list = (ll){
        .head = NULL,
        .tail = NULL,
        .size = 0,
    };
    return list;
}

void LinkedList_push(ll *list ,void *value){
    if(list == NULL) return;
    
    Node *node_alloc = list->head;
    Node *nn = malloc(sizeof(Node));

    if(list->head == NULL){
        list->head = nn;
        list->tail = nn;
    }else{
        list->tail->next = nn;
        nn->prev = list->tail;
        list->tail = nn;
    }
    list->size++;
}

void *LinkedList_pop(ll *list){
    if(list == NULL || list->size <= 0) return NULL;
    Node *pop = list->tail;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    list->size--;
    return pop;
}

void LinkedList_insert(ll *list, size_t pos, void *value){
    if(list = NULL || list->size <=0) return NULL;
    Node *current = list->head;
    while(current != NULL && pos){
        current = current->next;
        offset--;
    }
    Node *nd  = malloc(sizeof(*nd));
    *nd = malloc(sizeof(*nd));
    *nd = (Node){
        .data = value,
        .next = current->next,
        .prev = current,
    };
    if(offset >= list->size) 
}



void node_insert(Node *head, size_t offset, void *value){
    if(head == NULL || offset < 0) return;
    while(head->next != NULL && offset){ 
        head = head->next;
        offset--;
    }
    Node *nd = malloc(sizeof(*nd));
    *nd = (Node){
        .data = value,
        .next = head->next,
        .prev = head,
    };
    head->next = nd;
}

Node node_pop(Node **head){
    Node nd;
    if(head == NULL ||*head == NULL) return nd;
    while((*head)->next != NULL) *head = (*head)->next;
    nd = **head;
    if((*head)->prev == NULL) {
        free(*head);
        *head = NULL;
    }else{
        ((*head)->prev)->next = NULL;
        free(*head);
    }
    return nd;
}
//change to pointer to data as idk it makes more sense to want the data not the Node
Node node_pop_front(Node **head){
    Node nd;
    if(head == NULL || *head == NULL) return nd;
    while((*head)->prev != NULL) *head = (*head)->prev;
    nd = **head;
    if((*head)->next == NULL){
        free(*head);
        *head = NULL;
    }else{
        *head = (*head)->next;
        free((*head)->prev);
        (*head)->prev = NULL;
    }
    return nd;
}

//also i didnt add a destructor so scheize
//maybe add negative offset mode so it goes back it would be interesting 
void node_remove(Node **head, size_t offset){
    if(head == NULL || *head == NULL || offset < 0) return;

    Node *current = *head;
    


    while((*head)->next != NULL && offset) *head = (*head)->next;
}



