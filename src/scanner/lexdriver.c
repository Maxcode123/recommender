#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"

YYSTYPE yylval;

extern FILE *yyin;

int yylex(void); /* prototype for the lexing function */

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: ./a.out read_filename write_filename\n");
        exit(1);
    }
    
    char *fname, *fname2;
    int i;
    FILE *write;

    fname = argv[1];
    fname2 = argv[2];
    if (!(yyin = fopen(fname, "r"))) {
        fprintf(stderr, "cannot open read file\n");
        exit(1);
    }
    if (!(write = fopen(fname2, "w"))) {
        fprintf(stderr, "cannot open write file\n");
        exit(1);
    }

    for (;;) {
        i = yylex();
        if (i == 0) break;
        fprintf(write, "%s\n", yylval.sval);
    }
    return 0;
}