#include <iostream>
#include<bits/stdc++.h>
#include "Program.hpp"
#include "ASearch.hpp"
#include "Plot.hpp"
#include <random>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cairo.h>
#include <cairo-xlib.h>

using namespace std;

// g++ -std=c++11 ASearch.cpp Cell.cpp Plot.cpp test.cpp -o test -lcairo $(pkg-config xext x11 cairo-xlib-xrender --cflags --libs) && ./test

void test_ASearch(){

    /*
    vector<vector<int> > world = {

        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
    };
    */

    /*
    vector<vector<double> > world = {

        { 1, 0, 0, 0 },
        { 1, 1, 2, 2.5 },
        { 1, 0, 0, 1 },
        { 1, 1, 1, 1 }
    };
    */

    /*
    vector<vector<double> > world = {

        { 1, 0, 0, 1, 0 },
        { 1, 1, 2, 2.5, 1 },
        { 1, 0, 0, 1, 1 },
        { 2.5, 1, 1, 1, 1 },
        { 1, 1, 2, 1, 1 }
    };
    */

    /*
    vector<vector<double> > world = {

        { 1, 0, 0, 1, 0, 2 },
        { 1, 1, 2, 2.5, 1, 1 },
        { 1, 0, 0, 1, 1, 1 },
        { 2.5, 1, 1, 0, 2.5, 1 },
        { 1, 0, 2, 1, 2, 0 },
        { 1, 1, 2, 1, 1, 1 }
    };

    vector<pair<int, int> > available;

    for (int i = 0; i < world.size(); i++) {

        for (int j = 0; j < world[0].size(); j++) {

            if ( world[i][j] == 1 ) {

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

    pair<int, int> start_pos(start_x, start_y);

    available.erase(available.begin() + start_index);

    // Random final position

    int end_index = distr(eng);
    int end_x = available[end_index].first;
    int end_y = available[end_index].second;

    pair<int, int> end_pos(end_x, end_y);

    // Search for best path

    cout << "\nInitial position: " << start_pos.second << " , " << start_pos.first << endl;
    cout << "\nFinal position: " << end_pos.second << " , " << end_pos.first << endl;

    ASearch aSearch(start_pos, end_pos);

    aSearch.search(world);

    cout << "\n Solution: \n" << endl;

    aSearch.printPath();

    // Plot window with world matrix and solution found

    Plot p = Plot(world, aSearch.getPath(), start_pos, end_pos);
    p.plot();
    */
}

int main(int argc, char const *argv[]) {

    vector<vector<double> > world = {

        { 1, 0, 0, 1, 0, 2 },
        { 1, 1, 2, 2.5, 1, 1 },
        { 1, 0, 0, 1, 1, 1 },
        { 2.5, 1, 1, 0, 2.5, 1 },
        { 1, 0, 2, 1, 2, 0 },
        { 1, 1, 2, 1, 1, 1 }
    };

    Program p = Program(600, 600, world);
    p.run();

    return 0;
}
