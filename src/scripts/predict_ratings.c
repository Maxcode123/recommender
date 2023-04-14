#include "../preprocess/parser/parser.h"
#include "../preprocess/filter.h"
#include "../preprocess/vectorization.h"
#include "../clustering/kmeans.h"
#include "../neuron/predict.h"


void main(int argc, char **argv) {
    List rlst = lst_list();
    parseall(&rlst);

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);

    filter(&usermap, &rlst);

    HashTable moviemap = ht_init(1500);
    mapmovies(moviemap, rlst);
    printf("mapped %d movies\n", ht_size(moviemap));

    Vector *v = malloc(sizeof(*v) * ht_size(usermap));
    vectorization(v, usermap, moviemap);
    printf("performed vectorization\n");

    clustering(v, 4, ht_size(usermap), 100, &calcd_perc);
    printf("performed kmeans clustering\n");
    int *c = getclusters();
    for (int i = 0; i < ht_size(usermap); i++) {
        printf("cluster: %d\n", c[i]);
    }

    /*
    organize clusters into a key-value object with clusters as keys and arrays
    arrays of vectors as values
    
    separate each array into test and train

    for each vector in the train part fetch the k-nearest neighbors based on
    calcd_perc and merge their vectors into a single vector

    gather all the merged neighbors vectors and the corresponding vector of the
    user and train the neural network
    */
}