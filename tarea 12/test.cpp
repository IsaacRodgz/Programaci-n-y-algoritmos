#include <iostream>
#include<bits/stdc++.h>
#include "Organism.h"
#include "Population.h"
#include "Environment.h"
#include "Genetic_Ops.h"

using namespace std;

// g++ -std=c++11 Organism.cpp Population.cpp test.cpp -o test && ./test

void test_GA(){

    int pop_size = 10;
    int num_bits = 6;
    int func = 1;

    /*
    Organism o1(0, 1, 8);

    vector<double> freq{0.825, 0.925, 0.7, 0.95, 0.1, 0.15, 0.2, 0.05};

    o1.setChromosome(freq);

    cout << "\n" << o1.getChromosome() << "\n";

    o1.evaluate();

    cout << "\nX1: " << o1.getX1() << "\n";
    cout << "\nX2: " << o1.getX2() << "\n\n";
    */

    Environment env;
    Population p1(pop_size, num_bits);
    p1.initialize();
    env.evaluate(p1, func);
    p1.print();
    GeneticOps::select(1, p1, 0.3);
    cout << "\nSelected: \n\n";
    p1.print();
    p1.calculateFreq();
    p1.updatePopulation();
    env.evaluate(p1, func);
    cout << "\nNew population: \n\n";
    p1.print();
    GeneticOps::select(1, p1, 0.3);
    cout << "\nSelected: \n\n";
    p1.print();
}

int main(int argc, char const *argv[]) {

    test_GA();

    return 0;
}
