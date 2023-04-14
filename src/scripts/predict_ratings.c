#include "../preprocess/parser/parser.h"
#include "../preprocess/filter.h"
#include "../preprocess/vectorization.h"
#include "../clustering/kmeans.h"
#include "../clustering/process.h"
#include "../neuron/predict.h"


void main(int argc, char **argv) {
    List rlst = lst_list();
    parseall(&rlst);

    HashTable usermap = ht_init(900000);
    mapusers(usermap, rlst);

    filter(&usermap, &rlst);

    HashTable moviemap = ht_init(1500);
    mapmovies(moviemap, rlst);

    int k = 4;
    int n = ht_size(usermap);

    Vector *v = malloc(sizeof(*v) * n);
    vectorization(v, usermap, moviemap);

    clustering(v, k, n, 100, &calcd_perc);
    printf("performed kmeans clustering\n");

    int *c = getclusters();
    for (int i = 0; i < n; i++) {
        printf("cluster: %d\n", c[i]);
    }

    HashTable clustermap = vectormap(v, k, n);

    char *key = malloc(sizeof(*key)*10);

    NeuralNetwork *nets[k];
    int nodes[] = {};

    for (int i = 0; i < k; i++) {
        nets[i] = neuralnet(10, nodes);
        Vector *_X[3 * clustersize[i] / 4];
        Vector *_Y[3 * clustersize[i] / 4];
        clusterkey(i, key);
        Vector *vectors = ht_search(clustermap, key);
        Matrix dists = distmatrix(vectors, &calcd_euc);
        for (int j = 0; j < (3 * clustersize[i] / 4); j++) {
            Vector *neighbors = nearest(vectors, vectors[j], k, dists);
            _X[j] = vector_merge(neighbors);
            _Y[j] = vectors[j];
        }
        Matrix X = fromvectors(_X, 3 * clustersize[i] / 4);
        Matrix Y = fromvectors(_Y, 3 * clustersize[i] / 4);
        train(nets[i], X, Y, 0.001, 10000);
    }
    free(key);

}