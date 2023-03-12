#include "../preprocess/parser/parser.h"
#include "../preprocess/filter.h"


extern void defrbins(int, int, int, int, int);
extern void ratingshst(HashTable, char*);

void main(int argc, char **argv) {
    List rlst = lst_list();
    parseall(&rlst);

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);

    List fltr = filter(usermap, rlst);

    defrbins(5, 10, 20, 30, 40);
    ratingshst(usermap, "/home/max/Repos/recommender/plot/ratings_per_user.txt");
}