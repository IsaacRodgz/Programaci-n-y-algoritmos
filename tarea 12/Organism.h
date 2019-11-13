#ifndef ORGANISM_H
#define ORGANISM_H

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Organism {

private:

    double x1;
    double x2;
    string chromosome;
    double left;
    double right;
    int numBits;

public:

    Organism( double left, double right, int numBits );

    void evaluate();

    double getX1();
    double getX2();
    string getChromosome();

    void setChromosome(vector<double> freq);

};

#endif
