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

num \"[0-9]+\"
username \"[a-zA-Z0-9]([a-zA-Z0-9]|\-|\_|[.]|[ ]|@)*\"
date \"[0-9]+[ ][A-Za-z]+[ ][0-9]+\"


%%
{username} {yylval.sval = String(yytext); return USERNAME;}
{num} {yylval.sval = String(yytext); return NUM;}
{date} {yylval.sval = String(yytext); return DATE;}

