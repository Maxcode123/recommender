#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


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

/* indexed by enum Month, so monthdays[JANUARY] == 31; */ 
static int monthdays[] = {0, 31, 28, 31, 30, 31, 30, 31, 30, 30, 30, 31};

typedef struct _Date {
    int day;
    enum Month month;
    int year;
} *Date;

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

// Returns the number of leap years from AD to given date.
int date_leaps(Date);

// Returns the number of days since AD for given date.
long int date_since(Date);

// Parses date string into Date.
Date parsedate(char*);