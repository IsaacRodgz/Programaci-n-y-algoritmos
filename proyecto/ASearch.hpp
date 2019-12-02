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
    vector<vector<double> > world;

    vector<int> x_neighbours;
    vector<int> y_neighbours;

public:

    // Constructor

    ASearch(vector<vector<double> > world_p);

    // Methods

    void search(pair<int, int> start_pos, pair<int, int> end_pos);

    void initCellState(int x_size, int y_size);

    double estimateHEuclidean(Cell neighbour, pair<int, int> end_pos);

    double estimateHDiagonal(Cell neighbour, pair<int, int> end_pos);

    void printPath();

    void reset();

    // Getters

    vector<pair<int, int> > getPath();

    vector<vector<double> > getWorld();

    // Setters



};

#endif
