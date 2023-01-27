#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"

YYSTYPE yylval;

extern FILE *yyin;

int pos = 0;

int yylex(void); /* prototype for the lexing function */

static char *toknames[] = {
    "USERNAME",
    "RATING",
    "TITLE",
    "DATE",
};

char *getname(int i) {
    return i<257 || i>269 ? "BAD TOKEN" : toknames[i-257];
}

void reset(char *fname) {
    yyin = fopen(fname, "r");
    if (!yyin) {
        fprintf(stderr, "cannot open file\n");
        exit(1);
    }
}

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
    write = fopen(fname2, "w");
    reset(fname);

    for (;;) {
        i = yylex();
        if (i == 0) break;
        fprintf(write, "%s\n", yylval.sval);
    }
    return 0;
}