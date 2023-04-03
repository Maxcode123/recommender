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

