#ifndef GAMMA_H
#define GAMMA_H

#include <stdlib.h>
#include <stdio.h>
#include "epsilon.h"


/*
    To use the struct as a func argumment its recommend to use
    typedef gamma(<type>) <name>; 

    Also destructor receives the data not the struct

    Fun fact you can use any type of struct even custom ones without passing the only
    important thing is that it has the 3 main types *data, size, capacity, and destructor,
    as long as it has those it can work with anything

 */

//make a way to define destructor
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
            while((xs)->size != (new_size)) gamma_remove((xs), (xs)->size-1);}\
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

#endif


