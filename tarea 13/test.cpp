#include <iostream>
#include<bits/stdc++.h>
#include "Neuron.hpp"
#include "Layer.hpp"
#include "Network.hpp"
#include "Data.hpp"
#include "Graph.hpp"

using namespace std;

// g++ -std=c++11 Activation.cpp Neuron.cpp Layer.cpp Network.cpp Data.cpp Graph.cpp test.cpp -o test -lcairo && ./test 1

void test_MLP(int load){

    vector<vector<double> > x;
    vector<vector<double> > y;
    string dataset_file = "data.dat";

    Data::readDataSet(x, y, dataset_file);

    auto seed = unsigned ( time(0) );

    srand ( seed );
    random_shuffle ( x.begin(), x.end() );

    srand ( seed );
    random_shuffle ( y.begin(), y.end() );

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

    double learning_rate = 0.0001;

    Network model = Network(learning_rate);

    if (load) {

        model.load();

        model.eval(x, y);

        cout << "\n\nAccuracy: " << model.getAccuracy() << "\n" << endl;
    }

    else {

        model.addData(4);
        model.addDense(5, "relu");
        model.addOutput(1, "sigmoid");

        int num_epochs = 6000;
        int batch_size = 40;

        model.fit(x_train, y_train, num_epochs, batch_size);

        model.eval(x_test, y_test);

        cout << "\n\nTest Accuracy: " << model.getAccuracy() << "\n" << endl;

        vector<double> trainingLoss = model.getTrainingLoss();

        // Filter nan and inf values of cross_entropy cost function

        vector<double> trainingLoss_plot;
        copy_if (trainingLoss.begin(), trainingLoss.end(), back_inserter(trainingLoss_plot), [](double i){return !isnan(i) && !isinf(i);} );

        // Filter first epoch cost values for better visualization of cost graph

        vector<double>::const_iterator first_p = trainingLoss_plot.begin() + 30;
        vector<double>::const_iterator last_p = trainingLoss_plot.end();
        vector<double> trainingLoss_plot_f(first_p, last_p);

        plot(trainingLoss_plot_f);

        model.save();
    }
}

int main(int argc, char const *argv[]) {

    if(argc < 2){

        cerr << "\nError: Missing argument\n" << endl;
    }

    else
        test_MLP(atoi(argv[1]));

    return 0;
}
