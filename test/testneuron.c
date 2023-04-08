#include <criterion/criterion.h>

#include "../src/neuron/neuron.h"


Test(testneuron, testneuronedgeinit) {
    NeuronEdge e = neuronedge();
    cr_assert(e != NULL);
    cr_assert(e->weight == 0);
    cr_assert(e->value == 0);
}

Test(testneuron, testedgeprod) {
    NeuronEdge e = neuronedge(NULL, NULL);
    e->weight = 0.5;
    e->value = 5;
    cr_assert(edgeprod(e) == 2.5);
}

Test(testneuron, testneuralnetlayers) {
    int n[] = {3, 3, 1};
    NeuralNetwork NN = neuralnet(3, n);
    cr_assert(NN->input == 3);
    cr_assert(NN->output == 1);
    cr_assert(NN->hidden == 1);
}

Test(testneuron, testneuralnetout) {
    int n[] = {3, 3, 1};
    NeuralNetwork NN = neuralnet(3, n);

    NeuronNode out = NN->layers[NN->hidden + 1]->nodes[0];
    cr_assert(out->output == NULL);
    cr_assert(out->input != NULL);    
}

Test(testneuron, testneuralnetin) {
    int n[] = {3, 3, 1};
    NeuralNetwork NN = neuralnet(3, n);
    NeuronNode *in = NN->layers[0]->nodes;

    for (int i = 0; i < 3; i++) {
        cr_assert(in[i]->input == NULL);
        cr_assert(in[i]->output != NULL);
    }
}

Test(testneuron, testedges) {
    int n[] = {2, 2, 1};
    NeuralNetwork NN = neuralnet(3, n);

    NeuronNode first = NN->layers[0]->nodes[0];
    NeuronNode second = NN->layers[0]->nodes[1];
    NeuralLayer lyr2 = NN->layers[1];
    NeuralLayer out = NN->layers[2];

    cr_assert(first->output[0] == lyr2->nodes[0]->input[0]);
    cr_assert(first->output[1] == lyr2->nodes[1]->input[0]);

    cr_assert(second->output[0] == lyr2->nodes[0]->input[1]);
    cr_assert(second->output[1] == lyr2->nodes[1]->input[1]);

    cr_assert(lyr2->nodes[0]->output[0] == out->nodes[0]->input[0]);
    cr_assert(lyr2->nodes[1]->output[0] == out->nodes[0]->input[1]);
}

Test(testneuron, testmutateedges) {
    int n[] = {2, 2, 1};
    NeuralNetwork NN = neuralnet(3, n);

    NeuronEdge e = neuronedge();
    e->weight = 15;

    *(NN->layers[0]->nodes[0]->output[0]) = *e;
    cr_assert(NN->layers[0]->nodes[0]->output[0]->weight == 15);
    cr_assert(NN->layers[1]->nodes[0]->input[0]->weight == 15);
}

Test(testneuron, testnetinitbias) {
    int n[] = {3, 3, 2};
    NeuralNetwork NN = neuralnet(3, n);
    netinit(NN);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n[i]; j++) cr_assert(NN->layers[i]->nodes[j]->bias == 1);
    }
}

Test(testneuron, testinitweight) {
    int n[] = {3, 3, 2};
    NeuralNetwork NN = neuralnet(3, n);
    netinit(NN);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n[i]; j++) {
            for (int k = 0; k < n[i + 1]; k ++) {
                double w = NN->layers[i]->nodes[j]->output[k]->weight;
                cr_assert(w < 1 & w > 0);
            }
        }
    }
}

Test(testneuron, testrandinit) {
    int n[] = {3, 3, 2};
    NeuralNetwork NN = neuralnet(3, n);
    
    cr_assert(!getrandinit());
    netinit(NN);
    cr_assert(getrandinit());
    
    netinit(NN);
    cr_assert(getrandinit());
}