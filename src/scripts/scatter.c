#include "../clustering/PCA.h"
#include "../preprocess/parser/parser.h"
#include "../preprocess/filter.h"
#include "../preprocess/vectorization.h"

#include "../utils/matrix.h"


void main(int argc, char **argv) {
    List rlst = lst_list();
    parseall(&rlst);

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);
    printf("mapped %d users\n", ht_size(usermap));
    filter(&usermap, &rlst);
    printf("filtered users: %d\n", ht_size(usermap));

    HashTable moviemap = ht_init(1500);
    mapmovies(moviemap, rlst);
    printf("mapped %d movies\n", ht_size(moviemap));

    Vector *v = malloc(sizeof(*v) * ht_size(usermap));
    vectorization(v, usermap, moviemap);
    printf("vectorized maps\n");

    Matrix m = fromvectors(v, ht_size(usermap));
    
    free(v);
    free(usermap);
    free(moviemap);

    printf("created data matrix (%dx%d)\n", m->rows, m->cols);

    PCA(&m, 2);
    printf("performed PCA\n");
    
    // write2dvecs(m, "plot/scatter.txt");
}