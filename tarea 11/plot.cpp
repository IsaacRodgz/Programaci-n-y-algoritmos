#include <iostream>
#include <cairo.h>
#include <bits/stdc++.h>
# define PI 3.14159265359
using namespace std;

// g++ -std=c++11 visvalingam.cpp plot.cpp test2.cpp -o test -lcairo && ./test

void plot(){

    int w = 200;
    int h = 200;

    int size = 4;
    int x[] = {10, 50, 90, 140};
    int y[] = {10, 50, 25, 95};

    cairo_surface_t *surface;
    cairo_t *cr;
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
    cr = cairo_create(surface);

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint_with_alpha (cr, 1);
    cairo_stroke(cr);

    double radius = 2;
    cairo_set_source_rgb(cr, 1, 0, 0);

    for (size_t i = 0; i < size; i++) {

        cairo_arc(cr, x[i], y[i], radius, 0, 2*PI);
        cairo_fill(cr);
    }
    cairo_stroke(cr);

    double line_width = 1;
    cairo_set_line_width(cr, line_width);
    cairo_set_source_rgb(cr, 0, 0, 1);

    for (size_t i = 0; i < size; i++) {

        cairo_line_to(cr, x[i], y[i]);
    }
    cairo_stroke(cr);

    cairo_surface_write_to_png(surface, "image.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
