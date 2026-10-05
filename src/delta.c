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
    
    void *data = pop->data;
    free(pop);
    return data;
}

void *LinkedList_pop_front(ll *list){
    if(list == NULL || list->size <= 0)return NULL;
    Node *pop = list->head;
    list->head = list->head->next;
    (list->head == NULL) ? (list->tail = NULL) : (list->head->prev = NULL);
    list->size--;

    void *data = pop->data;
    free(pop);
    return data;
}


void *LinkedList_front(ll *list){
    if(list == NULL) return NULL;
    return list->head->data; 
}

void *LinkedList_back(ll *list){
    if(list == NULL) return NULL;
    return list->tail->data; 
}


void *LinkedList_at(ll *list, int pos){
    if(list == NULL || list->size<=0) return NULL;
    if(pos >= list->size){
        fprintf(stderr, "Linked list: Index out of bounds at {%d} where list size {%d}\n", pos, list->size);
        exit(1);       
    }
    if(pos == list->size-1) return list->head->data;
    Node *current = list->head;
    while(current->next != NULL && pos){
        current = current->next;
    }
    return current->data;
}

void LinkedList_insert(ll *list, size_t pos, void *value){
    if(list == NULL || list->size <=0) return;
    Node *current = list->head;
    if(pos >= list->size){
        LinkedList_push(list, value);
        return;
    }
    while(current->next != NULL && pos){
        current = current->next;
        pos--;
    }
    Node *nd  = malloc(sizeof(*nd));
    nd = malloc(sizeof(*nd));
    *nd = (Node){
        .data = value,
        .next = current,
        .prev = current->prev,
    };
    (nd->prev == NULL) ? (list->head = nd) : (nd->prev->next = nd);
    (nd->next == NULL) ? (list->tail = nd) : (nd->next->prev = nd);
    list->size++;
}


