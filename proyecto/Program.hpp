#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cairo.h>
#include <cairo-xlib.h>

#include "Plot.hpp"
#include "ASearch.hpp"

using namespace std;

class Program {

private:

    int width;
    int height;

    Plot plot;
    ASearch aSearch;
    vector<pair<int, int> > available;

    pair<int, int> start_pos;
    pair<int, int> end_pos;
    vector<pair<int, int> > path;


public:

    // Constructor

    Program(int width_p, int height_p, vector<vector<double> > world);

    void run();

    void initialize(vector<vector<double> > world);

    bool validateMove(int x, int y);

};

#endif
