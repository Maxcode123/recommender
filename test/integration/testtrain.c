#include <criterion/criterion.h>

#include "../../src/neuron/train.h"

Test(testtrain, testassignoutput) {
    int n[] = {2, 2, 1};
    NeuralNetwork NN = neuralnet(3, n);

    NN->layers[0]->nodes[0]->output[0]->value = 2;
    NN->layers[0]->nodes[0]->output[0]->weight = 1;

    NN->layers[0]->nodes[1]->output[0]->value = 5;
    NN->layers[0]->nodes[1]->output[0]->weight = 0.5;

    NN->layers[1]->nodes[0]->bias = 1.5;

    assignoutput(&(NN->layers[1]->nodes[0]), 2, 1);
    double h = 2*1 + 5*0.5 + 1.5;
    cr_assert(NN->layers[1]->nodes[0]->activation == h);
    cr_assert(NN->layers[1]->nodes[0]->output[0]->value = sigm(h));
    cr_assert(NN->layers[2]->nodes[0]->input[0]->value == sigm(h));
}

Test(testtrain, testforward) {
    int n[] = {2, 2, 1};
    NeuralNetwork NN = neuralnet(3, n);
    double arr[] = {5, 9};

    NN->layers[0]->nodes[0]->output[0]->weight = 0.5;
    NN->layers[0]->nodes[0]->output[1]->weight = 0.5;
    NN->layers[0]->nodes[1]->output[0]->weight = 0.5;
    NN->layers[0]->nodes[1]->output[1]->weight = 0.5;

    NN->layers[1]->nodes[0]->output[0]->weight = 0.5;
    NN->layers[1]->nodes[1]->output[0]->weight = 0.5;

    NN->layers[1]->nodes[0]->bias = 2.5;
    NN->layers[1]->nodes[1]->bias = 2.5;
    NN->layers[2]->nodes[0]->bias = 2.5;

    Vector x = vector_init_by_array(2, arr);
    Vector y_ = forward(NN, x);
    cr_assert(vector_size(y_) == 1);
    
    NeuronEdge e11_2 = NN->layers[0]->nodes[0]->output[0];
    NeuronEdge e12_2 = NN->layers[0]->nodes[0]->output[1];
    NeuronEdge e21_2 = NN->layers[0]->nodes[1]->output[0];
    NeuronEdge e22_2 = NN->layers[0]->nodes[1]->output[1];
    NeuronEdge e11_3 = NN->layers[1]->nodes[0]->output[0];
    NeuronEdge e21_3 = NN->layers[1]->nodes[1]->output[0];

    double a21 = (e11_2->weight * 5) + (e21_2->weight * 5) + NN->layers[1]->nodes[0]->bias;
    cr_assert(a21 == NN->layers[1]->nodes[0]->activation);
    cr_assert(e11_3->value == sigm(a21));

    double a22 = (e12_2->weight * 9) + (e22_2->weight * 9) + NN->layers[1]->nodes[1]->bias;
    cr_assert(a22 == NN->layers[1]->nodes[1]->activation);
    cr_assert(e21_3->value == sigm(a22));

    double a31 = (e11_3->weight * e11_3->value) + (e21_3->weight * e21_3->value) + NN->layers[2]->nodes[0]->bias;
    cr_assert(a31 == NN->layers[2]->nodes[0]->activation, "%f != %f", a31, NN->layers[2]->nodes[0]->activation);

    cr_assert(vector_get(y_, 0) == sigm(a31), "%f != %f", vector_get(y_, 0), sigm(a31));
}