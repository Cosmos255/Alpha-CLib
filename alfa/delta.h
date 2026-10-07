#ifndef DELTA_H
#define DELTA_H

#ifdef __cplusplus{
extern "C"{
#endif

typedef struct LinkedList LinkedList;
typedef LinkedList ll;

LinkedList *LinkedList_create();


void LinkedList_push(ll *list ,void *value);

void *LinkedList_pop(ll *list);

void *LinkedList_pop_front(ll *list);

void *LinkedList_front(ll *list);

void *LinkedList_back(ll *list);

void *LinkedList_at(ll *list, int pos);

void LinkedList_insert(ll *list, int pos, void *value);

void *LinkedList_remove(ll *list, int pos);

int LinkedList_size(ll *list);

#ifdef __cplusplus
}
#endif

#endif
