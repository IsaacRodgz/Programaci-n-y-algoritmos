#include "Genetic_Ops.h"
#include "Population.h"
#include "Selection.h"

#include <bits/stdc++.h>
#include <string.h>
#include <random>

using namespace std;

// Mutate()

void GeneticOps::crossOver(Population& p){

    vector<Organism> new_pop;

    p.setSize(p.getSizeO());

    for (int i = 0; i < p.getSize(); i++) {

        new_pop.push_back(p.createOrganism());
    }

    p.setPopulation(new_pop);
}

void GeneticOps::select(int method, Population& p, double percentage){

    Selection::ranking(p, percentage);
}
