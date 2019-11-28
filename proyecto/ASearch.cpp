#include <math.h>
#include <bits/stdc++.h>
#include "ASearch.hpp"
#include "Cell.hpp"

using namespace std;

// Constructor

ASearch::ASearch(pair<int, int> start_pos_p, pair<int, int> end_pos_p) : start_pos(start_pos_p), end_pos(end_pos_p) {

    x_neighbours = { -1, 0, 1, -1, 1, -1, 0, 1 };
    y_neighbours = { -1, -1, -1, 0, 0, 1, 1, 1 };
}

// Methods

void ASearch::search(vector<vector<int> > world){

    frontier.resize(world.size(), vector<bool>(world[0].size(), false));
    closed.resize(world.size(), vector<bool>(world[0].size(), false));

    //cout << "\n world dims: " << world.size() << " " << world[0].size() << "\n" << endl;
    //cout << "\n frontier dims: " << frontier.size() << " " << frontier[0].size() << "\n" << endl;
    //cout << "\n closed dims: " << closed.size() << " " << closed[0].size() << "\n" << endl;

    initCellState(world.size(), world[0].size());

    int init_x = start_pos.first;
    int init_y = start_pos.second;

    open.push_back(&cell_state[init_x][init_y]);
    frontier[init_x][init_y] = true;

    make_heap(open.begin(), open.end());

    int current_x;
    int current_y;

    while( !open.empty() ){

        // Remove item with lowest f value from open

        Cell* current = open.front();
        pop_heap(open.begin(), open.end());
        open.pop_back();

        current_x = (*current).getX();
        current_y = (*current).getY();

        // Add current to closed set

        //cout << "\nCurrent" << endl;
        //cout << "\n Coords: " << current_x << " " << current_y << "\n" << endl;

        closed[current_x][current_y] = true;

        // Check if current is the goal

        if ( current_x == end_pos.first and current_y == end_pos.second ) {

            cout << "\n Goal found\n" << endl;
            break;
        }

        // Iterate thorugh neighbours of current

        //cout << "\nNeighbours:" << endl;

        for (int i = 0; i < x_neighbours.size(); i++) {

            int neigh_x = current_x + x_neighbours[i];
            int neigh_y = current_y + y_neighbours[i];

            // Check if neighbour is valid

            if ( neigh_x >= 0 and neigh_x < world.size() and neigh_y >= 0 and neigh_y < world[0].size() and world[neigh_x][neigh_y] == 1 ) {

                //cout << "\n Coords: " << neigh_x << " " << neigh_y << "\n" << endl;

                double new_cost = (*current).getG() + 1.0;

                if ( frontier[neigh_x][neigh_y] == false or new_cost < cell_state[neigh_x][neigh_y].getG()) {

                    cell_state[neigh_x][neigh_y].setG(new_cost);

                    double priority = new_cost + estimateH(cell_state[neigh_x][neigh_y]);

                    cell_state[neigh_x][neigh_y].setParent(current_x, current_y);

                    cell_state[neigh_x][neigh_y].setF(priority);

                    open.push_back(&cell_state[neigh_x][neigh_y]);

                    make_heap(open.begin(), open.end());

                    frontier[neigh_x][neigh_y] = true;
                }
            }
        }
    }

    while ( current_x != start_pos.first and current_y != start_pos.second ) {

        cout << "\n Coords: " << current_x << " " << current_y << "\n" << endl;

        current_x = cell_state[current_x][current_y].getParentX();
        current_x = cell_state[current_x][current_y].getParentY();
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

double ASearch::estimateH(Cell neighbour){

    // Euclidean distance

    return 0.0;
}

// Getters



// Setters
