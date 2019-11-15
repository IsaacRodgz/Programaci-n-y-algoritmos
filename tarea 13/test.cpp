#include <iostream>
#include<bits/stdc++.h>
#include "Neuron.hpp"

using namespace std;

// g++ -std=c++11 Organism.cpp Population.cpp test.cpp -o test && ./test

void test_MLP(){

    Neuron n(3, false, 0.0);

    for (size_t i = 0; i < n.getWeightsSize(); i++) {

        cout << n.getWeights()[i] << endl;
    }

}

int main(int argc, char const *argv[]) {

    test_MLP();

    return 0;
}
