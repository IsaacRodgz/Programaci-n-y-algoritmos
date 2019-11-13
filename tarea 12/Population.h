#ifndef POPULATION_H
#define POPULATION_H

#include "Organism.h"

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Population {

private:

    int size;
    int numBits;
    vector<Organism> popul;
    vector<double> freq;

public:

    Population( int size, int numBits );

    int getSize();
    vector<Organism> getPopulation();

    void setSize(int new_size);
    void setPopulation(vector<Organism> pop);

    void initialize();

    void print();

    Organism createOrganism();
};

#endif
