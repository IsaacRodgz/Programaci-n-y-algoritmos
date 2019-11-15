#include <math.h>
#include <bits/stdc++.h>

#include "Layer.hpp"

using namespace std;

// Constructor

Layer::Layer(int input_size_p, int output_size_p, string activation_function_p) :
    input_size(input_size_p), output_size(output_size_p), activation_function(activation_function_p) {

    for (int i = 0; i < output_size; i++) {

        units.push_back(Neuron(input_size, false, 0.0, activation_function));
    }
}

// Methods

void Layer::activateLayer(vector<double> &input, vector<double> &output){

    for (int i = 0; i < output_size; i++) {

        units[i].activateNeuron(input, &output[i]);
    }
}

// Getters

int Layer::getInputSize(){

    return input_size;
}

int Layer::getOutputSize(){

    return output_size;
}

vector<Neuron> Layer::getUnits(){

    return units;
}

// Setters
