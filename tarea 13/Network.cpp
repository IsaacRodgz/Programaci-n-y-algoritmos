#include "Activation.hpp"
#include "Neuron.hpp"
#include "Layer.hpp"
#include "Network.hpp"

#include <math.h>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <iostream>

using namespace std;

// Constructor

Network::Network(double learning_rate_p) :
    input_size(0), output_size(0), num_layers(0), learning_rate(learning_rate_p) {}

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

    // For each epoch

    for (size_t e = 0; e < epochs; e++) {

        epoch_loss = 0;

        // For each example in training set

        for (int i = 0; i < x.size(); i++) {

            double current_loss = 0;

            // Calculate prediction of MLP

            forward(x[i]);

            // Get prediction vector y_hat

            for (int j = 0; j < layers[num_layers-1].getOutputSize(); j++) {

                y_hat = layers[num_layers-1].getActivatedOutput();

                current_loss += crossEntropyCost(y[i][j], y_hat[j]);
            }

            epoch_loss += current_loss;

            // Update weights with batch gradient descent

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

void Network::save(){

    // Creating a directory
    mkdir("model", 0777);

    ofstream file;
    file.open("model/weights");

    for (int k = 0; k < layers.size(); k++) {

        file << layers[k].getOutputSize() <<  " " << layers[k].getInputSize() << endl;

        for (int i = 0; i < layers[k].getOutputSize(); i++) {

            for (int j = 0; j < layers[k].getInputSize(); j++) {

                file << layers[k].getUnits()[i].getWeights()[j] << " ";
            }

                // Save bias at the end of the weights of each line (neuron)

            file << layers[k].getUnits()[i].getBias();

            file << "\n";
        }

        file << "\n";
    }

    file.close();

    // Save network and layers info

    file.open("model/params");

    file << num_layers << endl;
    file << learning_rate << endl;

    for (int k = 0; k < layers.size(); k++) {

        file << layers[k].getActivationFunction() << endl;
    }

    file.close();
}

void Network::load(){

    ifstream file;
    string line;

    // Load network and layers info

    file.open("model/params");

    string activation_function_s;
    vector<string> activation_function_v;

    getline(file, line);
    stringstream ss1(line);
    ss1 >> num_layers;

    getline(file, line);
    stringstream ss2(line);
    ss2 >> learning_rate;

    cout << "Num layers: " << num_layers << endl;
    cout << "Num Learning rate: " << learning_rate << endl;

    for (int k = 0; k < num_layers; k++) {

        getline(file, line);
        stringstream ss3(line);
        ss3 >> activation_function_s;
        activation_function_v.push_back(activation_function_s);
        cout << "Activation function: " << activation_function_s << endl;
    }

    file.close();

    // Load network weights

    file.open("model/weights");

    // Read weights by layer

    for (size_t k = 0; k < num_layers; k++) {

        // Get layer input and output size

        double input_size_p;
        double output_size_p;

        getline(file, line);
        stringstream ss3(line);
        ss3 >> output_size_p >> input_size_p;

        cout << "\nLayer input size: " << input_size_p << endl;
        cout << "\nLayer output size: " << output_size_p << "\n" << endl;

        // Read each line (neuron) of layer k

        double num_neurons_read = 0;
        vector<Neuron> units_p;

        while ( getline(file, line) ) {

            vector<double> weights_p;
            double bias_p;

            stringstream ss4(line);
            string token;
            double current_col = 0;
            num_neurons_read++;

            cout << "\nRead neuron: " << num_neurons_read << endl;

            while(getline(ss4, token, ' ')){

                if (current_col++ < input_size_p) {

                    cout << "Weight: " << token << endl;
                    weights_p.push_back(stod(token));
                }

                else{

                    cout << "Bias: " << token << endl;
                    bias_p = stod(token);
                }
            }

            units_p.push_back(Neuron(input_size_p, weights_p, bias_p, activation_function_v[k]));

            if (num_neurons_read == output_size_p) {
                break;
            }
        }

        layers.push_back(Layer(input_size_p, output_size_p, units_p, activation_function_v[k]));
        cout << "\nGet next Layer\n" << endl;
        getline(file, line);
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
