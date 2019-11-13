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

public:

    Population( int size, int numBits );

    void initialize();

    void print();
};

#endif
