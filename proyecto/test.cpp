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

// g++ -std=c++11 ASearch.cpp Cell.cpp Plot.cpp Program.cpp test.cpp -o test -lcairo $(pkg-config xext x11 cairo-xlib-xrender --cflags --libs) && ./test

int main(int argc, char const *argv[]) {

    /*
    vector<vector<double> > world = {

        { 1, 0, 0, 1, 0, 2 },
        { 1, 1, 2, 2.5, 1, 1 },
        { 1, 0, 0, 1, 1, 1 },
        { 2.5, 1, 1, 0, 2.5, 1 },
        { 1, 0, 2, 1, 2, 0 },
        { 1, 1, 2, 1, 1, 1 }
    };
    */

    /*
    vector<vector<double> > world = {

        { 1, 1, 1, 1, 1, 2, 1, 1, 1 },
        { 1, 1, 2, 2.5, 1, 1, 1, 1, 1 },
        { 1, 1, 0, 0, 0, 0, 0, 1, 1 },
        { 2.5, 1, 1, 1, 2.5, 1, 0, 1, 1 },
        { 1, 1, 1, 1, 2, 1, 0, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 0, 1, 1 },
        { 1, 1, 0, 0, 0, 0, 0, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };
    */

    /*
    vector<vector<double> > world = {

        { 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 2, 2.5, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
        { 2.5, 1, 1, 1, 2.5, 1, 0, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
        { 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 2.5 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 2.5, 1, 1, 1, 1, 1, 1 },
        { 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2.5, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1 },
        { 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1 }
    };
    */

    random_device rd;
    mt19937 eng(rd());
    uniform_real_distribution<> distr(0, 1);

    int w = 20;
    int h = 20;

    vector<vector<double> > world;
    world.resize(w, vector<double>(h, 0));

    for (int i = 0; i < w; i++) {

        for (int j = 0; j < h; j++) {

            double val = distr(eng);

            if ( val < 0.1 ) {

                world[i][j] = 0.0;
            }

            else if ( val < 0.5 ) {

                world[i][j] = 1.0;
            }

            else if ( val < 0.75 ) {

                world[i][j] = 2.0;
            }

            else {

                world[i][j] = 2.5;
            }
        }
    }

    Program p = Program(600, 600, world);
    p.run();

    return 0;
}
