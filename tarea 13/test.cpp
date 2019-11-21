#include <iostream>
#include<bits/stdc++.h>
#include "Neuron.hpp"
#include "Layer.hpp"
#include "Network.hpp"

using namespace std;

// g++ -std=c++11 Activation.cpp Neuron.cpp Layer.cpp Network.cpp test.cpp -o test && ./test

void test_MLP(){

    /*

    model = Network();
    model.add(Data(10));
    model.add(Dense(32, 'relu'));
    model.add(Dropout(0.5));
    model.add(Dense(2, 'sigmoid'));

    model.compile('squared');

    model.fit(x_train, y_train, batch_size, epochs, validation_data = (x_valid, y_valid), verbose = 1);

    model.predict(x_test);

    model.save("path");

    model.load("path");

    */

    //vector<double> x = {1.0, 1.0, 1.0};

    /*

    Neuron n(3, false, 0.0, "sigmoid");

    cout << "\n";

    for (size_t i = 0; i < n.getWeightsSize(); i++) {

        cout << n.getWeights()[i] << endl;
    }

    cout << "\n";

    n.activateNeuron(x);

    cout << "Inner product: " << n.getWeightedOutput() << "\n" << endl;

    cout << "Activated value: " << n.getActivatedOutput() << "\n" << endl;

    */

    /*

    Layer l(3, 3, "sigmoid");

    cout << "Weights: \n";

    for (int i = 0; i < l.getOutputSize(); i++) {

        cout << "\n";

        for (int j = 0; j < l.getInputSize(); j++) {

            cout << l.getUnits()[i].getWeights()[j] << endl;
        }

        cout << l.getUnits()[i].getBias() << endl;
    }

    cout << "\n";

    l.activateLayer(x);

    for (int i = 0; i < l.getOutputSize(); i++) {

        cout << "Activated value: " << l.getUnits()[i].getActivatedOutput() << "\n" << endl;
    }

    */

    /*

    Network model = Network();

    model.addData(3);
    model.addDense(3, "sigmoid");
    model.addOutput(1, "sigmoid");

    model.forward(x);

    vector<Layer> layers = model.getLayers();

    cout << "\nNum layers: " << layers.size() << "\n\n";

    for (int k = 0; k < layers.size(); k++) {

        cout << "Layer " << k+1 << ":\n\n";

        for (int i = 0; i < layers[k].getOutputSize(); i++) {

            cout << "\n";

            for (int j = 0; j < layers[k].getInputSize(); j++) {

                cout << layers[k].getUnits()[i].getWeights()[j] << endl;
            }

            cout << layers[k].getUnits()[i].getBias() << endl;

            cout << layers[k].getUnits()[i].getActivatedOutput() << endl;
        }

        cout << "\n";
    }

    cout << "\nPrediction: \n\n";

    for (int i = 0; i < layers[layers.size()-1].getOutputSize(); i++) {

        cout << layers[layers.size()-1].getUnits()[i].getActivatedOutput() << " ";
    }

    cout << "\n\n";

    */

    //vector<vector<double> > x = {{1.0}, {0.0}, {1.0}, {0.0}, {1.0}};
    //vector<vector<double> > y = {{0.0}, {1.0}, {0.0}, {1.0}, {0.0}};


    // XOR
    vector<vector<double> > x = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {1.0, 1.0}};
    vector<vector<double> > y = {{0.0}, {1.0}, {1.0}, {0.0}};

    Network model = Network();

    model.addData(2);
    model.addDense(3, "sigmoid");
    model.addOutput(1, "sigmoid");

    //model.printWeights();

    model.compile("sgd", "mse", "accuracy", 0.01);
    model.fit(x, y, 5000, 1);

    vector<double> x_test = {1.0, 1.0};
    vector<double> y_pred = model.predict(x_test);

    cout << "\n\nPrediction: \n" << endl;

    for (int i = 0; i < y_pred.size(); i++) {

        cout << y_pred[i] << " " << endl;
    }



}

int main(int argc, char const *argv[]) {

    test_MLP();

    return 0;
}
