#include "GA.h"
#include "Organism.h"
#include "Population.h"
#include "Environment.h"
#include "Genetic_Ops.h"

#include <math.h>
#include <bits/stdc++.h>

using namespace std;

GA::GA( int pop_sizep, int num_bitsp, int funcp, double leftp, double rightp,
    int selection_methodp, int itersp, double percentagep, double epsilonp ) :
    pop_size(pop_sizep), num_bits(num_bitsp), func(funcp), left(leftp), right(rightp),
    selection_method(selection_methodp), iters(itersp), percentage(percentagep),
    epsilon(epsilonp), p(pop_sizep, num_bitsp, leftp, rightp), lastIter(0) {}

void GA::run(){

    // Initialize population

    p.initialize();

    // Evaluate fitness of each organism
    env.evaluate(p, func);

    // Select organisms with best fitness by Ranking according to pecentage parameter

    GeneticOps::select(selection_method, p, percentage);

    // Save best solution so far

    best = p.getPopulation()[0];

    for (int i = 0; i < iters; i++) {

        lastIter++;

        // Update gene distribution (Frequency table)

        p.calculateFreq();

        // Generate new population with chromosomes following distribution calculated

        GeneticOps::crossOver(p);

        // Evaluate fitness of each organism

        env.evaluate(p, func);

        // Select organisms with best fitness by Ranking according to pecentage parameter

        GeneticOps::select(selection_method, p, percentage);

        // Update best solution

        if ( p.getPopulation()[0].getFitness() < best.getFitness() )
            best = p.getPopulation()[0];

        // Test if organisms differ in fitness at most by epsilon and stop iteration if true

        if ( p.getVariance() < epsilon )
            break;
    }
}

Organism GA::getBest(){

    return best;
}

int GA::getLastIter(){

    return lastIter;
}

void GA::print(){

    cout << "\nUMD Algorithm excecuted with following parameters:\n" << endl;
    cout << "* Population size: " << pop_size << endl;
    cout << "* Chromosome size: " << num_bits << endl;
    cout << "* Function option to minimize: " << func << endl;
    cout << "* Interval of search: [" << left << ", " << right << "]" << endl;
    cout << "* Selection method: " << "Ranking" << endl;
    cout << "* Ranking percentage: " << percentage*100.0 << "%" << endl;
    cout << "* Max number of iterations: " << iters << endl;
    cout << "* Stopping variance value: " << epsilon << endl;
}
