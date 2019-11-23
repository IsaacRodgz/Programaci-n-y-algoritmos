#ifndef LAYER_HPP
#define LAYER_HPP

#include "Neuron.hpp"

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Layer {

private:

    int input_size;
    int output_size;
    vector<Neuron> units;
    string activation_function;

public:

    // Constructor

    Layer(int input_size_p, int output_size_p, string activation_function_p);

    // Methods

    void activateLayer(vector<double> &input);

    void updateWeights(vector<double> &dz_dw, vector<double> &delta, double learning_rate, int batch_size);

    // Getters

    int getInputSize();

    int getOutputSize();

    vector<Neuron> getUnits();

    vector<double> getActivatedOutput();

    vector<double> getActivatedOutputDerivative();

    string getActivationFunction();

    // Setters



};

#endif
