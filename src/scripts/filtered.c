#include "../preprocess/parser/parser.h"
#include "../preprocess/filter.h"


void main(int argc, char **argv) {
    List rlst = lst_list();
    parseall(&rlst);

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);

    List fltr = filter(usermap, rlst);
    HashTable moviemap = ht_init(1500);
    mapmovies(moviemap, fltr);

    printf("Number of filtered Ratings: %d\n", lst_len(fltr));
    printf("Number of filtered unique users: %d\n", ht_size(usermap));
    printf("Number of filtered movies: %d\n", ht_size(moviemap));
}