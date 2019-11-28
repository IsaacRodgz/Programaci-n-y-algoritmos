#ifndef CELL_HPP
#define CELL_HPP

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Cell {

private:

    pair<int, int> parent;
    pair<int, int> location;
    double rank;
    double g;
    double h;

public:

    // Constructor

    Cell(int x_coord, int y_coord, double rank_p);

    // Methods



    // Getters

    double getRank() const;

    double getG();

    double getX();

    double getY();

    // Setters



};

#endif
