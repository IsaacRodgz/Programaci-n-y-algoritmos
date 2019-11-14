#include "Organism.h"

#include <bits/stdc++.h>
#include <string.h>
#include <random>

using namespace std;

Organism::Organism( double leftp, double rightp, int numBitsp ) :
    left(leftp), right(rightp), numBits(numBitsp) {}

Organism::Organism( ) {}

void Organism::decode(){

    // Assign half of the bits to variable X1 and half to X2

    int size = numBits/2;

    // Variables X1, X2 take values in discrete increments of (b-a)/(2^n)

    double epsilon = (right-left)/(1<<size);

    // decode organism chromosome of X1 to a real value

    int val = 0;
    int power = 1;

    for (int i = 0; i < size; i++) {

        if ( chromosome.compare(i, 1, "1") == 0 )
            val += power;

        power *= 2;

    }

    x1 = left + val*epsilon;

    // decode organism chromosome of X2 to a real value

    val = 0;
    power = 1;

    for (int i = size; i < 2*size; i++) {

        if ( chromosome.compare(i, 1, "1") == 0 )
            val += power;

        power *= 2;

    }

    x2 = left + val*epsilon;

}

double Organism::getX1(){

    return x1;
}

double Organism::getX2(){

    return x2;
}

string Organism::getChromosome(){

    return chromosome;
}

double Organism::getFitness() const{

        return fitness;
}

void Organism::setChromosome( vector<double> freq ){

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);

    chromosome = "";

    for (int i = 0; i < freq.size(); i++) {

        double val = dis(gen);

        //cout << "\nValue: " << val << "\n\n";

        if ( val < freq[i] )
            chromosome += "1";
        else
            chromosome += "0";
    }
}

void Organism::setFitness(double value){

    fitness = value;
}
