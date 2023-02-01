#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "scanner/tokens.h"
#include "../../utils/list.h"
#include "../../utils/map.h"


enum Month {
    JANUARY = 1,
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

/* indexed by enum Month, so monthdays[JANUARY] == 31; monthdays[FEBRUARY] is
invalid (-1) because it is calculated dynamically based on leap years. */ 
static int monthdays[] = {0, 31, -1, 31, 30, 31, 30, 31, 30, 30, 30, 31};

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

// Returns true if 1st argument is bigger than the second.
bool date_gt(Date, Date);

// Returns true if arguments are equal.
bool date_eq(Date, Date);

// Returns the difference in days of the second date from the first date.
signed int date_diff(Date, Date);

// Returns true if given year is a leap year.
bool date_leap(int);

// Rating constructor.
Rating rating(char*, char*, int, Date);

extern FILE *yyin;

int yylex(void); /* prototype for the lexing function */

// Parses string into int.
int parseint(char*);

// Parses date string into Date.
Date parsedate(char*);

// Parses file with given filename and inserts Ratings in given List.
void parsef(char*, List*);

// Prints rating in nice format.
void printrt(Rating);

// Parses all files and inserts ratings in given List.
void parseall(List*);

// Creates map of username to user's Rating list.
void mapusers(Map, List);

// Creates map of movies to movie's Rating list.
void mapmovies(Map, List);