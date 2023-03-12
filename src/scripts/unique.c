#include "../preprocess/parser/parser.h"



int main(int argc, char **argv) {
    
    List rlst = lst_list();
    parseall(&rlst);

    printf("Number of Ratings: %d\n", lst_len(rlst));

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);

    printf("Number of unique users: %d\n", ht_size(usermap));

    HashTable moviemap = ht_init(1500);
    mapmovies(moviemap, rlst);

    printf("Number of unique movies: %d\n", ht_size(moviemap));
}