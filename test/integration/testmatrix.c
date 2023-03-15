#include <criterion/criterion.h>

#include "../../src/preprocess/matrix.h"

Test(testmatrix, test) {
    List rlst = lst_list();
    parseall(&rlst);

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);

    List fltr = filter(usermap, rlst);
    HashTable moviemap = ht_init(1500);
    mapmovies(moviemap, fltr);

    
}
