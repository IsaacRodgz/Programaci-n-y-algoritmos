#include <math.h>
#include <bits/stdc++.h>

#include "Cell.hpp"

using namespace std;

// Constructor

Cell::Cell(int x_coord, int y_coord, double f_p) : f(f_p), g(0), h(0) {

    location = make_pair(x_coord, y_coord);
    parent = make_pair(-1, -1);
}

// Methods



// Getters

double Cell::getF(){

    return f;
}

double Cell::getG(){

    return g;
}

int Cell::getX(){

    return location.first;
}

int Cell::getY(){

    return location.second;
}

int Cell::getParentX(){

    return parent.first;
}

int Cell::getParentY(){

    return parent.second;
}

// Setters

void Cell::setG(double new_cost){

    g = new_cost;
}

void Cell::setF(double new_priority){

    f = new_priority;
}

void Cell::setParent(int x_coord, int y_coord){

    parent = make_pair(x_coord, y_coord);
}
