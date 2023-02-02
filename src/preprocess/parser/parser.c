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

Rating rating(char *u, char *m, int v, Date d) {
    if (v < 0 || v > 10) fprintf(stderr, "Invalid rating value for Rating object: %d\n", v);
    Rating r = malloc(sizeof(*r));
    r->username = u;
    r->movie = m;
    r->value = v;
    r->date = d;
    return r;
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

void parsef(char *fname, List *h) {
    if (!(yyin = fopen(fname, "r"))) {
        fprintf(stderr, "cannot open read file\n");
        exit(1);
    }
    int num = 0, tok;
    int value; char * username;
    Rating r;
    while (tok = yylex()) {
        switch (tok) {
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
                char *movie = malloc(sizeof(*movie)*200);
                strcpy(movie, fname);
                r = rating(username, movie, value, parsedate(yylval.sval));
                lst_add(node("", r), h);
                break;
        }
    }
}

void printrt(Rating r) {
    printf(
        "username: %s, rating: %d, date: %d %d %d, movie: %s\n",
        r->username, r->value, r->date->day, r->date->month, r->date->year, r->movie
        );
}

void parseall(List *rlst) {
    DIR *d;
    struct dirent *dir;
    if (d = opendir("data/preprocessed")) {
        char buff[100];
        while ((dir = readdir(d)) != NULL) {
            strcpy(buff, dir->d_name);
            if (strcmp(buff, "..") == 0 || strcmp(buff, ".") == 0) continue;
            char fname[117] = "data/preprocessed/";
            strcat(fname, buff);
            parsef(fname, rlst);
        }
        closedir(d);
    }
}

void mapusers(Map usermap, List rlst) {
    Node n = rlst;
    MapItem i;
    Rating r;
    while (n != NULL) {
        r = (Rating)n->i;
        if (i = map_get(usermap, r->username)) lst_add(node(r->movie, r), (List*)&i);
        else {
            List h = lst_list();
            lst_add(node(r->movie, r), &h);
            map_put(usermap, r->username, h);
        }
        n = n->next;
    }
}

void mapmovies(Map moviemap, List rlst) {
    Node n = rlst;
    MapItem i;
    Rating r;
    while (n != NULL) {
        r = (Rating)n->i;
        if (i = map_get(moviemap, r->movie)) lst_add(node(r->username, r), (List*)&i);
        else {
            List h = lst_list();
            lst_add(node(r->username, r), &h);
            map_put(moviemap, r->movie, h);
        }
        n = n->next;
    }
}