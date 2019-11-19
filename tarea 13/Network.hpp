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
    string optimizer;
    string loss;
    string metric;

public:

    // Constructor

    Network();

    // Methods

    void addData(int num_inputs);

    void addDense(int num_neurons, string activation_function);

    void addOutput(int num_outputs, string activation_function);

    void compile(string optimizer_p, string loss_p, string metric_p);

    vector<double> predict(vector<double> &input);

    void getOutput(vector<double> &input, vector<vector<double> > &z_layers, vector<double> &f_l);

    void fit(vector<vector<double> > x, vector<vector<double> > y, int epochs, int batch_size);

    void printWeights();

    // Getters

    vector<Layer> getLayers();

    // Setters



};

#endif
