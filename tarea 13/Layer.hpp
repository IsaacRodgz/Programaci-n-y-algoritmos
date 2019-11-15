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

    void activateLayer(vector<double> &input, vector<double> &output);

    // Getters

    int getInputSize();

    int getOutputSize();

    vector<Neuron> getUnits();

    // Setters



};

#endif
