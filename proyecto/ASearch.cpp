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

    bool found = false;

    while( !open.empty() ){

        // Remove item with lowest f value from open

        Cell* current = open.front();
        pop_heap(open.begin(), open.end());
        open.pop_back();

        current_x = (*current).getX();
        current_y = (*current).getY();

        // Add current to closed set

        cout << "\nCurrent" << endl;
        cout << "\n Coords: " << current_x << " " << current_y << "\n" << endl;

        closed[current_x][current_y] = true;

        // Iterate thorugh neighbours of current

        cout << "\nNeighbours:" << endl;

        for (int i = 0; i < x_neighbours.size(); i++) {

            int neigh_x = current_x + x_neighbours[i];
            int neigh_y = current_y + y_neighbours[i];

            // Check if neighbour is valid

            if ( neigh_x >= 0 and neigh_x < world.size() and neigh_y >= 0 and neigh_y < world[0].size() and world[neigh_x][neigh_y] == 1 ) {

                // Check if current is the goal

                if ( current_x == end_pos.first and current_y == end_pos.second ) {

                    cell_state[neigh_x][neigh_y].setParent(current_x, current_y);

                    cout << "\n Goal found\n" << endl;

                    found = true;
                }

                double new_cost = (*current).getG() + 1.0;

                if ( frontier[neigh_x][neigh_y] == false or new_cost < cell_state[neigh_x][neigh_y].getG()) {

                    cout << "\n Coords: " << neigh_x << " " << neigh_y << "\n" << endl;

                    cell_state[neigh_x][neigh_y].setG(new_cost);

                    double priority = new_cost + estimateH(cell_state[neigh_x][neigh_y]);

                    cell_state[neigh_x][neigh_y].setParent(current_x, current_y);

                    cell_state[neigh_x][neigh_y].setF(priority);

                    open.push_back(&cell_state[neigh_x][neigh_y]);

                    push_heap(open.begin(), open.end());

                    frontier[neigh_x][neigh_y] = true;

                    cout << "  priority_new: " << priority << "\n" << endl;

                    for (int i = 0; i < open.size(); i++) {

                        cout << "  priority: " << (*open[i]).getF() << endl;
                        cout << "  Min in heap: " << (*open[i]).getX() << " " << (*open[i]).getY() << endl;
                    }
                    cout << endl;
                }
            }

            if (found == true) {

                break;
            }
        }

        if (found == true) {

            break;
        }
    }

    int b = 0;

    while ( current_x != start_pos.first and current_y != start_pos.second ) {

        b++;

        cout << "\n Coords: " << current_x << " " << current_y << "\n" << endl;

        current_x = cell_state[current_x][current_y].getParentX();
        current_x = cell_state[current_x][current_y].getParentY();

        if(b > 20)
            break;
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

    double diffx = neighbour.getX() - end_pos.first;
    double diffy = neighbour.getY() - end_pos.second;


    return sqrt(diffx*diffx + diffy*diffy);
}

// Getters



// Setters
