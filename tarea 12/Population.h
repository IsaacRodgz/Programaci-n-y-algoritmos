#ifndef POPULATION_H
#define POPULATION_H

#include "Organism.h"

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Population {

private:

    int size;
    int sizeO;
    int numBits;
    vector<Organism> popul;
    vector<double> freq;

public:

    Population( int size, int numBits );

    int getSize();
    vector<Organism> getPopulation();
    Organism getElem(int i);

    void setSize(int new_size);
    void setElemFitness(int i, double value);
    void setPopulation(vector<Organism> pop);

    void initialize();

    Organism createOrganism();

    void updatePopulation();

    void calculateFreq();

    void print();

    void printBinary();

    void printFreqs();
};

#endif
