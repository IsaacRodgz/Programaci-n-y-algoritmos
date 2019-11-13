#include "Organism.h"

#include <bits/stdc++.h>
#include <string.h>
#include <random>

using namespace std;

Organism::Organism( double leftp, double rightp, int numBitsp ) : left(leftp), right(rightp), numBits(numBitsp) {


}

void Organism::evaluate(){

    int size = numBits/2;
    double epsilon = (right-left)/(1<<size);

    // set x1

    int val = 0;
    int power = 1;

    for (int i = 0; i < size; i++) {

        if ( chromosome.compare(i, 1, "1") == 0 )
            val += power;

        power *= 2;

    }

    x1 = left + val*epsilon;

    // set x1

    val = 0;
    power = 1;

    for (int i = size; i < 2*size-1; i++) {

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
