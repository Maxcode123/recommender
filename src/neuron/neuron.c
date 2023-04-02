#include "neuron.h"

NeuronEdge neuronedge(NeuronNode s, NeuronNode d) {
    NeuronEdge e = malloc(sizeof(*e));
    e->weight = 0;
    e->value = 0;
    e->source = s;
    e->destination = d;
    return e;
}

static inline double edgeprod(NeuronEdge e) {return e->weight * e->value;}

NeuronNode neuronnode() {
    NeuronNode n = malloc(sizeof(*n));
    n->input = NULL;
    n->output = NULL;
    n->bias = 0;
    n->activation = 0;
    return n;
}

NeuralLayer neurallyr(NeuronNode *n, int len) {
    NeuralLayer lyr = malloc(sizeof(*lyr));
    lyr->nodes = n;
    lyr->len = len;
    return lyr;
}

NeuralNetwork neuralnet(int lyrs, int *n) {
    NeuralNetwork NN = malloc(sizeof(*NN));
    NN->input = n[0];
    NN->hidden = lyrs - 2;
    NN->output = n[lyrs - 1];

    NeuralLayer *layers[lyrs];
    layers[0] = inputlyr(n[0]);
    
    for (int i = 1; i < lyrs; i++) {
        NeuralLayer before = layers[i - 1];
        NeuronNode nodes[n[i]];
        for (int j = 0; j < n[i]; j++) {
            nodes[j] = neuronnode();
            NeuronEdge input[before->len];
            for (int k = 0; k < before->len; k++) {
                input[k] = neuronedge(before->nodes[k], n);
            }
            nodes[j]->input = input;
        }
        layers[i] = neurallyr(nodes, n[i]);
    }
    NN->layers = layers;
    return NN;
}

NeuralLayer inputlyr(int len) {
    NeuralLayer input = malloc(sizeof(*input));
    input->len = len;
    NeuronNode nodes[len];
    for (int i = 0; i < len; i++) nodes[i] = neuronnode();
    input->nodes;
    return nodes;
}