#include "lexdriver.h"

YYSTYPE yylval;

int scan(char *fname, char *fname2) {
    
    int i;
    FILE *write;

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