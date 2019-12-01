#ifndef PLOT_HPP
#define PLOT_HPP

#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <X11/extensions/shape.h>

using namespace std;

class Plot {

private:

    int w;
    int h;

    cairo_surface_t *surface;
    cairo_t *cr;
    Display *dpy;
    cairo_surface_t *shape_surface;
    cairo_t *shape_cairo;
    Pixmap shape;

    vector<vector<double> > world;
    vector<pair<int, int> > path;
    pair<int, int> start_pos;
    pair<int, int> end_pos;

public:

    Plot(vector<vector<double> > world_p, vector<pair<int, int> > path_p, pair<int, int> start_pos_p, pair<int, int> end_pos_p);

    void plot();

    void paint();

    void shapeit();

};

#endif
