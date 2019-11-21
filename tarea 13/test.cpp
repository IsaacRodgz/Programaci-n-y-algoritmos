#include <iostream>
#include<bits/stdc++.h>
#include "Neuron.hpp"
#include "Layer.hpp"
#include "Network.hpp"
#include "Data.hpp"

using namespace std;

// g++ -std=c++11 Activation.cpp Neuron.cpp Layer.cpp Network.cpp Data.cpp test.cpp -o test && ./test

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

    /*

    // XOR
    vector<vector<double> > x = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {1.0, 1.0}};
    vector<vector<double> > y = {{0.0}, {1.0}, {1.0}, {0.0}};

    Network model = Network();

    model.addData(2);
    model.addDense(3, "sigmoid");
    model.addOutput(1, "sigmoid");

    //model.printWeights();

    model.compile("sgd", "cross_entropy", "accuracy", 0.1);
    model.fit(x, y, 5000, 1);

    vector<vector<double> > x_test = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {1.0, 1.0}};
    vector<vector<double> > y_test = {{0.0}, {1.0}, {1.0}, {0.0}};

    model.eval(x_test, y_test);

    cout << "\n\nAccuracy: " << model.getAccuracy() << "\n" << endl;

    vector<double> trainingLoss = model.getTrainingLoss();

    for (int i = 0; i < trainingLoss.size(); i++) {

        cout << i << " " << trainingLoss[i] << endl;
    }

    */

    vector<vector<double> > x;
    vector<vector<double> > y;
    string dataset_file = "data.dat";

    Data::readDataSet(x, y, dataset_file);

    auto seed = unsigned ( time(0) );

    srand ( seed );
    random_shuffle ( x.begin(), x.end() );

    srand ( seed );
    random_shuffle ( y.begin(), y.end() );

    /*
    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < y[i].size(); j++) {

            cout << "\ny: " << y[i][j] << endl;
        }

        cout << "\nx: "<< endl;

        for (int j = 0; j < x[i].size(); j++) {

            cout << " " << x[i][j] << endl;
        }
    }
    */

    // Split 80% train and 20% test

    // Generate x_train, x_test

    double train_pecentage = 0.8;

    int index = int(x.size()*train_pecentage);

    vector<vector<double> >::const_iterator first = x.begin();
    vector<vector<double> >::const_iterator last = x.begin() + index;
    vector<vector<double> > x_train(first, last);

    first = x.begin() + index;
    last = x.end();
    vector<vector<double> > x_test(first, last);

    // Generate y_train, y_test

    first = y.begin();
    last = y.begin() + index;
    vector<vector<double> > y_train(first, last);

    first = y.begin() + index;
    last = y.end();
    vector<vector<double> > y_test(first, last);

    // Build and Train model

    Network model = Network();

    model.addData(4);
    model.addDense(8, "sigmoid");
    model.addDense(4, "sigmoid");
    model.addOutput(1, "sigmoid");

    model.compile("sgd", "cross_entropy", "accuracy", 0.0001);

    model.fit(x_train, y_train, 10000, 1);

    model.eval(x_train, y_train);

    cout << "\n\nAccuracy: " << model.getAccuracy() << "\n" << endl;

}

int main(int argc, char const *argv[]) {

    test_MLP();

    return 0;
}
