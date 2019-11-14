#include "Population.h"
#include "Organism.h"

#include <bits/stdc++.h>
#include <string.h>
#include <random>

using namespace std;

Population::Population( int sizep, int numBitsp, double leftp, double rightp ) :

    size(sizep), sizeO(sizep), numBits(numBitsp), left(leftp), right(rightp), variance(0.0) { }


void Population::initialize(){

    /*
    Table of frequencies initialized to 0.5.
    Equal probability of 0.5 for each bit to have value 1.
    */

    for (int i = 0; i < numBits; i++) {

        freq.push_back(0.5);
    }

    // Create individuals

    for (int i = 0; i < size; i++) {

        popul.push_back(this->createOrganism());
    }
}

Organism Population::createOrganism(){

    Organism org(left, right, numBits);
    org.setChromosome(freq);
    org.decode();

    return org;
}

void Population::updatePopulation(){

    for (int i = 0; i < size; i++) {

        popul[i] = (this->createOrganism());
    }

    for (int i = size; i < sizeO; i++) {

        popul.push_back(this->createOrganism());
    }

    size = sizeO;
}

void Population::calculateFreq(){

    for (int i = 0; i < freq.size(); i++)
        freq[i] = 0;

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < numBits; j++) {

            string chromosome = popul[i].getChromosome();

            if ( chromosome.compare(j, 1, "1") == 0 )
                freq[j] += 1.0;
        }
    }

    for (int j = 0; j < numBits; j++) {

        freq[j] /= size;
    }

}

int Population::getSize(){

    return size;
}

int Population::getSizeO(){

    return sizeO;
}

vector<Organism> Population::getPopulation(){

    return popul;
}

Organism Population::getElem(int i){

    return popul[i];
}

double Population::getVariance(){

    return variance;
}

void Population::setSize(int new_size){

    size = new_size;
}

void Population::setElemFitness(int i, double value){

    popul[i].setFitness(value);
}

void Population::setPopulation(vector<Organism> pop){

    popul = pop;
}

void Population::setVariance(double variancep){

    variance = variancep;
}

void Population::print(){

    for (int i = 0; i < size; i++) {

        cout << i+1 << ": " << "( " << "x1: " << popul[i].getX1()
             << ", x2: " << popul[i].getX2() << ".  f(x1, x2) = " << popul[i].getFitness() << "\n";
    }
}

void Population::printBinary(){

    for (int i = 0; i < size; i++) {

        cout << i+1 << ": " << popul[i].getChromosome() << "\n";
    }
}

void Population::printFreqs(){

    for (int i = 0; i < numBits; i++) {

        cout << "freq[" << i+1 << "]" << ": " << freq[i] << "\n";
    }
}
