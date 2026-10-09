#include "../alfa/kappa.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct KappaNode{
    void *value;
    KappaNode *left;
    KappaNode *right;
};

struct KappaTree{
    void *root;
    TreeType type;
    int size;
    dest_fn destructor;
    comp_fn compare;
};

//void (*dest_fn)(void *a, void*b);

//TO DO add the AVL ones and replace inside of kappa with an inspection one

KappaTree* kappa_create(TreeType t, comp_fn comp , dest_fn destroy){
    KappaTree *tree = malloc(sizeof(KappaTree));
    if(tree == NULL){
        fprintf(stderr, "Error: couldnt allocate memory for the tree Wrapper\n");
        exit(1);
    }
    if(comp == NULL){
        fprintf(stderr, "Error: Node comparison function is NULL\n");
        exit(1);
    }
    tree->size = 0;
    tree->destructor = destroy;
    tree->compare = comp;
    return tree;
}

//uhhh eto this should probably be BTS insert 
void kappa_insert(KappaTree *tree, void *value){
    if(tree == NULL || value == NULL){
        fprintf(stderr, "Warning: tried to use insert without passing a tree or a value\n");
        return;
    }
    KappaNode *node = malloc(sizeof(KappaNode));
    if(node == NULL){
        frpintf(stderr, "Error allocating mem for Node\n");
        exit(1);
    }
    *node = (KappaNode){.value=value};
    
    if(tree->root = NULL){
        tree->root = node;
    }else{
        KappaNode *parent = tree->root; //C makes it implict nice :3 Note: IN cpp you must cast it mannualy
        
        //its a bit broken not reall optimised
        while(parent != NULL){
            int result = tree->compare(parent->value, value);
            if(!result){
                fprintf(stderr, "Warning the tree doesnt accept identical values this value wont be inserted");
                return;
            }
            if(result > 0){
                if(parent->left == NULL) parent->left = node;
                else{
                    parent = parent->left;
                    break;
                }
            }else{
                if(parent->right == NULL) parent->right = node;
                else{ 
                    parent = parent->right;
                    break;
                }
            }
        }
    }
    tree->size++;
};

/*
void AVL_insert(){

}
*/

bool kappa_contains(KappaTree *tree, void *value){
    KappaNode *node = kappa_find(tree, value);
    if(node == NULL) return 0;
    return 1;
}

const void* kappa_find(KappaTree *tree, void *value){
    if(tree == NULL || value == NULL){
        printf(stderr, "Warning: kappa_find received tree or value == NULL\n");
        return NULL;
    }
    if(tree->root == NULL) return NULL;

    KappaNode *parent = tree->root;
    int result = tree->compare(parent->value, value);
    while(parent != NULL){
        if(result == 0) return parent->value;
        if(result > 0) parent = parent->left;
        else parent = parent->right;
    }
    return NULL;
}

void kappa_erase(KappaTree *tree, void *value){
    if(tree == NULL || value == NULL){
        printf(stderr, "Warning: kappa_erase received tree or value == NULL\n");
        return NULL;
    }
    if(tree->root == NULL) return;

    //erase the node so the owner previous parent can change 2nd
    //search the inorder predecesoor if only 1 child then replace it with that

    KappaNode *parent = tree->root;  
    KappaNode *target = tree->root;
    int result = tree->compare(target->value, value);

    while(target != NULL){
        if(result == 0) break;
        parent = target;
        if(result > 0) target = target->left;
        else target = target->right;
    }
    if(target == NULL) return;
    KappaNode *replace = NULL;

    //One child or no child situation
    if(target->left == NULL || target->right == NULL)
        replace = (target->left == NULL) ? target->right : target->left;
    else{
        //func for finding successor or predecesor
    }
    (parent->left == target) ? (parent->left = replace) : (parent->right = replace);

    //if(parent->left == target) parent->left = replace;
    //else parent->right =replace;

    if(tree->destructor != NULL) tree->destructor(target);
}

KappaNode* kappa_take(KappaTree *tree, void *value){

}

void kappa_min(){}

void kappa_max(){}

KappaNode* inorder_successor(KappaNode *tree, void *value){

}
KappaNode* inorder_predecessor(){}


void kappa_size(){}

void kappa_clear(){

}

