#include "parser.h"

YYSTYPE yylval;

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

Rating *parsef(char *fname) {
    if (!(yyin = fopen(fname, "r"))) {
        fprintf(stderr, "cannot open read file\n");
        exit(1);
    }
    int num = 0, t, i = 0;
    int value; char * username;
    Rating *rs = malloc(sizeof(*rs)*1000);
    while (t = yylex()) {
        switch (t) {
            case USERNAME: 
                if (strcmp(yylval.sval, "\"Null\"") == 0) {
                    value = 0;
                    num++;
                    break;
                }
                username = yylval.sval;
                break;
            case NUM:
                if (!num) value = parseint(yylval.sval); num++; break;
            case DATE:
                num = 0;
                rs[i++] = rating(username, fname, value, parsedate(yylval.sval));
                break;
        }
    }
    return rs;
}

int parseint(char *v) {
    int i;
    sscanf(v, "\"%d\"", &i);
    return i;
}

Date parsedate(char * dt) {
    char *m = malloc(sizeof(*m)*11);
    int d, y;
    sscanf(dt, "\"%d %s %d\"", &d, m, &y);
    return date(d, month(m), y);
}

void printrt(Rating r) {
    printf(
        "username: %s, rating: %d, date: %d %d %d, movie: %s\n",
        r->username, r->value, r->date->day, r->date->month, r->date->year, r->movie
        );
}