#ifndef ALPHA_H
#define ALPHA_H

#ifdef __cplusplus
extern "C"{
#endif

#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned int uint;

#define SV_fmt "%.*s"


typedef struct{
    int count;
    char *data;

}String_View;

String_View sv(const char *cstr);

void sv_chop_left(String_View *sv, uint n);

void sv_chop_right(String_View *sv, uint n);

void sv_trim(String_View *sv);

String_View sv_delim_chop(String_View *sv, char delim);





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
















#define SWAP(a , b) do{\
    typeof(a) tmp = (a);\
    (a) = (b);\
    (b) = (tmp);\
}while(0)


















#define Gamma(T) struct{\
    T *data;\
    size_t size;\
    size_t capacity;\
    void(*destructor)(T*);\
}\

//hidden pointers :3 typedef struct Stack Stack

//can also pass void * and let, user recast back so its more geneic

//Removes all elements
#define gamma_clear(xs)\
do{\
    if(xs->data == NULL) break;\
    if(xs->destructor == NULL) free(xs->data);\
    else{\
        while(xs->size){\
        xs->destructor(xs->data[--xs->size]);\
        }\
    }\
    xs->data = NULL;\
    xs->size = 0;\
    xs->capacity = 0;\
}while(0)

//removes one element O(n)
#define gamma_remove(xs, pos)\
do{\
    if((xs)->size <= 0 || (pos) < 0) break;\
    if((xs)->destructor != NULL){\
        (xs)->destructor(&(xs)->data[(pos)]);\
    }\
    if((pos) != (xs)->size-1){\
    int i = (pos)+1;\
        while(i < (xs)->size){\
            (xs)->data[i-1] = (xs)->data[i];\
            i++;\
        }\
    }\
    (xs)->size--;\
}while(0)

//Removes elements fast but doesnt retain order O(1)
#define gamma_swap_remove(xs, pos)\
do{\
    if((pos) >= (xs)->size || (pos) < 0) break;\
    SWAP((xs)->data[pos], (xs)->data[(xs)->size-1]);\
    gamma_remove((xs), (xs)->size-1);\
}while(0)

//like in Rust condition to keep
//#define gamma_retain()



#define gamma_resize(xs, new_size)\
    do{\
        if((new_size) < 0) break;\
        if((new_size) < (xs)->size){\
            while((xs)->size != (new_size)) gamma_remove((xs), (xs)->size-1);\
        }\
        typeof((xs)->data) temp = realloc((xs)->data, (new_size) * sizeof(*(xs)->data));\
        if(temp == NULL && new_size != 0){\
            fprintf(stderr, "error failed to realocate the dynamic array in gamma()\n");\
            exit(1);\
        }\
        (xs)->data = temp;\
        (xs)->capacity = (new_size);\
    }while(0)


#define gamma_push(xs, x)\
    do{\
        if((xs)->size >= (xs)->capacity){\
            int new_size = ((xs)->capacity == 0) ? 256 : ((xs)->capacity*2);\
            gamma_resize((xs), new_size);\
        }\
        (xs)->data[(xs)->size++] = (x);\
    }while(0)

//DOnt forget to add desutrctor cuz_resize is still not finished for if new_size is smaller
//


#define gamma_insert(xs, pos, value)\
    do{\
        if((pos) >= (xs)->size) gamma_push((xs), (value));\
        if((pos) < 0) break;\
        else{\
            if((xs)->size >= (xs)->capacity) gamma_resize((xs), (xs)->capacity*2);\
            int i = (xs)->size;\
            while(i > (pos) && i > 0){\
                (xs)->data[i] = (xs)->data[--i];\
            }\
            (xs)->data[(pos)] = (value);}\
    }while(0)


#define gamma_shrink_to_size(xs)\
    do{\
        gamma_resize((xs), (xs)->size);\
    }while(0)


#define gamma_pop(xs)\
    do{\
        if((xs)->size == 0) break;\
        gamma_remove((xs), (xs)->size-1);\
    }while(0)

#define gamma_at(xs, pos)\
    do{\
        if((pos) >= (xs)->size || (pos) < 0) return;\
        return (xs)->data[(pos)];\
    }while(0)

#define gamma_data(xs)\
    do{\
        return (xs)->data;\
    }while(0)

#define gamma_size(xs)\
    do{\
        return (sx)->size;\
    }while(0)

//#define erase(xs, pos, count)\



typedef struct Queue Queue;

Queue *queue_create();

void enqueue(Queue *q, void *data);

void *dequeue(Queue *q);

void *queue_front(Queue *q);

void *queue_back(Queue *q);

int queue_size(Queue *q);

bool queue_isempty(Queue *q);



typedef struct Stack Stack;

Stack* stack_create(int capacity);

void stack_push(Stack *s, void *value);

int stack_size(Stack *s);

bool stack_is_empty(Stack *s);

void *stack_peek(Stack *s);

void *stack_pop(Stack *s);

void stack_free(Stack *s);






typedef struct KappaTree KappaTree;
typedef struct KappaNode KappaNode;

typedef enum {AVL, BST, SIMPLE}TreeType;

//maybe do Kappa status a struct with one of this values + a message
typedef enum {NOT_FOUND, INVALID_ARGUMENT, ALOCATION_ERROR, Ok, Err, NO_DESTRUCTOR} KappaStatus;

typedef void(*dest_fn)(const void *value);

//the function is intended to accept the payload of the node
//retunr is by convention a>b => 1; a = b => 0;  a < b => -1;
typedef int(*comp_fn)(const void *, const void*);




typedef struct KappaTree KappaTree;
typedef struct KappaNode KappaNode;

typedef enum {AVL, BTS, SIMPLE}TreeType;

//maybe do Kappa status a struct with one of this values + a message
typedef enum {NOT_FOUND, INVALID_ARGUMENT, ALOCATION_ERROR, Ok, Err, NO_DESTRUCTOR} KappaStatus;
typedef enum {Inorder, Preorder, Postorder} TravMode;

typedef void(*dest_fn)(void *);

//the function is intended to accept the payload of the node
//retunr is by convention a>b => 1; a = b => 0;  a < b => -1;
typedef int(*comp_fn)(const void *, const void*);




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