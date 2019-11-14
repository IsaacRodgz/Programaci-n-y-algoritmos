#ifndef POPULATION_H
#define POPULATION_H

#include "Organism.h"

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Population {

private:

    int size;                   // Population size
    int sizeO;                  // Population size to update size variable when it is modified
    int numBits;                // Size of each Organism chromosome
    double left;                // Region of R^2 where to look for minimum of f(X1, X2)
    double right;
    vector<Organism> popul;     // Vector that contains all organisms
    vector<double> freq;        // Probability frequency table to generate new organims
    double variance;            // Variance of fitness value of current population (Stopping criterion)

public:

    // Constructor

    Population( int size, int numBits, double left, double right );

    // Methods

    void initialize();
    Organism createOrganism();
    void updatePopulation();
    void calculateFreq();
    void print();
    void printBinary();
    void printFreqs();

    // Getters

    int getSize();
    int getSizeO();
    vector<Organism> getPopulation();
    Organism getElem(int i);
    double getVariance();

    // Setters

    void setSize(int new_size);
    void setElemFitness(int i, double value);
    void setPopulation(vector<Organism> pop);
    void setVariance(double variancep);
};

#endif
