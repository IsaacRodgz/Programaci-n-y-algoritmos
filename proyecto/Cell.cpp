#include <math.h>
#include <bits/stdc++.h>

#include "Cell.hpp"

using namespace std;

// Constructor

Cell::Cell(int x_coord, int y_coord, double rank_p) : rank(rank_p), g(0), h(0) {

    location = make_pair(x_coord, y_coord);
    parent = make_pair(-1, -1);
}

// Methods



// Getters

double Cell::getRank() const{

    return rank;
}

double Cell::getG(){

    return g;
}

double Cell::getX(){

    return location.first;
}

double Cell::getY(){

    return location.second;
}

// Setters
