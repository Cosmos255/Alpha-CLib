#ifndef KAPPA_H
#define KAPPA_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

typedef struct KappaTree KappaTree;
typedef struct KappaNode KappaNode;

typedef enum {AVL, BTS, SIMPLE}TreeType;

typedef void(*dest_fn)(const void *value);

//the function is intended to accept the payload of the node
//retunr is by convention a>b => 1; a = b => 0;  a < b => -1;
typedef int(*comp_fn)(const void *a, const void*b);


KappaTree* kappa_create(TreeType t, comp_fn comp , dest_fn destroy);
void kappa_insert(KappaTree *tree, void *value);
bool kappa_contains(KappaTree *tree, void *value);
const void* kappa_find(KappaTree *tree, void *value);


#ifdef __cplusplus
}
#endif

#endif