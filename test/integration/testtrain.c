#include <criterion/criterion.h>

#include "../../src/neuron/train.h"

Test(testtrain, testforward) {
    int n[] = {2, 2, 1};
    NeuralNetwork NN = neuralnet(3, n);
    double arr[] = {5, 9};
    Vector x = vector_init_by_array(2, arr);
    Vector y_ = forward(NN, x);
}