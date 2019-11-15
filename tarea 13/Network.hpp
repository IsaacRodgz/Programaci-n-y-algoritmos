#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "Layer.hpp"

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Network {

private:

    int input_size;
    int output_size;
    int num_layers;
    vector<Layer> layers;

public:

    // Constructor

    Network();

    // Methods

    void addData(int num_inputs);

    void addDense(int num_neurons, string activation_function);

    void addOutput(int num_outputs, string activation_function);

    vector<double> predict(vector<double> &input);

    // Getters

    vector<Layer> getLayers();

    // Setters



};

#endif
