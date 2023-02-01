#include "histogram.h"

void main() {
    List rlst = lst_list();
    parseall(&rlst);

    printf("all ratings: %d\n", lst_len(rlst));

    Map usermap = map();
    mapusers(usermap, rlst);

    printf("unique users: %d\n", map_len(usermap));

    ratings(usermap);
}

void allratings() {
    List rlst = lst_list();
    parseall(&rlst);

    // Lower bound inclusive upper bound exclusive.
    List rating0_2 = lst_list(); // List with 0-2 ratings. (lower bound exclusive)
    List rating2_4 = lst_list(); // List with 2-4 ratings.
    List rating4_6 = lst_list(); // List with 4-6 rating.
    List rating6_8 = lst_list(); // List with 6-8 rating.
    List rating8_10 = lst_list(); // List with 8-10 rating. (upper bound inclusive)

    Node n = rlst;
    Rating r;
    while (n != NULL) {
        r = (Rating)n->i;
        if (r->value == 0) {n = n->next; continue;}
        if (r->value > 0 && r->value < 2) lst_add(node(n->k, n->i), &rating0_2);
        else if (r->value >= 2 && r->value < 4) lst_add(node(n->k, n->i), &rating2_4);
        else if (r->value >= 4 && r->value < 6) lst_add(node(n->k, n->i), &rating4_6);
        else if (r->value >= 6 && r->value < 8) lst_add(node(n->k, n->i), &rating6_8);
        else if (r->value >= 8 && r->value <= 10) lst_add(node(n->k, n->i), &rating8_10);
        n = n->next;
    }

    printf("All ratings: %d\n", lst_len(rlst));

    FILE *write;

    if (!(write = fopen("plot/ratings.txt", "w"))) {
        fprintf(stderr, "cannot open histogram write file\n");
        exit(1);
    }

    fprintf(write, "\"0-2\" %d\n", lst_len(rating0_2));
    fprintf(write, "\"2-4\" %d\n", lst_len(rating2_4));
    fprintf(write, "\"4-6\" %d\n", lst_len(rating4_6));
    fprintf(write, "\"6-8\" %d\n", lst_len(rating6_8));
    fprintf(write, "\"8-10\" %d\n", lst_len(rating8_10));
}

void ratings(Map usermap){
    // Clusters: 0-10, 10-20, 20-30, 30-40, 40+
    int r[] = {0, 0, 0, 0, 0};
    List n = usermap->lst;
    int len;
    while (n != NULL) {
        len = lst_len((List)n->i);
        if (len > 0 && len <= 2) r[0]++;
        else if (len > 2 && len <= 4) r[1]++;
        else if (len > 4 && len <= 6) r[2]++;
        else if (len > 6 && len <= 8) r[3]++;
        else if (len > 8) r[4]++;
        n = n->next;
    }

    FILE *write;

    if (!(write = fopen("plot/ratings_per_user.txt", "w"))) {
        fprintf(stderr, "cannot open ratings histogram write file\n");
        exit(1);
    }

    fprintf(write, "\"1-2\" %d\n", r[0]);
    fprintf(write, "\"3-4\" %d\n", r[1]);
    fprintf(write, "\"5-6\" %d\n", r[2]);
    fprintf(write, "\"7-8\" %d\n", r[3]);
    fprintf(write, "\"8+\" %d\n", r[4]);
}