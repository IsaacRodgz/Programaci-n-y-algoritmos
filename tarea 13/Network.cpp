#include "Activation.hpp"
#include "Neuron.hpp"
#include "Layer.hpp"
#include "Network.hpp"

#include <math.h>
#include <bits/stdc++.h>

using namespace std;

// Constructor

Network::Network() : input_size(0), output_size(0), num_layers(0) {}

// Methods

void Network::addData(int num_inputs){

    input_size = num_inputs;
}

void Network::addDense(int num_neurons, string activation_function){

    if ( num_layers == 0 ) {

        layers.push_back(Layer(input_size, num_neurons, activation_function));
    }

    else{

        layers.push_back(Layer(layers[num_layers-1].getOutputSize(), num_neurons, activation_function));
    }

    num_layers++;
}

void Network::addOutput(int num_outputs, string activation_function){

    output_size = num_outputs;

    layers.push_back(Layer(layers[num_layers-1].getOutputSize(), num_outputs, activation_function));

    num_layers++;
}

vector<double> Network::predict(vector<double> &input){

    vector<double> output_temp(layers[0].getOutputSize(), 0.0);
    vector<double> input_temp(input);

    for (int i = 0; i < num_layers-1; i++) {

        layers[i].activateLayer(input_temp, output_temp);

        input_temp.resize(output_temp.size());
        input_temp = output_temp;
        output_temp.resize(layers[i+1].getOutputSize());
    }

    layers[num_layers-1].activateLayer(input_temp, output_temp);

    return output_temp;
}

// Getters

vector<Layer> Network::getLayers(){

    return layers;
}

// Setters
