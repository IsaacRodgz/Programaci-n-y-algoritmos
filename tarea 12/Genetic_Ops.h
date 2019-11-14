#ifndef GENETIC_OPS_H
#define GENETIC_OPS_H

#include "Population.h"

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class GeneticOps {

public:

    // Methods

    static void crossOver(Population& p);

    static void select(int method, Population& p, double percentage);

};

#endif
