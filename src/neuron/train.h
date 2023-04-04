#pragma once

#include "neuron.h"

/* Train the given neural network. Second argument is X matrix, third argument
is Y matrix, fourth argument is learning rate, fifth argument is number of
epochs to train. */
void train(NeuralNetwork, Matrix X, Matrix Y, double r, int e);

// Trains the neural network for one epoch.
void singletrain(NeuralNetwork, Vector *X, Vector *Y, int n, double r);

/* Performs the forward step of training. Calculates h[i][k] and o[i][k] for 
the given vector. h[i][k] is the product sum plus bias for perceptron i in 
layer k, o[i][k] is the output for node i in layer k and is assigned to the 
value field of the corresponding NeuronEdge. Returns the vector of output 
values from the output layer. */
Vector forward(NeuralNetwork, Vector x);

/* Assigns input vector x values to the output of the nodes in the input layer
of the neural network. */
void initinputlyr(NeuralNetwork, Vector x);

/* Calculates the output values of given node and assigns them to the 
corresponding output edges. Second argument is number of inputs and third is
number of outputs of currrent node. */
void assignoutput(NeuronNode*, int in, int out);

// Calculates the output values of given node.
double calcoutput(NeuronNode, int in);

// Sigmoid function. Used as activation function.
double sigm(double);

/* Derivative of sigmoid function. Used in gradient descent to calculate the 
deltas of weights and biases. Receives as input the output of the sigmoid
function. */
double sigmderiv(double);

/* Performs the backward step of training. Returns the vector array of error
terms calculated. */
void backward(NeuralNetwork, Vector y, Vector y_, Vector *d);

/* Calculates final layer's error terms. δ[i] = g'(a[i])*(y_ - y) */
void finalerr(NeuralNetwork, Vector y, Vector y_, Vector *d);

/* Calculates error terms of given layer (i is the index of the layer and
ranges from 0 to m-1). */
void lyrerr(NeuralNetwork, int i, Vector *d);

/* Assigns new values to biases and weights based on error term vector array d
 and learning rate r. */
void updatewb(NeuralNetwork, Vector *d, double r);
