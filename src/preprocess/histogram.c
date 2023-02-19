#include "histogram.h"

void main() {
    List rlst = lst_list();
    parseall(&rlst);

    printf("all ratings: %d\n", lst_len(rlst));

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);

    printf("unique users: %d\n", ht_size(usermap));

    ratingshst(usermap, "/home/max/Repos/recommender/plot/ratings_per_user.txt");
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

void ratingshst(HashTable usermap, char* fname) {
    int r[] = {0, 0, 0, 0, 0};
    int len;
    for (int i = 0; i < ht_size(usermap); i++) {
        len = lst_len((List)usermap->entries->value);
        if (N_RATINGS_CLUSTER_1(len)) r[0]++;
        else if (N_RATINGS_CLUSTER_2(len)) r[1]++;
        else if (N_RATINGS_CLUSTER_3(len)) r[2]++;
        else if (N_RATINGS_CLUSTER_4(len)) r[3]++;
        else if (N_RATINGS_CLUSTER_5(len)) r[4]++;
    }

    FILE *write;

    if (!(write = fopen(fname, "w"))) {
        fprintf(stderr, "cannot open ratings histogram write file\n");
        exit(1);
    }

    fprintf(write, "\"1-49\" %d\n", r[0]);
    fprintf(write, "\"50-99\" %d\n", r[1]);
    fprintf(write, "\"100-149\" %d\n", r[2]);
    fprintf(write, "\"150-200\" %d\n", r[3]);
    fprintf(write, "\"200+\" %d\n", r[4]);
}

void dateshst(Map usermap, char* fname) {
    int days[] = {0, 0, 0, 0};
    List n = usermap->lst;
    Node tmp1 = n;
    while (tmp1 != NULL) {
        List r = (List)n->i;
        Date min = ((Rating)r->i)->date, max = ((Rating)r->i)->date;
        Node tmp2 = r;
        while (tmp2 != NULL) {
            Date d = ((Rating)tmp2->i)->date;
            if (!date_gt(d, min)) min = d;
            if (date_gt(d, max)) max = d;
            tmp2 = tmp2->next;
        }
        int diff = date_diff(min, max);
        if (N_DAYS_CLUSTER_1(diff)) days[0]++;
        else if (N_DAYS_CLUSTER_2(diff)) days[1]++;
        else if (N_DAYS_CLUSTER_3(diff)) days[2]++;
        else if (N_DAYS_CLUSTER_4(diff)) days[3]++;
        tmp1 = tmp1->next;
    }
    
    FILE *write;

    if (!(write = fopen(fname, "w"))) {
        fprintf(stderr, "cannot open dates histogram write file\n");
        exit(1);
    }

    fprintf(write, "\"1-364 (1yr)\" %d\n", days[0]);
    fprintf(write, "\"365-729 (1-2yr)\" %d\n", days[1]);
    fprintf(write, "\"730-1094 (2-3yr)\" %d\n", days[2]);
    fprintf(write, "\"1095+ (3yr+)\" %d\n", days[3]);
}