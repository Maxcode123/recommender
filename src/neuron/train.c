#include "train.h"


void train(NeuralNetwork NN, Matrix X, Matrix Y, double r, int e) {

}

void singletrain(NeuralNetwork NN, Matrix X, Matrix Y, double r) {

}

Vector forward(NeuralNetwork NN, Vector x) {
    initinputlyr(NN, x);
    for (int k = 1; k < NN->hidden + 1; k++) {
        NeuralLayer before = NN->layers[k-1], lyr = NN->layers[k], after = NN->layers[k+1];
        for (int i = 0; i < lyr->len; i++) {
            assignoutput(lyr->nodes[i], before->len, after->len);
        }
    }
    Vector y_ = vector_create(NN->output);
    NeuralLayer out = NN->layers[NN->hidden + 1];
    int in = NN->layers[NN->hidden]->len;
    for (int i = 0; out->len; i++) vector_push(y_, calcoutput(out->nodes[i], in));
    return y_;
}

void initinputlyr(NeuralNetwork NN, Vector x) {
    NeuralLayer input = NN->layers[0];
    NeuralLayer first = NN->layers[1];
    for (int i = 0; i < input->len; i++) {
        NeuronNode n = input->nodes[i];
        for (int j = 0; j < first->len; j++) {
            n->output[j]->value = vector_get(x, j);
        }
    }
}

void assignoutput(NeuronNode n, int in, int  out) {
    double o = calcoutput(n, in);
    for (int i = 0; i < out; i++) n->output[i]->value = o;
}

double calcoutput(NeuronNode n, int in) {
    double h = 0;
    for (int i = 0; i < in; i++) h += edgeprod(n->input[i]);
    h += n->bias;
    n->activation = h;
    return sigm(h);
}

inline double sigm(double x) {return (1.0 / (1 + exp(-x)));}

inline double sigmderiv(double sigm) {return sigm * (1 - sigm);}

void backward(NeuralNetwork NN, Vector x, Vector y, Vector y_, double r) {
    Vector *d = malloc(sizeof(*d)*(NN->hidden+2)); // Array of error term vectors.
    d[NN->hidden + 1] = finalerr(NN, y, y_);
    for (int i = NN->hidden; i > 0; i--) d[i] = lyrerr(NN, i);
    assignw(NN, d);
    assignd(NN, d);
}

Vector finalerr(NeuralNetwork NN, Vector y, Vector y_) {

}

Vector lyrerr(NeuralNetwork NN, int lyr) {

}

void updatewb(NeuralNetwork NN, Vector *d, double r) {
    for (int i = 0; i < NN->hidden + 1; i++) {
        NeuralLayer lyr = NN->layers[i];
        NeuralLayer after = NN->layers[i + 1];
        for (int j = 0; j < lyr->len; j++) {
            NeuronNode n = lyr->nodes[j];
            n->bias += -r * vector_get(d[i], j);
            for (int k = 0; k < after->len; k++) {
                NeuronEdge e = n->output[k];
                e->weight += -r * vector_get(d[i], j) * e->value; 
            }
        }
    }
    for (int i = 0; i < NN->output; i++) {
        NN->layers[NN->hidden + 1]->nodes[i]->bias += -r * vector_get(d[NN->hidden + 1], i);
    }
}