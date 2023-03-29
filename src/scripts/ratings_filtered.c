#include "../preprocess/parser/parser.h"
#include "../preprocess/filter.h"


extern void defrbins(int, int, int, int, int);
extern void ratingshst(HashTable, char*);

void main(int argc, char **argv) {
    List rlst = lst_list();
    parseall(&rlst);

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);

    filter(&usermap, &rlst);

    defrbins(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    ratingshst(usermap, "/home/max/Repos/recommender/plot/ratings_per_user.txt");
}