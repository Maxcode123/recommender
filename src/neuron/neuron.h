#pragma once

#include "../utils/matrix.h"

typedef struct _NeuronNode *NeuronNode;

// Represents an edge between two neuron nodes.
typedef struct _NeuronEdge {
    double weight;
    double value;
} *NeuronEdge;


// Represents a neuron node.
typedef struct _NeuronNode {
    NeuronEdge* input; // array of input edges
    NeuronEdge* output; // array of output edges
    double bias;
    double activation; // Sum of weight and value products of incoming edges plus bias
} *NeuronNode;


// Represents a neural network layer.
typedef struct _NeuralLayer {
    NeuronNode* nodes;
    int len; // number of nodes in layer
} *NeuralLayer;


// Represents a neural network.
typedef struct _NeuralNetwork {
    NeuralLayer* layers; // layers[0] is the input layer, layers[hidden+1] is the output layer
    int input; // number of input dimensions
    int hidden; // number of hidden layers
    int output; // number of output dimensions            
} *NeuralNetwork;


// Neuron edge constructor.
NeuronEdge neuronedge();

// Constructs an array of neuron edges.
NeuronEdge *neuronedges(int);

// Calculates the product of weight and value of given edge.
double edgeprod(NeuronEdge);

// Neuron node constructor.
NeuronNode neuronnode();

// Constructs an array of neuron nodes.
NeuronNode *neuronnodes(int);

// Neuron layer constructor.
NeuralLayer neurallyr(NeuronNode*, int);

/* Neural network constructor. First argument is number of layers, second 
argument is an array with corresponding number of nodes in each layer. */
NeuralNetwork neuralnet(int, int*);

/* Creates the input layer. First argument is number of nodes in input layer, 
second argument is number of nodes in first hidden layer. */
NeuralLayer inputlyr(int, int);

NeuralLayer finallyr(int, int);

// Initializes weight and bias to random values.
void netinit(NeuralNetwork);
