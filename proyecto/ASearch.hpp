#ifndef ASEARCH_HPP
#define ASEARCH_HPP

#include <bits/stdc++.h>
#include <string.h>
#include "Cell.hpp"

using namespace std;

class ASearch {

private:

    priority_queue<Cell> openList;
    vector<vector<bool> > closed;
    vector<vector<bool> > frontier;
    vector<vector<Cell> > cell_state;
    vector<pair<int, int> > path;

    pair<int, int> start_pos;
    pair<int, int> end_pos;

    vector<int> x_neighbours;
    vector<int> y_neighbours;

public:

    // Constructor

    ASearch(pair<int, int> start_pos_p, pair<int, int> end_pos_p);

    // Methods

    void search(vector<vector<double> > world);

    void initCellState(int x_size, int y_size);

    double estimateH(Cell neighbour);

    void printPath();

    // Getters

    vector<pair<int, int> > getPath();

    // Setters



};

#endif
