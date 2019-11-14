#include <iostream>
#include<bits/stdc++.h>
#include "GA.h"
#include "Organism.h"
#include "Population.h"
#include "Environment.h"
#include "Genetic_Ops.h"

using namespace std;

// g++ -std=c++11 Organism.cpp Population.cpp test.cpp -o test && ./test

void test_GA(){

    // f1 [-3, 3]
    // f2 [-4, 4]

    // Set algorithm parameters

    int pop_size = 30;
    int num_bits = 20;
    int func = 2;
    double left = -4;
    double right = 4;
    int selection_method = 1;
    int iters = 50;
    double percentage = 0.3;
    double epsilon = 0.000001;

    // Initialize new genetic algorithm with specified parameters

    GA ga(pop_size, num_bits, func, left, right, selection_method, iters, percentage, epsilon);

    // Print parameters to console

    ga.print();

    // Excecute Genetic Algorithm to find minimum of function

    ga.run();

    // Get best solution found by the algorithm

    Organism best = ga.getBest();

    // Print best solution to console

    cout << "\nBest solution found: f(" << best.getX1() << ", " << best.getX2()
    << ") = " << best.getFitness()  << endl;

    cout << "\nFound after " << ga.getLastIter() << " iterations\n" << endl;

}

int main(int argc, char const *argv[]) {

    test_GA();

    return 0;
}
