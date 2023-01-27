#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scanner/tokens.h"


enum Month {
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

typedef struct _Date {
    int day;
    enum Month month;
    int year;
} *Date;

typedef struct _Rating {
    char *username;
    char *movie;
    int value;
    Date date;
} *Rating;

// Maps month string to enum.
enum Month month(char*);

// Date constructor.
Date date(int, enum Month, int);

// Rating constructor.
Rating rating(char*, char*, int, Date);

extern FILE *yyin;

int yylex(void); /* prototype for the lexing function */

// Parses string into int.
int parseint(char*);

// Parses date string into Date.
Date parsedate(char*);

// Parses file with given filename and returns an array of Rating(s).
Rating *parsef(char*);
