#include "../alfa/stack.h"
#include "../alfa/gamma.h"
#include <stdio.h>
#include <stdbool.h>

struct Stack {
    void **data;
    int size;
    int capacity;
    void (*destructor)(void *);
};

Stack* stack_create(int capacity){
    Stack *s = malloc(sizeof(Stack));
    s->capacity = capacity;
    s->size = 0;
    s->data = malloc(sizeof(void*)*capacity);
    return s;
}

void stack_push(Stack *s, void *value){
    if(s == NULL) return;
    gamma_push(s, value);
}

int stack_size(Stack *s){
    if(s == NULL) return -1; 
    return s->size; 
}

bool stack_is_empty(Stack *s){
    if(s == NULL) return false;
    return (s->size == 0);
}

void *stack_peek(Stack *s){
    if(s == NULL || s->size == 0 || s->data == NULL) return NULL;
    return s->data[(s->size-1)];
}

void *stack_pop(Stack *s){
    if(s == NULL || s->size == 0 || s->data == NULL) return NULL;
    return s->data[--s->size];
}

void stack_free(Stack *s){
    while(s->size--){
        free(s->data[s->size]);
    }
    free(s->data);
    s->data = NULL;
}


