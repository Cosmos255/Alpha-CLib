#ifndef BETA_H
#define BETA_H

#include <ctype.h>
#include <stdint.h>
#include <string.h>

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

#endif
