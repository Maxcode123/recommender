#include "neuron.h"

/* Train the given neural network. Second argument is X matrix, third argument
is Y matrix, fourth argument is learning rate, fifth argument is number of
epochs to train. */
void train(NeuralNetwork, Matrix X, Matrix Y, double r, int e);

// Trains the neural network for one epoch.
void singletrain(NeuralNetwork, Matrix X, Matrix Y, double r);

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
void assignoutput(NeuronNode, int in, int out);

// Calculates the output values of given node.
double calcoutput(NeuronNode, int in);

// Sigmoid function. Used as activation function.
inline double sigm(double);

/* Derivative of sigmoid function. Used in gradient descent to calculate the 
deltas of weights and biases. Receives as input the output of the sigmoid
function. */
inline double sigmderiv(double);

/* Performs the backward step of training. Updates the weights w[i][j][k] and
biases b[i][k]. w[i][j][k] is the weight for perceptron h in layer k for
incoming node i in layer k-1, b[i][k] is the bias for perceptron i in layer k.
The weight is assigned to the relative NeuronEdge and the bias to the relative
NeuronNode. */
void backward(NeuralNetwork, Vector x, Vector y, Vector y_, double r);

/* Calculates final layer's error terms. δ[i] = g'(a[i])*(y_ - y) */
Vector finalerr(NeuralNetwork, Vector y, Vector y_);

/* Calculates error terms of given layer (lyr). */
Vector lyrerr(NeuralNetwork, int lyr);

/* Assigns new values to biases and weights based on error term vector array d
 and learning rate r. */
void updatewb(NeuralNetwork, Vector *d, double r);
