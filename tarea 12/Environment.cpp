#include "Environment.h"
#include "Population.h"

#include <math.h>
#include <bits/stdc++.h>

using namespace std;

double Environment::f1(double x1, double x2){

    return x1*x1 + x2*x2 + 4;
}

double Environment::f2(double x1, double x2){

    return cos(x1)*cos(x2);
}

void Environment::evaluate(Population& p, int option){

    // Variables to update variance

    double mean;
    double variance = 0;

    // Update fitness value of each organism

    for (int i = 0; i < p.getSize(); i++) {

        double x1 = p.getElem(i).getX1();
        double x2 = p.getElem(i).getX2();

        double fitness;

        switch (option) {
            case 1:
                fitness = f1(x1, x2);
                break;
            case 2:
                fitness = f2(x1, x2);
                break;
        }

        mean += fitness;

        p.setElemFitness(i, fitness);
    }

    mean /= p.getSize();

    // Calculate variance of fitness in population

    for (int i = 0; i < p.getSize(); i++) {

        variance += (p.getElem(i).getFitness() - mean)*(p.getElem(i).getFitness() - mean);
    }

    variance /= (p.getSize()-1);

    p.setVariance(variance);
}
