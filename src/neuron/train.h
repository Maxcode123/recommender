#include "neuron.h"

/* Train the given neural network. Second argument is X matrix, third argument
is Y matrix, fourth argument is learning rate, fifth argument is number of
epochs to train. */
void train(NeuralNetwork, Matrix, Matrix, double, int);

/* Calculates the output values of given node and assigns them to the 
corresponding output edges. */
void assignoutput(NeuronNode);

// Sigmoid function. Used as activation function.
double sigm(double);

/* Derivative of sigmoid function. Used in gradient descent to calculate the 
deltas of weights and biases. */
double sigmderiv(double);
