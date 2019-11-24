#include "Neuron.hpp"
#include "Activation.hpp"

#include <math.h>
#include <bits/stdc++.h>

using namespace std;

// Constructor

Neuron::Neuron(int num_inputs_p, bool use_constant_weight,
    double constant_weight, string activation_function_p) :
    num_inputs(num_inputs_p), bias(1.0), activation_function(activation_function_p),
    num_iters(0.0), batch_count(0), batch_gradient(0.0) {

        weight_initialization(use_constant_weight, constant_weight);
    }

Neuron::Neuron(int num_inputs_p, vector<double> weights_p, double bias_p, string activation_function_p) :
    num_inputs(num_inputs_p), bias(bias_p), activation_function(activation_function_p),
    num_iters(0.0), batch_count(0), batch_gradient(0.0), weights(weights_p) {

        average_v.resize(num_inputs, 0.0);
        batch_gradient.resize(num_inputs, 0.0);
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

    average_v.resize(num_inputs, 0.0);

    batch_gradient.resize(num_inputs, 0.0);
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
    activated_output_derivative = Activation::activateDerivative(activation_function, weighted_output);
}

void Neuron::updateWeights(vector<double> &dz_dw, double delta, double learning_rate, int batch_size){

    batch_count++;
    num_iters++;

    for (int i = 0; i < weights.size(); i++) {

        batch_gradient[i] += (dz_dw[i]*delta);

        if ( batch_count%batch_size == 0 ) {

            batch_gradient[i] = batch_gradient[i]/double(batch_size);

            double beta = 0.9;

            average_v[i] = beta*average_v[i] + (1-beta)*batch_gradient[i];
            //average_v = average_v/(1-pow(beta, num_iters));

            weights[i] -= learning_rate*average_v[i];

            batch_gradient[i] = 0;
        }

        //weights[i] -= learning_rate*average_v[i];
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

double Neuron::getActivatedOutputDerivative(){

    return activated_output_derivative;
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
