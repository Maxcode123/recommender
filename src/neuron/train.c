#include "train.h"


void train(NeuralNetwork NN, Matrix X, Vector Y, double r, int e) {
    int n = X->rows;
    Vector *X_ = tovectors(X);
    for (int i = 0; i < e; i++) singletrain(NN, X_, Y, n, r);
}

void singletrain(NeuralNetwork NN, Vector *X, Vector Y, int n, double r) {
    Vector *d = initerr(NN); // Array of error term vectors θE/θw.
    Vector *d_ = initerr(NN); // buffer
    Vector y_ = forward(NN, X[0]);
    backward(NN, Y, y_, d);
    for (int i = 0; i < n; i++) {
        y_ = forward(NN, X[i]);
        backward(NN, Y, y_, d_);
        for (int j = 0; j < NN->hidden + 2; j++) vector_add(d[j], d_[j]);
    }
    double factor = 1.0 / n;

    for (int k = 0; k < NN->hidden + 2; k++) vector_scale(d[k], factor);
    updatewb(NN, d, r);
    free(d);
    free(d_);
}

Vector forward(NeuralNetwork NN, Vector x) {
    initinputlyr(NN, x);
    for (int k = 1; k < NN->hidden + 1; k++) {
        NeuralLayer before = NN->layers[k-1], lyr = NN->layers[k], after = NN->layers[k+1];
        for (int i = 0; i < lyr->len; i++) {
            assignoutput(&(lyr->nodes[i]), before->len, after->len);
        }
    }
    Vector y_ = vector_create(NN->output);
    NeuralLayer out = NN->layers[NN->hidden + 1];
    int in = NN->layers[NN->hidden]->len; // number of nodes in last hidden layer
    for (int i = 0; i < out->len; i++) vector_push(y_, calcoutput(out->nodes[i], in, true));
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

void assignoutput(NeuronNode *n, int in, int  out) {
    double o = calcoutput(*n, in, false);
    for (int i = 0; i < out; i++) {
        NeuronEdge tmp = neuronedge();
        tmp->weight = (*n)->output[i]->weight;
        tmp->value = o;
        (*n)->output[i]->value = o;
        free(tmp);
    }
}

double calcoutput(NeuronNode n, int in, bool final) {
    double h = 0;
    for (int i = 0; i < in; i++) h += edgeprod(n->input[i]);
    h += n->bias;
    n->activation = h;
    if (final) return h; // g(x) = x, final layer
    return sigm(h); // g(x) = σ(x), hidden layers
}

double sigm(double x) {return (1.0 / (1 + exp(-x)));}

double sigmderiv(double x) {
    double s = sigm(x);
    return s * (1 - s);
}

void backward(NeuralNetwork NN, Vector y, Vector y_, Vector *d) {
    finalerr(NN, y, y_, d);
    for (int i = NN->hidden; i >= 0; i--) lyrerr(NN, i, d);
}

void finalerr(NeuralNetwork NN, Vector y, Vector y_, Vector *d) {
    NeuralLayer final = NN->layers[NN->hidden + 1];
    for (int i = 0; i < vector_size(y_); i++) {
        vector_set(d[NN->hidden + 1], i, (vector_get(y_, i) - vector_get(y, i)));
    }
}

void lyrerr(NeuralNetwork NN, int i, Vector *d) {
    NeuralLayer lyr = NN->layers[i];
    NeuralLayer after = NN->layers[i + 1];
    for (int k = 0; k < lyr->len; k++) {
        NeuronNode n = lyr->nodes[k];
        double g = sigmderiv(n->activation); // g'(ajk) = σ(x)*(1-σ(x))
        double sum = 0;
        for (int j = 0; j < after->len; j++) {
            sum += n->output[j]->weight * vector_get(d[i + 1], j); // wji(k+1) * δi(k+1)
        }
        vector_set(d[i], k, g * sum);        
    }
}

Vector *initerr(NeuralNetwork NN) {
    Vector *d = malloc(sizeof(*d) * (NN->hidden + 2));
    for (int i = 0; i < (NN->hidden + 2); i++) {
        d[i] = vector_init_by_value(NN->layers[i]->len, 0);
    }
    return d;
}

void updatewb(NeuralNetwork NN, Vector *d, double r) {
    for (int i = 0; i < NN->hidden + 1; i++) {
        NeuralLayer lyr = NN->layers[i];
        NeuralLayer after = NN->layers[i + 1];
        for (int j = 0; j < lyr->len; j++) {
            NeuronNode n = lyr->nodes[j];
            NN->layers[i]->nodes[j]->bias += -r * vector_get(d[i], j);
            for (int k = 0; k < after->len; k++) {
                NeuronEdge e = n->output[k];
                NN->layers[i]->nodes[j]->output[k]->weight += -r * vector_get(d[i], j) * e->value; 
            }
        }
    }
    for (int i = 0; i < NN->output; i++) {
        NN->layers[NN->hidden + 1]->nodes[i]->bias += -r * vector_get(d[NN->hidden + 1], i);
    }
}