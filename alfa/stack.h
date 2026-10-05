#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

typedef struct Stack Stack;

Stack* stack_create(int capacity);

void stack_push(Stack *s, void *value);

int stack_size(Stack *s);

bool stack_is_empty(Stack *s);

void *stack_peek(Stack *s);

void *stack_pop(Stack *s);

void stack_free(Stack *s);


#endif
