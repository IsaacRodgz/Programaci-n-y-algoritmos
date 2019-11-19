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

void Network::compile(string optimizer_p, string loss_p, string metric_p){

    optimizer = optimizer_p;
    loss = loss_p;
    metric = metric_p;
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

void Network::getOutput(vector<double> &input, vector<vector<double> > &z_layers, vector<double> &f_l){

    vector<double> output_temp(layers[0].getOutputSize(), 0.0);
    vector<double> input_temp(input);

    for (int i = 0; i < num_layers-1; i++) {

        layers[i].activateLayer(input_temp, output_temp);

        z_layers.emplace_back(move(input_temp));

        input_temp.resize(output_temp.size());
        input_temp = output_temp;
        output_temp.resize(layers[i+1].getOutputSize());
    }

    layers[num_layers-1].activateLayer(input_temp, output_temp);

    f_l = move(output_temp);

    z_layers.emplace_back(move(input_temp));
}

void Network::fit(vector<vector<double> > x, vector<vector<double> > y, int epochs, int batch_size){

    // MSE calculated for each iteration

    double mse_current;

    for (int i = 0; i < x.size(); i++) {

        mse_current = 0;

        // Activated output of each layer

        vector<vector<double> > z_layers;
        vector<double> f_l;

        getOutput(x[i], z_layers, f_l);

        for (int j = 0; j < f_l.size(); j++) {

            mse_current += (y[i][j] - f_l[j])*(y[i][j] - f_l[j]);

            
        }

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
