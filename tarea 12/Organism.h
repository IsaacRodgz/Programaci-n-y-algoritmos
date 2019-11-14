#ifndef ORGANISM_H
#define ORGANISM_H

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Organism {

private:

    double fitness;      // Fitness value
    double x1;           // First independent variable to evaluate f(X1, X2)
    double x2;           // Second independent variable to evaluate f(X1, X2)
    string chromosome;   // Chromosome that encodes tuple X1,X2 as a binary string
    double left;         // Interval where X1, X2 belong ( left <= X1,X2 <= right )
    double right;
    int numBits;         // Size of chromosome attribute, numBits/2 bits for X1 and X2

public:

    // Constructors

    Organism( double left, double right, int numBits );
    Organism();

    // Methods

    void decode();

    // Getters

    double getX1();
    double getX2();
    double getFitness() const;
    string getChromosome();

    // Setters

    void setChromosome(vector<double> freq);
    void setFitness(double value);

};

#endif
