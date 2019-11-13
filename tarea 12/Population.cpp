#include "Population.h"
#include "Organism.h"

#include <bits/stdc++.h>
#include <string.h>
#include <random>

using namespace std;

Population::Population( int sizep, int numBitsp ) : size(sizep), numBits(numBitsp) {


}

void Population::initialize(){

    vector<double> freq;

    for (int i = 0; i < numBits; i++) {

        freq.push_back(0.5);
    }

    // For each individual

    for (int i = 0; i < size; i++) {

        Organism org(0, 1, numBits);
        org.setChromosome(freq);
        org.evaluate();

        popul.push_back(org);
    }
}

void Population::print(){

    for (int i = 0; i < size; i++) {

        cout << i << "( " << "x1: " << popul[i].getX1() << ", x2: " << popul[i].getX2() << ")\n";
    }
}
