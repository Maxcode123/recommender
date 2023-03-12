#include "../preprocess/parser/parser.h"
#include "../preprocess/filter.h"


extern void defdbins(int, int, int, int);
extern void dateshst(HashTable, char*);

void main(int argc, char **argv) {
    List rlst = lst_list();
    parseall(&rlst);

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);

    // List fltr = filter(usermap, rlst);

    defdbins(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    dateshst(usermap, "/home/max/Repos/recommender/plot/dates.txt");
}