#include <math.h>
#include <bits/stdc++.h>
#include "ASearch.hpp"
#include "Cell.hpp"

using namespace std;

bool operator<(const Cell& c1, const Cell& c2) {

    return c1.getF() > c2.getF();
}

// Constructor

ASearch::ASearch(vector<vector<double> > world_p) : world(world_p) {

    x_neighbours = { -1, 0, 1, -1, 1, -1, 0, 1 };
    y_neighbours = { -1, -1, -1, 0, 0, 1, 1, 1 };
}

// Methods

void ASearch::search(pair<int, int> start_pos, pair<int, int> end_pos){

    reset();

    frontier.resize(world.size(), vector<bool>(world[0].size(), false));
    closed.resize(world.size(), vector<bool>(world[0].size(), false));

    //cout << "\n world dims: " << world.size() << " " << world[0].size() << "\n" << endl;
    //cout << "\n frontier dims: " << frontier.size() << " " << frontier[0].size() << "\n" << endl;
    //cout << "\n closed dims: " << closed.size() << " " << closed[0].size() << "\n" << endl;

    initCellState(world.size(), world[0].size());

    int init_x = start_pos.first;
    int init_y = start_pos.second;

    openList.push(cell_state[init_x][init_y]);
    frontier[init_x][init_y] = true;

    int current_x;
    int current_y;

    bool found = false;

    while( !openList.empty() ){

        // Remove item with lowest f value from open

        Cell current = openList.top();
        openList.pop();

        current_x = current.getX();
        current_y = current.getY();

        // Add current to closed set

        //cout << "\nCurrent" << endl;
        //cout << "\n Coords: " << current_x << " " << current_y << "\n" << endl;

        if ( closed[current_x][current_y] == true ) {

            continue;
        }

        else {

            closed[current_x][current_y] == true;
        }

        // Iterate thorugh neighbours of current

        //cout << "\nNeighbours:" << endl;

        for (int i = 0; i < x_neighbours.size(); i++) {

            int neigh_x = current_x + x_neighbours[i];
            int neigh_y = current_y + y_neighbours[i];

            // Check if neighbour is valid

            if ( neigh_x >= 0 and neigh_x < world.size() and neigh_y >= 0 and neigh_y < world[0].size() and world[neigh_x][neigh_y] != 0 and closed[current_x][current_y] == false ) {

                // Check if current is the goal

                if ( neigh_x == end_pos.first and neigh_y == end_pos.second ) {

                    cell_state[neigh_x][neigh_y].setParent(current_x, current_y);

                    current_x = neigh_x;
                    current_y = neigh_y;

                    cout << "\n Goal found\n" << endl;

                    found = true;
                }

                // Goal found, break for cicle

                if (found == true) {

                    break;
                }

                // If movement is diagonal only penalization is moving from one cell to another

                double new_cost;

                if ( neigh_x != current_x and neigh_y != current_y ) {

                    new_cost = current.getG() + world[neigh_x][neigh_y];
                }

                // Else add penalization specific to neighbour cell

                else {

                    new_cost = current.getG() + world[neigh_x][neigh_y];
                }

                if ( frontier[neigh_x][neigh_y] == false or new_cost < cell_state[neigh_x][neigh_y].getG()) {

                    //cout << "\n Coords: " << neigh_x << " " << neigh_y << "\n" << endl;

                    cell_state[neigh_x][neigh_y].setG(new_cost);

                    double priority = new_cost + estimateHDiagonal(cell_state[neigh_x][neigh_y], end_pos);

                    cell_state[neigh_x][neigh_y].setParent(current_x, current_y);

                    cell_state[neigh_x][neigh_y].setF(priority);

                    openList.push(cell_state[neigh_x][neigh_y]);

                    frontier[neigh_x][neigh_y] = true;

                    //cout << "\n Parent of: " << neigh_x << " " << neigh_y;
                    //cout << "\n is : " << cell_state[neigh_x][neigh_y].getParentX() << " " << cell_state[neigh_x][neigh_y].getParentY() << endl;

                    //cout << "  priority_new: " << priority << "\n" << endl;

                    //cout << "  priority: " << (*open[i]).getF() << endl;
                    //cout << "  Min in heap: " << (*open[i]).getX() << " " << (*open[i]).getY() << endl;

                    //cout << endl;
                }
            }
        }

        // Goal found, break while cicle

        if (found == true) {

            break;
        }
    }

    // Recover path in order from beggining to end

    int next_x = cell_state[end_pos.first][end_pos.second].getX();
    int next_y = cell_state[end_pos.first][end_pos.second].getY();

    stack<pair<int, int> > path_stack;

    while ( next_x != -1 and next_y != -1 ) {

        int current_x = next_x;
        int current_y = next_y;

        path_stack.push(make_pair(current_x, current_y));

        next_x = cell_state[current_x][current_y].getParentX();
        next_y = cell_state[current_x][current_y].getParentY();
    }

    while ( !path_stack.empty() ) {

        pair<int, int> current = path_stack.top();path_stack.pop();

        path.push_back(current);
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

double ASearch::estimateHEuclidean(Cell neighbour, pair<int, int> end_pos){

    double diffx = neighbour.getX() - end_pos.first;
    double diffy = neighbour.getY() - end_pos.second;


    return sqrt(diffx*diffx + diffy*diffy);
}

double ASearch::estimateHDiagonal(Cell neighbour, pair<int, int> end_pos){

    double diffx = fabs(neighbour.getX() - end_pos.first);
    double diffy = fabs(neighbour.getY() - end_pos.second);


    return max(diffx, diffy);
}

void ASearch::printPath(){

    for (int i = 0; i < path.size(); i++) {

        cout << "  x: " << path[i].second << ", y: " << path[i].first << "\n" << endl;
    }
}

void ASearch::reset(){

    frontier.clear();
    closed.clear();
    cell_state.clear();
    path.clear();

    while (!openList.empty()){

        openList.pop();
    }
}

// Getters

vector<pair<int, int> > ASearch::getPath(){

    return path;
}

vector<vector<double> > ASearch::getWorld(){

    return world;
}

// Setters
