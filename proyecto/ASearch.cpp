#include <math.h>
#include <bits/stdc++.h>
#include "ASearch.hpp"
#include "Cell.hpp"

using namespace std;

inline bool operator<(const Cell& c1, const Cell& c2) {

    return c1.getRank() < c2.getRank();
}

// Constructor

ASearch::ASearch(pair<int, int> start_pos_p, pair<int, int> end_pos_p) : start_pos(start_pos_p), end_pos(end_pos_p) {

    x_neighbours = { -1, 0, 1, -1, 1, -1, 0, 1 };
    y_neighbours = { -1, -1, -1, 0, 0, 1, 1, 1 };
}

// Methods

void ASearch::search(vector<vector<int> > world){

    closed.resize(world.size(), vector<bool>(world[0].size(), false));

    initCellState(world.size(), world[0].size());

    while( !open.empty() ){

        // Remove lowest rank item from open

        Cell current = open.top();open.pop();
        int current_x = current.getX();
        int current_y = current.getY();

        // Add current to closed set

        closed[current_x][current_y] = true;

        // Iterate thorugh neighbours of current

        for (int i = 0; i < x_neighbours.size(); i++) {

            int neigh_x = x_neighbours[i];
            int neigh_y = y_neighbours[i];

            double cost = current.getG() + 1.0;

        }
    }
}

void ASearch::initCellState(int x_size, int y_size){

    vector<Cell> row;

    for (int i = 0; i < x_size; i++) {

        for (int j = 0; j < y_size; j++) {

            row.push_back(Cell(i, j, 0.0));
        }

        cell_state.push_back(row);

        row.clear();
    }
}

double ASearch::estimateH(Cell current, Cell neighbour){

    // Euclidean distance

    return 0.0;
}

// Getters



// Setters
