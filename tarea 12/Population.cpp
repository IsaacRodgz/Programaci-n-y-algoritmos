#include "Population.h"
#include "Organism.h"

#include <bits/stdc++.h>
#include <string.h>
#include <random>

using namespace std;

Population::Population( int sizep, int numBitsp ) : size(sizep), numBits(numBitsp) {


}

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

    Organism org(0, 1, numBits);
    org.setChromosome(freq);
    org.decode();

    return org;
}

int Population::getSize(){

    return size;
}

vector<Organism> Population::getPopulation(){

    return popul;
}

void Population::setSize(int new_size){

    size = new_size;
}

void Population::setPopulation(vector<Organism> pop){

    popul = pop;
}

void Population::print(){

    for (int i = 0; i < size; i++) {

        cout << i+1 << ": " << "( " << "x1: " << popul[i].getX1() << ", x2: " << popul[i].getX2() << ")\n";
    }
}
