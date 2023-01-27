#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils/list.h"



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
Rating rating(char*, char *, int, Date);

// Parses file with given filename and returns an array of Rating(s).
void parsef(char*);

