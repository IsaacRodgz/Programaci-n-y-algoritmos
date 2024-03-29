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

Layer::Layer(int input_size_p, int output_size_p, vector<Neuron> units_p, string activation_function_p) :
    input_size(input_size_p), output_size(output_size_p), activation_function(activation_function_p),
    units(units_p) {}

// Methods

void Layer::activateLayer(vector<double> &input){

    for (int i = 0; i < output_size; i++) {

        units[i].activateNeuron(input);
    }
}

void Layer::updateWeights(vector<double> &dz_dw, vector<double> &delta, double learning_rate, int batch_size){

    for (int i = 0; i < units.size(); i++) {

        units[i].updateWeights(dz_dw, delta[i], learning_rate, batch_size);
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

vector<double> Layer::getActivatedOutput(){

    vector<double> output;

    for (int i = 0; i < getOutputSize(); i++) {

        output.push_back(units[i].getActivatedOutput());
    }

    return output;
}

vector<double> Layer::getActivatedOutputDerivative(){

    vector<double> output;

    for (int i = 0; i < getOutputSize(); i++) {

        output.push_back(units[i].getActivatedOutputDerivative());
    }

    return output;
}

string Layer::getActivationFunction(){

    return activation_function;
}

// Setters

void Layer::setInputSize(int input_size_p){

    input_size = input_size_p;
}

void Layer::setOutputSize(int output_size_p){

    output_size = output_size_p;
}

void Layer::setActivationFunction(string activation_function_p){

    activation_function = activation_function_p;
}
