#include "../src/preprocess/parser/parser.h"
#include "../src/preprocess/matrix.h"


int main(int argc, char **argv) {
    List rlst = lst_list();
    parseall(&rlst);

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);

    List fltr = filter(usermap, rlst);
    HashTable moviemap = ht_init(1500);
    mapmovies(moviemap, fltr);

    Vector *v = malloc(sizeof(*v) * ht_size(usermap));
    matrix(v, usermap, moviemap);
    for (int i = 0; i < ht_size(usermap); i++) {
        printf("%d\n", vector_size(v[i]));
    }
}