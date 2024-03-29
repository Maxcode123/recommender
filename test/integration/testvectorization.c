#include <criterion/criterion.h>

#include "../../src/preprocess/vectorization.h"

Test(testmatrix, test) {
    List rlst = lst_list();
    parseall(&rlst);

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);

    filter(&usermap, &rlst);
    HashTable moviemap = ht_init(1500);
    mapmovies(moviemap, rlst);

    Vector *v = malloc(sizeof(*v) * ht_size(usermap));
    vectorization(v, usermap, moviemap);
    for (int i = 0; i < ht_size(usermap); i++) {
        cr_assert(vector_size(v[i]) == ht_size(moviemap),
                  "Vector has not length (%d) equal to number of movies (%d)",
                  vector_size(v[i]),
                  ht_size(moviemap));
    }
}
