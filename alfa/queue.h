#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue Queue;

void queue_create();

void enqueue(Queue *q, void *data);

void *dequeue(Queue *q, void *data);

void *queue_front(Queue *q);

void *queue_back(Queue *q);

int queue_size(Queue *q);

bool queue_isempty(Queue *q);

#endif
