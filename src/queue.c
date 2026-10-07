#include "../alfa/delta.h"
#include "../alfa/queue.h"
#include <stdlib.h>
#include <stdbool.h>

struct Queue{
    LinkedList *list;
};

Queue *queue_create(){
    Queue *q = malloc(sizeof(Queue));
    q->list = LinkedList_create();
    return q;
}

void enqueue(Queue *q, void *data){
    LinkedList_push(q->list, data);
}

void *dequeue(Queue *q){
    return LinkedList_pop_front(q->list);
}

void *queue_front(Queue *q){
    return LinkedList_front(q->list);
}

void *queue_back(Queue *q){
    return LinkedList_back(q->list);
}

int queue_size(Queue *q){
    return LinkedList_size(q->list);
}

bool queue_isempty(Queue *q){
    return queue_size(q) <= 0;
}

