#include "parser.h"

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
}

Date date(int d, enum Month m, int y) {
    Date dt = malloc(sizeof(*dt));
    dt->day = d;
    dt->month = m;
    dt->year = y;
    return dt;
}

Rating rating(char *u, char *m, int v, Date d) {
    Rating r = malloc(sizeof(*r));
    r->username = u;
    r->movie = m;
    r->value = v;
    r->date = d;
    return r;
}

char* getfield(char* line, int num)
{
    char* tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}


Rating *parsef(char *fname) {
    
}

