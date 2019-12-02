#include <bits/stdc++.h>
#include <random>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cairo.h>
#include <cairo-xlib.h>

#include "Plot.hpp"
#include "ASearch.hpp"
#include "Program.hpp"

using namespace std;

// Constructor

Program::Program(int width_p, int height_p, vector<vector<double> > world) :
    width(width_p), height(height_p), aSearch(world), plot(width_p, height_p) {}

// Methods

void Program::run(){

    initialize(aSearch.getWorld());

    aSearch.search(start_pos, end_pos);

    aSearch.printPath();

    path = aSearch.getPath();

    plot.paint(start_pos, end_pos, path, aSearch.getWorld());

    /*
        left: 65361
        right: 65363
        up: 65362
        down: 65364

        left-up: 113
        right-up: 119
        left-down: 97
        right-down: 115
    */

    while(1){

        int key;

        key = plot.checkEvent(1);

        if ( key == 65361 ) {

            if ( validateMove(-1, 0) ) {

                cout << "left\n" << endl;

                end_pos.first = end_pos.first-1;

                aSearch.search(start_pos, end_pos);

                cout << "\n New path\n" << endl;

                aSearch.printPath();

                path = aSearch.getPath();

                plot.paint(start_pos, end_pos, path, aSearch.getWorld());
            }
        }

        else if ( key == 65363 ) {

            if ( validateMove(1, 0) ) {

                cout << "Right\n" << endl;

                end_pos.first = end_pos.first+1;

                aSearch.search(start_pos, end_pos);

                cout << "\n New path\n" << endl;

                aSearch.printPath();

                path = aSearch.getPath();

                plot.paint(start_pos, end_pos, path, aSearch.getWorld());
            }
        }

        else if ( key == 65362 ) {

            if ( validateMove(0, -1) ) {

                cout << "Up\n" << endl;

                end_pos.second = end_pos.second-1;

                aSearch.search(start_pos, end_pos);

                cout << "\n New path\n" << endl;

                aSearch.printPath();

                path = aSearch.getPath();

                plot.paint(start_pos, end_pos, path, aSearch.getWorld());
            }
        }

        else if ( key == 65364 ) {

            if ( validateMove(0, 1) ) {

                cout << "Down\n" << endl;

                end_pos.second = end_pos.second+1;

                aSearch.search(start_pos, end_pos);

                cout << "\n New path\n" << endl;

                aSearch.printPath();

                path = aSearch.getPath();

                plot.paint(start_pos, end_pos, path, aSearch.getWorld());
            }
        }

        else if ( key == 113 ) {

            if ( validateMove(-1, -1) ) {

                cout << "Left-Up\n" << endl;

                end_pos.first = end_pos.first-1;
                end_pos.second = end_pos.second-1;

                aSearch.search(start_pos, end_pos);

                cout << "\n New path\n" << endl;

                aSearch.printPath();

                path = aSearch.getPath();

                plot.paint(start_pos, end_pos, path, aSearch.getWorld());
            }
        }

        else if ( key == 119 ) {

            if ( validateMove(1, -1) ) {

                cout << "Right-Up\n" << endl;

                end_pos.first = end_pos.first+1;
                end_pos.second = end_pos.second-1;

                aSearch.search(start_pos, end_pos);

                cout << "\n New path\n" << endl;

                aSearch.printPath();

                path = aSearch.getPath();

                plot.paint(start_pos, end_pos, path, aSearch.getWorld());
            }
        }

        else if ( key == 97 ) {

            if ( validateMove(-1, 1) ) {

                cout << "Left-Down\n" << endl;

                end_pos.first = end_pos.first-1;
                end_pos.second = end_pos.second+1;

                aSearch.search(start_pos, end_pos);

                cout << "\n New path\n" << endl;

                aSearch.printPath();

                path = aSearch.getPath();

                plot.paint(start_pos, end_pos, path, aSearch.getWorld());
            }
        }

        else if ( key == 115 ) {

            if ( validateMove(1, 1) ) {

                cout << "Right-Down\n" << endl;

                end_pos.first = end_pos.first+1;
                end_pos.second = end_pos.second+1;

                aSearch.search(start_pos, end_pos);

                cout << "\n New path\n" << endl;

                aSearch.printPath();

                path = aSearch.getPath();

                plot.paint(start_pos, end_pos, path, aSearch.getWorld());
            }
        }

        else if ( key == 65307 ) {

            exit(1);
        }

        cout << "\n\n---------------------------------------------------------------\n\n";
    }

    plot.close();
}

void Program::initialize(vector<vector<double> > world){

    for (int i = 0; i < world.size(); i++) {

        for (int j = 0; j < world[0].size(); j++) {

            if ( world[i][j] != 0 ) {

                available.push_back(make_pair(i, j));
            }
        }
    }

    // Random initial and end positon

    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, available.size());

    // Random initial position

    int start_index = distr(eng);
    int start_x = available[start_index].first;
    int start_y = available[start_index].second;

    start_pos.first = start_x;
    start_pos.second = start_y;

    available.erase(available.begin() + start_index);

    // Random final position

    int end_index = distr(eng);
    int end_x = available[end_index].first;
    int end_y = available[end_index].second;

    end_pos.first = end_x;
    end_pos.second = end_y;
}

bool Program::validateMove(int x, int y){

    int new_x = end_pos.first+x;
    int new_y = end_pos.second+y;

    if ( (new_x == start_pos.first) and (new_y == start_pos.second) ) {

        return false;
    }

    for (int i = 0; i < available.size(); i++) {

        if ( (new_x == available[i].first) and (new_y == available[i].second) ) {

            cout << "\nNew start_pos: " << new_y << ", " << new_x << endl;

            return true;
        }
    }

    return false;
}

// Getters



// Setters
