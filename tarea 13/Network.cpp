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

double Network::meanSquaredCost(double y, double y_hat){

    return 0.5*(y-y_hat)*(y-y_hat);
}

void Network::updateWeights(vector<double> x, vector<double> y, int batch_size){

    vector<double> delta = {};

    /*
    Update last layer weights
    */

    // delta at output layer

    for (int i = 0; i < y.size(); i++) {

        double delta_l = layers[num_layers-1].getActivatedOutput()[i] - y[i];
        delta.push_back(delta_l);
    }

    /*
        dC/dW^L = dz/dW^L * delta_L = a^(l-1) * delta_L

        dC/db^L = delta_L
    */

    vector<double> dz_dw = layers[num_layers-2].getActivatedOutput();
    layers[num_layers-1].updateWeights(dz_dw, delta, learning_rate, batch_size);

    /*
    Update hidden layers weights
    */

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

        /*
        Update delta_l

        delta_l = dC/dz^(l+1) * dz^(l+1)/da^(l) * da^(l)/dz^(l)

        * dz^(l+1)/da^(l) = w^(l+1)                -> matriz of weights of layer l+1
        * da^(l)/dz^(l) = sigmoid_prime(z^(l))     -> vector of derivative of activation function evaluated at z^(l)
        * dC/dz^(l+1) = delta_(l+1)                -> vector delta of layer l+1

        */

        delta_temp.resize(layers[i].getOutputSize(), 0.0);

        // Calculate matrix-vector product dz^(l+1)/da^(l) * dC/dz^(l+1)
        // dz^(l+1)/da^(l) * dC/dz^(l+1) = w^(l+1) * delta_(l+1) = delta_temp

        l_front = layers[i+1].getUnits();

        for (int j = 0; j < l_front.size(); j++) {

            for (int k = 0; k < l_front[j].getNumInputs(); k++) {

                delta_temp[k] += l_front[j].getWeights()[k] * delta[j];
            }
        }

        // Calculate delta_l = delta_temp * da^(l)/dz^(l) (element-wise product of vectors)
        // delta_l = delta_temp * sigmoid_prime(z^(l))

        activate_prime = layers[i].getActivatedOutputDerivative();

        delta.resize(delta_temp.size(), 0.0);

        for (int j = 0; j < delta.size(); j++) {

            delta[j] = delta_temp[j]*activate_prime[j];
        }

        // Update weights

        layers[i].updateWeights(dz_dw, delta, learning_rate, batch_size);

    }
}

void Network::fit(vector<vector<double> > x, vector<vector<double> > y, int epochs, int batch_size){

    double learning_rate0 = learning_rate;
    double learning_step = 0;
    double epoch_loss;
    vector<double> y_hat;

    for (size_t e = 0; e < epochs; e++) {

        epoch_loss = 0;

        for (int i = 0; i < x.size(); i++) {

            double current_loss = 0;

            forward(x[i]);

            for (int j = 0; j < layers[num_layers-1].getOutputSize(); j++) {

                y_hat = layers[num_layers-1].getActivatedOutput();

                current_loss += meanSquaredCost(y[i][j], y_hat[j]);
            }

            epoch_loss += current_loss;

            updateWeights(x[i], y[i], batch_size);
        }

        epoch_loss /= x.size();

        training_loss.push_back(epoch_loss);

        if( e%100 == 0 ){

            cout << "\nEpoch: " << e << endl;
            cout << "\nCost: " << epoch_loss << endl;
            //learning_step++;
            //learning_rate = learning_rate0 * exp(-0.1*(learning_step+1));
            //cout << "\nlearning_rate: " << learning_rate << endl;
            cout << "\n----------------------------------------------------" << endl;
        }
    }
}

void Network::eval(vector<vector<double> > x_test, vector<vector<double> > y_test){

    vector<double> y_pred;
    bool equal;
    accuracy = 0;

    for (int i = 0; i < x_test.size(); i++) {

        y_pred = predict(x_test[i]);

        equal = true;

        for (int j = 0; j < y_pred.size(); j++) {

            if (y_pred[j] != y_test[i][j]) {

                equal = false;
                break;
            }
        }

        if (equal)
            accuracy += 1;

    }

    accuracy /= y_test.size();
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

vector<double> Network::getTrainingLoss(){

    return training_loss;
}

double Network::getAccuracy(){

    return accuracy;
}

// Setters
