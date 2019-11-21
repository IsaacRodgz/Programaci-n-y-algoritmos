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

void Network::compile(string optimizer_p, string loss_p, string metric_p, double learning_rate_p){

    optimizer = optimizer_p;
    loss = loss_p;
    metric = metric_p;
    learning_rate = learning_rate_p;
}

vector<double> Network::predict(vector<double> &input){

    vector<double> output_temp(layers[0].getOutputSize(), 0.0);
    vector<double> input_temp(input);

    for (int i = 0; i < num_layers-1; i++) {

        layers[i].activateLayer(input_temp);

        input_temp.resize(output_temp.size());
        input_temp = layers[i].getActivatedOutput();
        output_temp.resize(layers[i+1].getOutputSize());
    }

    layers[num_layers-1].activateLayer(input_temp);
    output_temp = layers[num_layers-1].getActivatedOutput();

    for (int k = 0; k < output_temp.size(); k++) {

        if ( output_temp[k] >= 0.5 )
            output_temp[k] = 1;
        else
            output_temp[k] = 0;
    }

    return output_temp;
}

void Network::forward(vector<double> &input){

    vector<double> input_temp(input);

    for (int i = 0; i < num_layers-1; i++) {

        layers[i].activateLayer(input_temp);
        input_temp = layers[i].getActivatedOutput();
    }

    layers[num_layers-1].activateLayer(input_temp);
}

double Network::crossEntropyCost(double y, double y_hat){

    return -(y*log(y_hat) + (1-y)*log(1-y_hat));
}

void Network::updateWeights(vector<double> x, vector<double> y){

    vector<double> delta = {};

    // delta at output layer

    for (int i = 0; i < y.size(); i++) {

        double delta_l = layers[num_layers-1].getActivatedOutput()[i] - y[i];
        delta.push_back(delta_l);
    }

    // Update last layer weights

    /*
        dC/dW^L = dz/dW^L * delta_L = a^(l-1) * delta_(l+1)

        dC/db^L = delta_L
    */

    vector<double> dz_dw = layers[num_layers-2].getActivatedOutput();
    layers[num_layers-1].updateWeights(dz_dw, delta, learning_rate);

    // Update hidden layers weights

    vector<Neuron> l_front;
    vector<double> delta_temp;
    vector<double> activate_prime;

    for (int i = num_layers-2; i >= 0; i--) {

        // Update dz/dW^L = a^(l-1)
        // If l = 0, a^(l-1) = x

        if (i == 0) {

            dz_dw = x;
        }

        else{

            dz_dw = layers[i-1].getActivatedOutput();
        }

        // Update delta_l

        delta_temp.resize(layers[i].getOutputSize(), 0.0);

        // Get weights of layer l+1

        l_front = layers[i+1].getUnits();

        for (int j = 0; j < l_front.size(); j++) {

            for (int k = 0; k < l_front[j].getNumInputs(); k++) {

                delta_temp[k] += l_front[j].getWeights()[k] * delta[j];
            }
        }

        activate_prime = layers[i].getActivatedOutputDerivative();

        delta.resize(delta_temp.size(), 0.0);

        for (int j = 0; j < delta.size(); j++) {

            delta[j] = delta_temp[j]*activate_prime[j];
        }

        // Update weights

        layers[i].updateWeights(dz_dw, delta, learning_rate);

    }
}

void Network::fit(vector<vector<double> > x, vector<vector<double> > y, int epochs, int batch_size){

    // MSE calculated for each iteration

    double mse_current;
    vector<double> y_hat;

    for (size_t e = 0; e < epochs; e++) {

        cout << "\nEpoch " << e+1 << "\n" << endl;

        for (int i = 0; i < x.size(); i++) {

            double current_cost = 0;

            forward(x[i]);

            for (int j = 0; j < layers[num_layers-1].getOutputSize(); j++) {

                y_hat = layers[num_layers-1].getActivatedOutput();

                current_cost += crossEntropyCost(y[i][j], y_hat[j]);
            }

            cout << "\nCost: " << current_cost << "\n" << endl;

            updateWeights(x[i], y[i]);
        }

        cout << "\n" << endl;
    }

}

void Network::printWeights(){

    cout << "\n";

    for (int k = 0; k < layers.size(); k++) {

        cout << "Layer " << k+1 << ":\n\n";

        for (int i = 0; i < layers[k].getOutputSize(); i++) {

            cout << "\n";

            for (int j = 0; j < layers[k].getInputSize(); j++) {

                cout << layers[k].getUnits()[i].getWeights()[j] << endl;
            }
        }

        cout << "\n";
    }
}

// Getters

vector<Layer> Network::getLayers(){

    return layers;
}

// Setters
