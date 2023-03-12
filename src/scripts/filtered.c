#include "../preprocess/parser/parser.h"
#include "../preprocess/filter.h"


void main(int argc, char **argv) {
    List rlst = lst_list();
    parseall(&rlst);

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);

    filter(usermap);
    printf("Filtered unique users: %d\n", ht_size(usermap));
}