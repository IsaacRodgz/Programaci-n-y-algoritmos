#include "Genetic_Ops.h"
#include "Population.h"
#include "Selection.h"

#include <bits/stdc++.h>
#include <string.h>
#include <random>

using namespace std;

// CrossOver()

// Mutate()

void GeneticOps::select(int method, Population p, double percentage){

    Selection::ranking(p, percentage);
}
