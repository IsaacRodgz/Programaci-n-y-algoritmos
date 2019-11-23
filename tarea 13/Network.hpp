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
    double learning_rate;
    vector<double> training_loss;
    double accuracy;

public:

    // Constructor

    Network(double learning_rate_p);

    // Methods

    void addData(int num_inputs);

    void addDense(int num_neurons, string activation_function);

    void addOutput(int num_outputs, string activation_function);

    vector<double> predict(vector<double> &input);

    void forward(vector<double> &input);

    double crossEntropyCost(double y, double y_hat);

    double meanSquaredCost(double y, double y_hat);

    void updateWeights(vector<double> x, vector<double> y, int batch_size);

    void fit(vector<vector<double> > x, vector<vector<double> > y, int epochs, int batch_size);

    void eval(vector<vector<double> > x_test, vector<vector<double> > y_test);

    void printWeights();

    void save();

    void load();

    // Getters

    vector<Layer> getLayers();

    vector<double> getTrainingLoss();

    double getAccuracy();

    // Setters



};

#endif
