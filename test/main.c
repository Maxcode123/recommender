#include "../src/preprocess/parser/parser.h"
#include "../src/preprocess/matrix.h"
#include "../src/clustering/kmeans.h"


int main(int argc, char **argv) {

    List rlst = lst_list();
    parseall(&rlst);

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);
    printf("mapped users\n");

    List fltr = filter(usermap, rlst);
    HashTable moviemap = ht_init(1500);
    mapmovies(moviemap, fltr);
    printf("mapped movies\n");

    Vector *R = malloc(sizeof(*R) * ht_size(usermap));
    matrix(R, usermap, moviemap);
    printf("created vector array\n");

    clustering(R, 3, ht_size(usermap), 20);
    printf("finished clustering\n");
}