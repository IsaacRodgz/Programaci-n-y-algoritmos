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


    vector<vector<double> > world = {

        { 1, 0, 0, 1, 0, 2 },
        { 1, 1, 2, 2.5, 1, 1 },
        { 1, 0, 0, 1, 1, 1 },
        { 2.5, 1, 1, 0, 2.5, 1 },
        { 1, 0, 2, 1, 2, 0 },
        { 1, 1, 2, 1, 1, 1 }
    };


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
    Program p = Program(600, 600, world);
    p.run();

    return 0;
}
