#include <iostream>
#include<bits/stdc++.h>
#include "GA.h"
#include "Organism.h"

using namespace std;

// g++ -std=c++11 Organism.cpp Population.cpp Genetic_Ops.cpp Selection.cpp Environment.cpp GA.cpp test.cpp -o test && ./test

void test_GA(int pop_size, int num_bits, int func_option, double left_limit, double right_limit, int max_iters, double selection_percentage, double epsilon){

    // Initialize new genetic algorithm with specified parameters

    GA ga(pop_size, num_bits, func_option, left_limit, right_limit, 1, max_iters, selection_percentage, epsilon);

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

    if ( argc < 9 ) {

        cerr << "\n8 arguments are required: pop_size, num_bits, func_option, left_limit, right_limit, max_iters, selection_percentage, epsilon" << "\n\n";
    }

    else {

        test_GA( atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]), atof(argv[7]), atof(argv[8]));
    }

    return 0;
}
