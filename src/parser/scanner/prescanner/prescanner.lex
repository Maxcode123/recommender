%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../tokens.h"

char *String(char *s) {
    char *p = malloc(strlen(s)+1);
    strcpy(p,s);
    return p;
}

int _pos=1;

int yywrap(void)
{
 _pos=1;
 return 1;
}

%}

username \".*\"
num \"[0-9]+\"
date \"[0-9]+[ ][A-Za-z]+[ ][0-9]+\"

%%
{username}","{num}","{num}","{date} {yylval.sval = String(yytext); return 1;}

" "	{continue;}
. {}
