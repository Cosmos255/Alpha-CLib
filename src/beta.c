#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../alfa/beta.h"

//include gamma later

/*
 *za-fold
 zc-close fold
 zo open fold
 zM close all folds
 zR open all folds
 * */

String_View sv(const char *cstr){
    return (String_View){
        .count = strlen(cstr),
        .data = cstr,
    };    
}


void sv_chop_left(String_View *sv, uint n){
    if(sv == NULL) return;
    if(n > sv->count) n = sv->count;
    sv->data+=n;
};

void sv_chop_right(String_View *sv, uint n){
    if(sv == NULL) return;
    if(n > sv->count) n = sv->count;
    sv->count-=n;
};

void sv_trim_left(String_View *sv){
    if(sv == NULL) return;
    while(sv->count > 0 && isspace(*sv->data)){
        sv_chop_left(sv, 1);
    };
}

void sv_trim_right(String_View *sv){
    if(sv == NULL) return;
    while(sv->count > 0 && isspace(*sv->data)){
        sv_chop_right(sv, 1);
    };
};

void sv_trim(String_View *sv){
    sv_trim_left(sv);
    sv_trim_right(sv);
};

String_View sv_delim_chop(String_View *sv, char delim){
    int i = 0;
    while(i < sv->count && sv != NULL && sv->data[i] != delim) i++;
    

    if(i < sv->count){
        String_View result = {
            .count = i,
            .data = sv->data,
        };

        sv_chop_left(sv, i+1);
        return result;
    }
    String_View *result = sv;
    sv_chop_left(sv, sv->count);
    return *result;
};








