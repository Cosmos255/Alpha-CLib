#ifndef EPSILON_H
#define EPSILON_H


#define SWAP(a , b) do{\
    typeof(a) tmp = (a);\
    (a) = (b);\
    (b) = (tmp);\
}while(0)

#endif
