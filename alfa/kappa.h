#ifndef KAPPA_H
#define KAPPA_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

typedef struct KappaTree KappaTree;
typedef struct KappaNode KappaNode;

typedef enum {AVL, BTS, SIMPLE}TreeType;

//maybe do Kappa status a struct with one of this values + a message
typedef enum {NOT_FOUND, INVALID_ARGUMENT, ALOCATION_ERROR, Ok, Err, NO_DESTRUCTOR} KappaStatus;

typedef void(*dest_fn)(const void *value);

//the function is intended to accept the payload of the node
//retunr is by convention a>b => 1; a = b => 0;  a < b => -1;
typedef int(*comp_fn)(const void *a, const void*b);



KappaTree* kappa_create(TreeType t, comp_fn comp , dest_fn destroy);
KappaStatus kappa_insert(KappaTree *tree, void *value);
bool kappa_contains(KappaTree *tree, void *value);
const void* kappa_find(KappaTree *tree, void *value);
KappaStatus kappa_erase(KappaTree *tree, void *value);
void* kappa_take(KappaTree *tree, void *value);
const void* kappa_min(KappaTree *tree);
const void* kappa_max(KappaTree *tree);
int kappa_size(KappaTree *tree);
void* kappa_clear(KappaTree *tree);

#ifdef __cplusplus
}
#endif

#endif