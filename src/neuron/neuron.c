#include "neuron.h"

NeuronEdge neuronedge(NeuronNode s, NeuronNode d) {
    NeuronEdge e = malloc(sizeof(*e));
    e->weight = 0;
    e->value = 0;
    e->source = s;
    e->destination = d;
    return e;
}

NeuronNode neuronnode(NeuronEdge *i, NeuronEdge *o) {
    NeuronNode n = malloc(sizeof(*n));
    n->input = i;
    n->output = o;
    n->bias = 0;
    return n;
}

NeuralLayer neurallyr(NeuronNode *n, int len) {
    NeuralLayer lyr = malloc(sizeof(*lyr));
    lyr->nodes = n;
    lyr->len = len;
    return lyr;
}

NeuralNetwork neuralnet(int lyrs, int *n) {
    for (int i = 0; i < lyrs; i++) {
        
    }
}