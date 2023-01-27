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

void parsef(char *fname) {
    FILE *fp;
    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    printf("opened file\n");
    char *u = malloc(sizeof(char)*100);
    char *r = malloc(sizeof(char)*5);
    char *h = malloc(sizeof(char)*5);
    char *t = malloc(sizeof(char)*5);
    char *d = malloc(sizeof(char)*50);
    char *tl = malloc(sizeof(char)*100);
    char *rv = malloc(sizeof(char)*2000);

    char line[1024];
    while (fgets(line, 1024, fp))
    {
        char* tmp = strdup(line);
        if (tmp[0] != '"') {
            continue;
        }
        char *username = getfield(tmp, 1);
        if (username[1] == 13 || username[1] == '\0' || username[1] == '"') continue;
        printf("username is %s", username);
        char *rating = getfield(tmp, 2);
        printf(", rating is %s", rating);
        printf(" 1st char is %d\n", rating[1]);
        // NOTE strtok clobbers tmp
        free(tmp);
    }
}

