#include <iostream>
#include<bits/stdc++.h>
#include "Neuron.hpp"
#include "Layer.hpp"
#include "Network.hpp"

using namespace std;

// g++ -std=c++11 Neuron.cpp test.cpp -o test && ./test

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

    vector<double> x = {1.0, 1.0, 1.0};

    /*

    Neuron n(3, false, 0.0, "relu");

    cout << "\n";

    for (size_t i = 0; i < n.getWeightsSize(); i++) {

        cout << n.getWeights()[i] << endl;
    }

    cout << "\n";

    n.calculateInnerProduct(x, &output);

    cout << "Inner product: " << output << "\n" << endl;

    n.activateNeuron(x, &output);

    cout << "Activated value: " << output << "\n" << endl;

    */

    /*

    Layer l(3, 3, "relu");

    cout << "Weights: \n";

    for (int i = 0; i < l.getOutputSize(); i++) {

        cout << "\n";

        for (int j = 0; j < l.getInputSize(); j++) {

            cout << l.getUnits()[i].getWeights()[j] << endl;
        }
    }

    cout << "\n";

    l.activateLayer(x, output);

    for (int i = 0; i < output.size(); i++) {

        cout << "Activated value: " << output[i] << "\n" << endl;
    }

    */

    Network model = Network();

    model.addData(3);
    model.addDense(3, "relu");
    model.addOutput(1, "sigmoid");

    vector<Layer> layers = model.getLayers();

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

    cout << "\nPrediction: ";

    vector<double> output = model.predict(x);

    for (int i = 0; i < output.size(); i++) {
        cout << output[i] << " ";
    }

    cout << "\n\n";

}

int main(int argc, char const *argv[]) {

    test_MLP();

    return 0;
}