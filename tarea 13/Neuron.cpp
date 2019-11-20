#include "Neuron.hpp"
#include "Activation.hpp"

#include <math.h>
#include <bits/stdc++.h>

using namespace std;

// Constructor

Neuron::Neuron(int num_inputs_p, bool use_constant_weight,
    double constant_weight, string activation_function_p) :
    num_inputs(num_inputs_p), bias(0.0), activation_function(activation_function_p) {

        weight_initialization(use_constant_weight, constant_weight);
    }

// Methods

void Neuron::weight_initialization(bool use_constant_weight, double constant_weight) {

    if ( use_constant_weight ) {

        weights.resize(num_inputs, constant_weight);
    }

    else {

        weights.resize(num_inputs);
        generate(weights.begin(), weights.end(), gen);

    }
}

double Neuron::gen(){

    random_device rd;
    mt19937 e2(rd());
    normal_distribution<> dist(0, 1);

    return dist(e2);
}

void Neuron::calculateInnerProduct(vector<double> &input){

    weighted_output = inner_product(begin(input), end(input), begin(weights), 0.0);
    weighted_output += bias;
}

void Neuron::activateNeuron(vector<double> &input){

    calculateInnerProduct(input);

    activated_output = Activation::activate(activation_function, weighted_output);
}

void Neuron::updateWeights(double dz_dw, double delta, double learning_rate){

    for (int i = 0; i < weights.size(); i++) {

        weights[i] -= learning_rate*(dz_dw*delta);
        bias -= learning_rate*delta;
    }
}

// Getters

int Neuron::getNumInputs(){

    return num_inputs;
}

double Neuron::getBias(){

    return bias;
}

vector<double> Neuron::getWeights(){

    return weights;
}

int Neuron::getWeightsSize(){

    return weights.size();
}

double Neuron::getWeightedOutput(){

    return weighted_output;
}

double Neuron::getActivatedOutput(){

    return activated_output;
}

// Setters

void Neuron::setNumImputs(int num_inputs_p){

    num_inputs = num_inputs_p;
}

void Neuron::setBias(double bias_p){

    bias = bias_p;
}

void Neuron::setWeights(vector<double> weights_p){

    weights = weights_p;
}
