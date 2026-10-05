#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../alfa/gamma.h"



#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))





//
////-1 failed to resize
//bool gamma_resize(gamma *vec, size_t new_size){
//    if(new_size <= 0) new_size = 256;
//    else new_size*=256;
//
//    int *temp = realloc(vec->items, new_size*sizeof(*vec->items));
//    if(temp == NULL) return -1;
//
//    vec->cappacity = new_size;
//    vec->items = temp;
//    vec->size = MIN(vec->size, new_size); 
//    return 0;
//}
//
//void gamma_push(gamma *vec, int item){
//    if(vec->size >= vec->cappacity) gamma_resize(vec, vec->cappacity);
//    vec->items[vec->size++] = item;
//}
//
//
//
//int gamma_pop(gamma *vec){
//    if(vec == NULL) return -1;
//    if(vec->size){
//        return vec->items[vec->size-1];
//        vec->size--;
//    }
//    return 0;
//}
//
//
//void gamma_free(gamma *vec){
//    if(vec == NULL) return;
//    free(vec->items);
//    vec->items = NULL;
//}
//
//
////pos is 0 indexe
//void gamma_delete(gamma *vec, size_t pos, size_t count){
//    if(vec == NULL || pos < 0 || pos >= vec->size || count <=0) return;
//    count = MIN(count, (vec->size-pos));
//    memmove(&vec->items[pos],&vec->items[pos+count], (vec->size-count)*sizeof(*vec->items));
//    vec->size-=count;
//}
//



int main(){
    gamma(int) arr;
    
    for(int i=0; i<20; i++){
        gamma_push(arr, i);
    }

    
    for(int i=0; i<arr.size; i++){
        printf("%d ", i);
    }
    printf("\n");

    /*
     Iota = iterators
     Beta = strings
     zeta = hashing
     nu = io strema events
     eta = memory / allocators
     epsilon = small utilities
     delta = linkked listst mutable structures
     kappa = trees

     

      */
    return 0;
}
