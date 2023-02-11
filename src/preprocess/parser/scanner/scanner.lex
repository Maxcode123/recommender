%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tokens.h"

char *String(char *s) {
    char *p = malloc(strlen(s)+1);
    strcpy(p,s);
    return p;
}

extern int pos;
int _pos=1;

int yywrap(void)
{
 _pos=1;
 return 1;
}

%}

month "January"|"February"|"March"|"April"|"May"|"June"|"July"|"August"|"September"|"October"|"November"|"December"
num \"([0-9]|[1][0])\"
username \"[a-zA-Z0-9]([a-zA-Z0-9]|\-|\_|[.]|[ ]|@)*\"
date \"[0-9]+[ ]{month}[ ][0-9]+\"


%%
{num} {yylval.sval = String(yytext); return NUM;}
{date} {yylval.sval = String(yytext); return DATE;}
{username} {yylval.sval = String(yytext); return USERNAME;}

. {return -1;}
" " {return -1;}
"\n" {return -1;}

