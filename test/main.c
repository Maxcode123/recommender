#include "../src/preprocess/parser/parser.h"
#include "../src/preprocess/filter.h"
#include "../src/clustering/kmeans.h"
#include "../src/clustering/PCA.h"
#include "../src/preprocess/vectorization.h"
#include "../src/utils/matrix.h"
#include "../src/neuron/neuron.h"
#include "../src/neuron/train.h"


int main(int argc, char **argv) {
    int n[] = {9, 3, 3};
    NeuralNetwork NN = neuralnet(3, n);
    netinit(NN);

    netprint(NN);

    Matrix X = matrix(3, 9);
    
    X->matrix[0][0] = 6;
    X->matrix[0][1] = 9;
    X->matrix[0][2] = 5.5;
    X->matrix[0][3] = 7.2;
    X->matrix[0][4] = 8.4;
    X->matrix[0][5] = 4;
    X->matrix[0][6] = 6.5;
    X->matrix[0][7] = 9.1;
    X->matrix[0][8] = 6.5;

    X->matrix[1][0] = 7;
    X->matrix[1][1] = 8;
    X->matrix[1][2] = 9.3;
    X->matrix[1][3] = 6.5;
    X->matrix[1][4] = 7.1;
    X->matrix[1][5] = 9.8;
    X->matrix[1][6] = 5;
    X->matrix[1][7] = 7.7;
    X->matrix[1][8] = 8.4;

    X->matrix[2][0] = 3;
    X->matrix[2][1] = 4;
    X->matrix[2][2] = 4.3;
    X->matrix[2][3] = 3.5;
    X->matrix[2][4] = 3.9;
    X->matrix[2][5] = 4.5;
    X->matrix[2][6] = 3.2;
    X->matrix[2][7] = 4;
    X->matrix[2][8] = 4;

    Matrix Y = matrix(3, 3);
    
    Y->matrix[0][0] = 6.4;
    Y->matrix[0][1] = 8.6;
    Y->matrix[0][2] = 5.5;
    Y->matrix[1][0] = 7;
    Y->matrix[1][1] = 8;
    Y->matrix[1][2] = 9;
    Y->matrix[2][0] = 3;
    Y->matrix[2][1] = 4;
    Y->matrix[2][2] = 3; 


    train(NN, X, Y, 0.0001, 10000);

    netprint(NN);

    Vector x = vector_create(9);
    vector_push(x, 6);
    vector_push(x, 9);
    vector_push(x, 5.5);
    vector_push(x, 7.2);
    vector_push(x, 8.4);
    vector_push(x, 4);
    vector_push(x, 6.5);
    vector_push(x, 9.1);
    vector_push(x, 6.5);

    
    Vector y_ = forward(NN, x);

    vector_print(y_);
}
