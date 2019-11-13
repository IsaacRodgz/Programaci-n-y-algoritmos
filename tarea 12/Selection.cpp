#include "Selection.h"
#include "Organism.h"
#include "Population.h"

#include <bits/stdc++.h>
#include <string.h>
#include <random>

using namespace std;

struct compare {

    inline bool operator() (const Organism& org1, const Organism& org2) {

        return (org1.getFitness() > org2.getFitness());
    }
};

void Selection::ranking(Population p, double percentage){

    int size = p.getSize();

    vector<Organism> p_new = p.getPopulation();

    sort(p_new.begin(), p_new.end(), compare());

    vector<Organism> sub(p_new.begin(), p_new.begin() + (int)(percentage*size));

    p.setPopulation(sub);
    p.setSize(sub.size());
}
