#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Population.h"

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Environment {

public:

    // Methods

    double f1(double x1, double x2);

    double f2(double x1, double x2);

    void evaluate(Population& p, int option);

};

#endif
