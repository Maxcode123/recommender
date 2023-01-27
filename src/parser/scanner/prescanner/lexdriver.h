#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../tokens.h"



extern FILE *yyin;

int yylex(void); /* prototype for the lexing function */

/*
Writes the `username`, `rating`, `helpful`, `total` and `date` fields from csv
file fname to csv file fname2.
*/
int scan(char *fname, char *fname2);