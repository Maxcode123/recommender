#include "date.h"


enum Month month(char *m) {
    if (strcmp(m, "January") == 0) return JANUARY;
    if (strcmp(m, "February") == 0) return FEBRUARY;
    if (strcmp(m, "March") == 0) return MARCH;
    if (strcmp(m, "April") == 0) return APRIL;
    if (strcmp(m, "May") == 0) return MAY;
    if (strcmp(m, "June") ==0) return JUNE;
    if (strcmp(m, "July") == 0) return JULY;
    if (strcmp(m, "August") == 0) return AUGUST;
    if (strcmp(m, "September") == 0) return SEPTEMBER;
    if (strcmp(m, "October") == 0) return OCTOBER;
    if (strcmp(m, "November") == 0) return NOVEMBER;
    if (strcmp(m, "December") == 0) return DECEMBER;
    fprintf(stderr, "Invalid month: %s\n", m);
}

Date date(int d, enum Month m, int y) {
    if (y < 0) fprintf(stderr, "Invalid year for Date object: %d\n", y);
    if (d < 0 || d > 31) fprintf(stderr, "Invalid day for Date object: %d\n");
    Date dt = malloc(sizeof(*dt));
    dt->day = d;
    dt->month = m;
    dt->year = y;
    return dt;
}

bool date_gt(Date d1, Date d2) {
    if (d1->year > d2->year) return true;
    else if (d1->year == d2->year) {
        if (d1->month > d2->month) return true;
        else if (d1->month == d2->month) return (d1->day > d2->day);
        return false;
    }
    return false;
}

bool date_eq(Date d1, Date d2) {
    return d1->year == d2->year && d1->month == d2->month && d1->day == d2->day;
}

signed int date_diff(Date d1, Date d2) {
    if (date_gt(d1, d2)) return -date_diff(d2, d1);
    if (date_eq(d1, d2)) return 0;
    return date_since(d2) - date_since(d1);
}

bool date_leap(int y) {
    if (((y % 4 == 0) && (y % 100!= 0)) || (y % 400 == 0)) return true;
    return false;
}

int date_leaps(Date d) {
    int n = d->year;
    if (d->month <= 2) n--;
    return n/4 - n/100 + n/400; // Number of leap years
}

long int date_since(Date d) {
    long int n1 = d->year * 365 + d->day;
    for (int i = 1; i < d->month; i++) n1 += monthdays[i];
    return n1 + date_leaps(d); 
}
