#ifndef SMARTCALC_H
#define SMARTCALC_H

#include "dlist.h"
#include "types.h"

typedef struct s_input_str
{
    int i;
    int len;
    int start;
    char *s;
}   t_input_string;


typedef struct s_token {
    int token_type;
    int token;

}   t_token;
#endif