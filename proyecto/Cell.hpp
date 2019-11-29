#ifndef CELL_HPP
#define CELL_HPP

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Cell {

private:

    pair<int, int> parent;
    pair<int, int> location;
    double f;
    double g;
    double h;

public:

    // Constructor

    Cell(int x_coord, int y_coord, double f_p);

    // Methods

    

    // Getters

    double getF() const;

    double getG();

    int getX();

    int getY();

    int getParentX();

    int getParentY();

    // Setters

    void setG(double new_cost);

    void setF(double new_priority);

    void setParent(int x_coord, int y_coord);

};

#endif
