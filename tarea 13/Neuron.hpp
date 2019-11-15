#ifndef NEURON_HPP
#define NEURON_HPP

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Neuron {

protected:

    int num_inputs;
    vector<double> weights;
    double bias;
    string activation_function;

public:

    // Constructor

    Neuron(int num_inputs_p, bool use_constant_weight, double constant_weight, string activation_function_p);

    // Methods

    void weight_initialization(bool use_constant_weight, double constant_weight);

    static double gen();

    void calculateInnerProduct(vector<double> &input, double* output);

    void activateNeuron(vector<double> &input, double* output);

    // Getters

    int getNumInputs();

    double getBias();

    vector<double> getWeights();

    int getWeightsSize();

    // Setters

    void setNumImputs(int num_inputs_p);

    void setBias(double bias_p);

    void setWeights(vector<double> weights_p);

};

#endif
