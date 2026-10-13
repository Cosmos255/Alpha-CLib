#include <kappa.h>
//#include <alfa/queue.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct KappaNode{
    void *value;
    KappaNode *left;
    KappaNode *right;
    int height;
};

struct KappaTree{
    KappaNode *root;
    TreeType type;
    int size;
    dest_fn destructor;
    comp_fn compare;
};

//void (*dest_fn)(void *a, void*b);

//TO DO add the AVL ones and replace inside of kappa with an inspection one

//_node are function suppoused to be helper ones meant to be used inside the program

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
    tree->type = t;
    tree->size = 0;
    tree->destructor = destroy;
    tree->compare = comp;
    return tree;
}

//uhhh eto this should probably be BTS insert 
KappaStatus kappa_insert(KappaTree *tree, void *value){
    if(tree == NULL || value == NULL){
        fprintf(stderr, "Warning: tried to use insert without passing a tree or a value\n");
        return Err;
    }
    KappaNode *node = malloc(sizeof(KappaNode));
    if(node == NULL){
        fprintf(stderr, "Error allocating mem for Node\n");
        exit(1);
        return ALOCATION_ERROR;
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
                //fprintf(stderr, "Warning the tree doesnt accept identical values this value wont be inserted");
                return Err;
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
    return Ok;
};

/*
void AVL_insert(){

}
*/

bool kappa_contains(KappaTree *tree, void *value){
    KappaNode *result = kappa_find(tree, value);
    if(result == NULL) return 0;
    return 1;
}

//only for local use
//if info
 
//have to change everything to void ptr

KappaNode** node_find(KappaTree *tree, void *value){
    if(tree == NULL || value == NULL){
        fprintf(stderr, "Warning: kappa_find received tree or value == NULL\n");
        exit(1);
    }

    //broken 
    KappaNode **node = &(tree->root);

    int result;

    while(*node != NULL){
        result = tree->compare((*node)->value, value);

        if(result == 0) break;

        node = (result > 0) ? &(*node)->left : &(*node)->right;
    }
    return node;
}

const void* kappa_find(KappaTree *tree, void *value){
    KappaNode **result = node_find(tree, value);
    if(result == NULL) return NULL;
    return *result; //idk if it works it might not :3
}

//1 error 0 ok :3
//maybe implement some kind of return error
KappaStatus kappa_erase(KappaTree *tree, void *value){
    void* node = kappa_take(tree, value);
    if(node == NULL) return NOT_FOUND;

    if(tree->destructor == NULL){
        fprintf(stderr, "Usage of kappa_erase without a destructor specified");
        return NO_DESTRUCTOR;
    }
    tree->destructor(node);
    return Ok;
} 

void* kappa_take(KappaTree *tree, void *value){
    if(tree == NULL || value == NULL){
        fprintf(stderr, "Warning: kappa_erase received tree or value == NULL\n");
        return NULL;
    }
    if(tree->root == NULL) return NULL;

    KappaNode **node = node_find(tree, value);

    if(node == NULL){
        fprintf(stderr, "Warning: kappa_erase received tree or value == NULL\n");
        return NULL;
    }

    //not best practices
    value = (*node)->value;


    if((*node)->left == NULL || (*node)->right == NULL){
        KappaNode *replacement = ((*node)->left == NULL) ? (*node)->right : (*node)->left;
        free(*node);
        *node = replacement;
        tree->size--;
        return value;
    }else{
        KappaNode **successor = node;
        successor = &(*successor)->right;
        if ((*successor)->left == NULL){
            free(*node);
            *node = *successor;
            tree->size--;
            return value;
        }

        while((*successor)->left != NULL){
            successor = &(*successor)->left;
        }
        KappaNode *temp = (*successor)->right;
        (*successor)->right = (*node)->right;
        (*successor)->left = (*node)->left;
        free(*node);
        *node = *successor;
        *successor = temp;
        tree->size--;
        return value;
    }
}

const void* kappa_min(KappaTree *tree){
    if(tree == NULL || tree->root == NULL) return NULL;
    KappaNode *min = tree->root;
    while(min->left != NULL){
        min = min->left;
    }
    return min;
}

const void* kappa_max(KappaTree *tree){
    if(tree == NULL || tree->root == NULL) return NULL;
    KappaNode *max = tree->root;
    while(max->right != NULL){
        max = max->right;
    }
    return max;
}

/*
void** inorder_successor(KappaNode **node){
    //so its a pain the idea is you go back until you find root cuz you want to go right at least once then left so on short recursion it is
    if(node == NULL){
        printf(stderr, "Warning: inorder succesoor received node == NULL\n");
        return NULL;
    }
    if((*node)->right == NULL) return node;

}

KappaNode* inorder_successor(KappaTree *tree, void *value){

}


KappaNode* inorder_predecessor(){

}

*/

int kappa_size(KappaTree *tree){
    if(tree == NULL) return -1;
    return tree->size;
}

//warning if no destructor defined it will leak memory :3
//i mean i could add a stack return so it doesnt just dump memory
void node_clear(KappaNode *node, void **arr, int index){
    if(node != NULL){
        arr[index] = node->value;
        if(node->left != NULL) node_clear(node->left, arr, index++);
        if(node->right != NULL) node_clear(node->right, arr, index++);
        free(node);        
    }
    return; 
}

void** kappa_clear(KappaTree *tree){
    if(tree == NULL) return NULL;
    if(tree->destructor == NULL){
        fprintf(stderr, "Called clear without a specified destructor if this is the intention use release");
        exit(1);
    }
    int size = tree->size;
    void **arr = kappa_release(tree);
    if(arr != NULL){
        while(size){
            tree->destructor(arr[size-1]);
            size--;
        }
    }
    return NULL;
}

void** kappa_release(KappaTree *tree){
    if(tree != NULL && tree->size > 0){
        void **arr = malloc(sizeof(*arr)*tree->size);
        node_clear(tree->root, arr, 0);
        tree->size = 0;
        return arr;
    }
    return NULL;
}


void rsd(KappaNode *node, void **arr, int *index){
    arr[(*index)++] = node->value;
    if(node->left != NULL) rsd(node->left, arr, index);
    if(node->right != NULL) rsd(node->right, arr, index);
    return;
}

void srd(KappaNode *node, void **arr, int *index){
    if(node->left != NULL) rsd(node->left, arr, index);
    arr[(*index)++] = node->value;
    if(node->right != NULL) rsd(node->right, arr, index);
    return;
}

void sdr(KappaNode *node, void **arr, int *index){
    if(node->left != NULL) rsd(node->left, arr, index);
    if(node->right != NULL) rsd(node->right, arr, index);
    arr[(*index)++] = node->value;
    return;
}

void** kappa_traverse(KappaTree *tree, TravMode mode){
    if(tree == NULL) return NULL;
    void **arr = malloc(sizeof(*arr)*tree->size);
    if(arr == NULL) return NULL;
    if(tree->root != NULL){
        if(mode == Inorder) srd(tree->root, arr, &(int){0});
        else if(mode == Preorder) rsd(tree->root, arr, &(int){0});
        else sdr(tree->root, arr, &(int){0});
        return arr;
    }
    return NULL;
}
