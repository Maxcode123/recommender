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
    int c = 0;
    while (n != NULL) {
        r = (Rating)n->i;
        printf("%d ", ++c);
        printrt(r);
        if (i = map_get(usermap, r->username)) lst_add(node(r->movie, r), (List*)&i);
        else {
            List h = lst_list();
            lst_add(node(r->movie, r), &h);
            map_put(usermap, r->username, h);
        }
        n = n->next;
    }
}