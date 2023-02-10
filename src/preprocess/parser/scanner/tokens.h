#pragma once

#include <string.h>


typedef union {
    int pos;
    int ival;
    char *sval;
} YYSTYPE;
extern YYSTYPE yylval;

# define USERNAME 257
# define NUM 258
# define DATE 259
