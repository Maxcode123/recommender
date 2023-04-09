#include "neuron.h"

NeuronEdge neuronedge() {
    NeuronEdge e = malloc(sizeof(*e));
    e->weight = 0;
    e->value = 0;
    return e;
}

NeuronEdge *neuronedges(int n) {
    NeuronEdge *e = malloc(sizeof(*e) * n);
    for (int i = 0; i < n; i++) e[i] = neuronedge();
    return e;
}

double edgeprod(NeuronEdge e) {return e->weight * e->value;}

NeuronNode neuronnode() {
    NeuronNode n = malloc(sizeof(*n));
    n->input = NULL;
    n->output = NULL;
    n->bias = 0;
    n->activation = 0;
    return n;
}

NeuronNode *neuronnodes(int n) {
    NeuronNode *nodes = malloc(sizeof(*nodes) * n);
    for (int i = 0; i < n; i++) nodes[i] = neuronnode();
    return nodes;
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

    NN->layers = malloc(sizeof(*NN->layers) * lyrs);
    NN->layers[0] = inputlyr(n[0], n[1]);
    
    for (int i = 1; i < lyrs - 1; i++) {
        NeuralLayer before = NN->layers[i - 1];
        NeuronNode *nodes = neuronnodes(n[i]);
        for (int j = 0; j < n[i]; j++) {
            nodes[j]->input = neuronedges(before->len);
            for (int k = 0; k < before->len; k++) {
                nodes[j]->input[k] = before->nodes[k]->output[j];
            } 
            nodes[j]->output = neuronedges(n[i + 1]);
        }
        NN->layers[i] = neurallyr(nodes, n[i]);
    }
    NN->layers[lyrs - 1] = finallyr(n[lyrs - 1], NN->layers[lyrs - 2]);
    return NN;
}

NeuralLayer inputlyr(int len, int after) {
    NeuralLayer input = malloc(sizeof(*input));
    input->len = len;
    input->nodes = neuronnodes(len);
    for (int i = 0; i < len; i++) input->nodes[i]->output = neuronedges(after);
    return input;
}

NeuralLayer finallyr(int len, NeuralLayer before) {
    NeuronNode *nodes = neuronnodes(len);
    for (int i = 0; i < len; i++) {
        nodes[i]->input = neuronedges(before->len);
        for (int k = 0; k < before->len; k++) {
            nodes[i]->input[k] = before->nodes[k]->output[i];
        }
    }
    NeuralLayer output = neurallyr(nodes, len);
    return output;
}

bool getrandinit() {return randinit;}

void netinit(NeuralNetwork NN) {
    if (!randinit) {
        srand(time(NULL));
        randinit = true;
    }
    for (int i = 0; i < NN->hidden + 1; i++) {
        NeuralLayer lyr = NN->layers[i];
        NeuralLayer after = NN->layers[i + 1];
        for (int j = 0; j < lyr->len; j++) {
            lyr->nodes[j]->bias = 1;
            for (int k = 0; k < after->len; k++) {
                lyr->nodes[j]->output[k]->weight = ((double)rand()) / RAND_MAX;
            }
        }
    }
    for (int i = 0; i < NN->layers[NN->hidden + 1]->len; i++) {
        NN->layers[NN->hidden + 1]->nodes[i]->bias = 1;
    }
}

void netprint(NeuralNetwork NN) {
    for (int i = 0; i < NN->hidden + 1; i++) {
        NeuralLayer lyr = NN->layers[i];
        NeuralLayer after = NN->layers[i + 1];
        printf("------  LAYER %d  ---------------\n", i);
        for (int j = 0 ; j < lyr->len; j++) {
            printf("    NODE %d:\n", j);
            printf("        bias: %f\n", lyr->nodes[j]->bias);
            for (int k = 0; k < after->len; k++) {
                printf("        output %d weight: %f\n", k, lyr->nodes[j]->output[k]->weight);
            }
        }
        printf("---------------------------------\n");
    }
    NeuralLayer final = NN->layers[NN->hidden + 1];
    printf("----- FINAL LAYER ----------------\n");
    for (int i = 0; i < final->len; i++) {
        printf("    NODE %d:\n", i);
        printf("        bias: %f\n", final->nodes[i]->bias);
    }
    printf("-------------------------------------\n");
}
