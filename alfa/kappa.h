#ifndef KAPPA_H
#define KAPPA_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

typedef struct KappaTree KappaTree;
typedef struct KappaNode KappaNode;

typedef enum {AVL, BST, SIMPLE}TreeType;

//maybe do Kappa status a struct with one of this values + a message
typedef enum {NOT_FOUND, INVALID_ARGUMENT, ALOCATION_ERROR, Ok, Err, NO_DESTRUCTOR} KappaStatus;
typedef enum {Inorder, Preorder, Postorder} TravMode;

typedef void(*dest_fn)(void *);

//the function is intended to accept the payload of the node
//retunr is by convention a>b => 1; a = b => 0;  a < b => -1;
typedef int(*comp_fn)(const void *, const void*);




KappaTree* kappa_create(TreeType t, comp_fn comp , dest_fn destroy);
KappaStatus kappa_insert(KappaTree *tree, void *value);

//Check or find elements
bool kappa_contains(KappaTree *tree, void *value);
const void* kappa_find(KappaTree *tree, void *value);
const void* kappa_min(KappaTree *tree);
const void* kappa_max(KappaTree *tree);
const void* kappa_ceil(KappaTree *tree, void *value);
const void* kappa_floor(KappaTree *tree, void *value);

//Deletes the node and its value via destructor
KappaStatus kappa_erase(KappaTree *tree, void *value);
//Delets the node and returns the value for the user
void* kappa_take(KappaTree *tree, void *value);


//Clears the entire tree via destructor
KappaStatus kappa_clear(KappaTree *tree);
//Clears the tree but returns the values in an array of void pointers
//NOTE use size to know the size of the arr
void** kappa_release(KappaTree *tree);


int kappa_size(KappaTree *tree);

void** kappa_traverse(KappaTree *tree, TravMode mode);


#ifdef __cplusplus
}
#endif

#endif