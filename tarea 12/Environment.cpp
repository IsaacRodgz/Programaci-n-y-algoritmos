#include "Environment.h"
#include "Population.h"

#include <math.h>
#include <bits/stdc++.h>

using namespace std;

double Environment::f1(double x1, double x2){

    return 0.2*x1*x1 + 0.2*x2*x2 - 5*cos(x1 + x2) + 2;
}

double Environment::f2(double x1, double x2){

    return cos(x1)*cos(x2);
}

void Environment::evaluate(Population& p, int option){

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

        p.setElemFitness(i, fitness);

    }
}
