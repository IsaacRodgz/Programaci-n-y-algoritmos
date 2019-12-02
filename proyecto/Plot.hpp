#ifndef PLOT_HPP
#define PLOT_HPP

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cairo.h>
#include <cairo-xlib.h>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Plot {

private:

    int w;
    int h;

    cairo_surface_t *sfc;
    cairo_t *cr;
    cairo_surface_t *shape_surface;
    cairo_t *shape_cairo;
    Pixmap shape;

public:

    Plot(int width_p, int height_p);

    void cairo_create_x11_surface();

    int checkEvent(int block);

    void close();

    void paint(pair<int, int> start_pos, pair<int, int> end_pos, vector<pair<int, int> > path, vector<vector<double> > world);

};

#endif
