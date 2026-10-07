#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct Queue Queue;

Queue *queue_create();

void enqueue(Queue *q, void *data);

void *dequeue(Queue *q);

void *queue_front(Queue *q);

void *queue_back(Queue *q);

int queue_size(Queue *q);

bool queue_isempty(Queue *q);

#ifdef __cplusplus
}
#endif

#endif
