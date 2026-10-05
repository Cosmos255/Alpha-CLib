#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../alfa/stack.h"
#include <string.h>

typedef struct{
    char *c;
    int varsta;
    bool majorat;
}my_struct;

int main(){
    my_struct *Persoana = malloc(sizeof(*Persoana));

    *Persoana = (my_struct){
        .c = malloc(sizeof(char)*10),
        .varsta = 19,
        .majorat = true,
    };

    strcpy(Persoana->c, "Victor\0");
    int *number = malloc(sizeof(int));
    *number = 10;
    
    int *my_arr = malloc(sizeof(int)*20);
    
    for(int i=0; i<20; i++){
        my_arr[i] = i;
    }

    Stack *my_stack = stack_create(5);
    
    stack_push(my_stack, Persoana);
    stack_push(my_stack, number);
    stack_push(my_stack, my_arr);

    

    int *arr_out = (int*)stack_pop(my_stack);
    int *numb = (int*)stack_pop(my_stack);
    my_struct *Person_out = (my_struct*)stack_pop(my_stack);

    for(int i=0; i<20; i++){
        printf("%d ", arr_out[i]);
    }
    puts("");
    printf("%s\n", Person_out->c);
    printf("%d\n", Person_out->varsta);
    printf("%d\n", Person_out->majorat);
    puts("");
    printf("%d\n", *numb);

    free(number);
    free(arr_out);
    free(Person_out);
}

