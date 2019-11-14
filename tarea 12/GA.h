#ifndef GA_H
#define GA_H

#include "Organism.h"
#include "Population.h"
#include "Environment.h"

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class GA {

private:

    // Algorithm Parameters

    int pop_size;
    int num_bits;
    int func;
    double left;
    double right;
    int selection_method;
    int iters;
    int lastIter;
    double percentage;
    double epsilon;
    Organism best;

    // GA objetcs

    Environment env;
    Population p;

public:

    // Constructor

    GA( int pop_sizep, int num_bitsp, int funcp, double leftp, double rightp,
        int selection_methodp, int itersp, double percentagep, double epsilonp );

    // Methods

    void run();

    void print();

    // Getters

    Organism getBest();

    int getLastIter();

};

#endif
