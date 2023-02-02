#include "parser.h"

YYSTYPE yylval;

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