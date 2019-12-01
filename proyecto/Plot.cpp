#include <math.h>
#include <bits/stdc++.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <X11/extensions/shape.h>

#include "Plot.hpp"
# define PI 3.14159265359

using namespace std;

Plot::Plot(vector<vector<double> > world_p, vector<pair<int, int> > path_p, pair<int, int> start_pos_p, pair<int, int> end_pos_p) :
    w(600), h(600), world(world_p), path(path_p), start_pos(start_pos_p), end_pos(end_pos_p) {}

void Plot::plot(){

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        fprintf(stderr, "Error: Can't open display. Is DISPLAY set?\n");
    }

    Window win;
    win = XCreateSimpleWindow(dpy, RootWindow(dpy, 0), 400, 100, w, h, 0, 0, BlackPixel(dpy, 0));
    XSetWindowAttributes winattr;
    winattr.override_redirect = 1;
    XChangeWindowAttributes(dpy, win, CWOverrideRedirect, &winattr);

    XSelectInput(dpy, win, StructureNotifyMask | ExposureMask);
    XMapWindow(dpy, win);

    surface = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), w, h);
    cr = cairo_create(surface);

    shape = XCreatePixmap(dpy, win, w, h, 1);
    shape_surface = cairo_xlib_surface_create_for_bitmap(dpy, shape, DefaultScreenOfDisplay(dpy), w, h);

    shape_cairo = cairo_create(shape_surface);

    paint();

    shapeit();

    while (1) {

        
    }
}

void Plot::paint(){

    // Background color

    cairo_pattern_t *pat;
    pat = cairo_pattern_create_linear(w/2, 0.0, w/2, h);
    cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.9, 0.9, 0.9);
    cairo_pattern_add_color_stop_rgb(pat, 1.0, 0.6, 0.6, 0.6);
    cairo_rectangle(cr, 0, 0, w, h);
    cairo_set_source(cr, pat);
    cairo_fill(cr);


    // Draw axis

    // min y max de (x, y)

    double xmax = world[0].size();
    double xmin = 0;

    double ymax = world.size();
    double ymin = 0;

    double ejex = w - w/8;
    double ejey = h/8;
    double origenx = w/8;
    double origeny = h - h/8;

    double metrica_ejex = (ejex - origenx)/world[0].size();
    double metrica_ejey = (origeny - ejey)/world.size();

    // Draw predator

    int w_predator, h_predator;
    cairo_surface_t *predator;

    cairo_save(cr);
    predator = cairo_image_surface_create_from_png ("predator.png");
    w_predator = cairo_image_surface_get_width (predator);
    h_predator = cairo_image_surface_get_height (predator);
    cairo_translate (cr, origenx + (start_pos.first)*metrica_ejex, origeny - (world.size()-start_pos.second)*metrica_ejey);
    cairo_scale  (cr, metrica_ejex/double(w_predator), metrica_ejey/double(h_predator));
    cairo_set_source_surface (cr, predator, 0, 0);
    cairo_paint (cr);
    cairo_surface_destroy (predator);
    cairo_restore(cr);

    // Draw prey

    int w_prey, h_prey;
    cairo_surface_t *prey;

    cairo_save(cr);
    prey = cairo_image_surface_create_from_png ("prey.png");
    w_prey = cairo_image_surface_get_width (prey);
    h_prey = cairo_image_surface_get_height (prey);
    cairo_translate (cr, origenx + (end_pos.first)*metrica_ejex, origeny - (world.size()-end_pos.second)*metrica_ejey);
    cairo_scale  (cr, metrica_ejex/double(w_prey), metrica_ejey/double(h_prey));
    cairo_set_source_surface (cr, prey, 0, 0);
    cairo_paint (cr);
    cairo_surface_destroy (prey);
    cairo_restore(cr);

    // Color rest of the cells

    for (int i = 1; i < world.size()+1; i++) {

        for (int j = 0; j < world[0].size(); j++) {

            if ( (j != start_pos.first and (i-1) != start_pos.second) or (j != end_pos.first and (i-1) != end_pos.second) ) {

                double x_left = origenx + j*metrica_ejex;
                double y_upper = origeny - i*metrica_ejey;

                if ( world[j][world.size()-i] == 0 ) {

                    int w_water, h_water;
                    cairo_surface_t *water;

                    cairo_save(cr);
                    water = cairo_image_surface_create_from_png ("water.png");
                    w_water = cairo_image_surface_get_width (water);
                    h_water = cairo_image_surface_get_height (water);
                    cairo_translate (cr, origenx + j*metrica_ejex, origeny - i*metrica_ejey);
                    cairo_scale  (cr, metrica_ejex/double(w_water), metrica_ejey/double(h_water));
                    cairo_set_source_surface (cr, water, 0, 0);
                    cairo_paint (cr);
                    cairo_surface_destroy (water);
                    cairo_restore(cr);
                }

                else if( world[j][world.size()-i] == 1 ) {

                    cairo_rectangle(cr, x_left, y_upper, metrica_ejex, metrica_ejey);
                    cairo_set_source_rgba(cr, 0, 0.7, 0, 0.5);
                    cairo_fill(cr);
                }

                else if( world[j][world.size()-i] == 2 ) {

                    cairo_rectangle(cr, x_left, y_upper, metrica_ejex, metrica_ejey);
                    cairo_set_source_rgba(cr, 0.9, 0.3, 0.3, 0.5);
                    cairo_fill(cr);
                }

                else if( world[j][world.size()-i] == 2.5 ) {

                    cairo_rectangle(cr, x_left, y_upper, metrica_ejex, metrica_ejey);
                    cairo_set_source_rgba(cr, 0.6, 0.1, 0.1, 0.5);
                    cairo_fill(cr);
                }
            }
        }
    }

    for (int i = 0; i < path.size(); i++) {

        double x_left = origenx + path[i].first*metrica_ejex;
        double y_upper = origeny - (world.size()-path[i].second)*metrica_ejey;

        cairo_rectangle(cr, x_left, y_upper, 15, 10);
        cairo_set_source_rgba(cr, 1, 1, 1, 1);
        cairo_fill(cr);

        cairo_set_source_rgba(cr, 0, 0, 0, 1);
        cairo_text_extents_t te;
        cairo_text_extents (cr, to_string(i+1).c_str(), &te);
        cairo_move_to (cr, x_left, y_upper + te.width*(1.6));
        cairo_show_text (cr, to_string(i+1).c_str());
    }

    //Grid x

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 1.0);

    // x axis
    cairo_move_to(cr, origenx, origeny);
    cairo_line_to(cr, ejex, origeny);
    cairo_stroke(cr);

    for (int i = 1; i < world[0].size()+1; i++) {

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 1.0);

        cairo_move_to(cr, (origenx+(metrica_ejex*i)), origeny);
        cairo_line_to(cr, (origenx+(metrica_ejex*i)), ejey);

        cairo_stroke(cr);
    }

    //Grid y

    // y axis
    cairo_move_to(cr, origenx, origeny);
    cairo_line_to(cr, origenx, ejey);
    cairo_stroke(cr);

    for (int i = 1; i < world.size()+1; i++) {

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 1.0);

        cairo_move_to(cr, origenx, (ejey+(metrica_ejey*(i-1))));
        cairo_line_to(cr, ejex, (ejey+(metrica_ejey*(i-1))));

        cairo_stroke(cr);
    }

}

void Plot::shapeit(){

    cairo_set_operator(shape_cairo, CAIRO_OPERATOR_CLEAR);
    cairo_pattern_t *pat;
    pat = cairo_pattern_create_linear(w/2, 0.0, w/2, h);
    cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.9, 0.9, 0.9);
    cairo_pattern_add_color_stop_rgb(pat, 1.0, 0.6, 0.6, 0.6);
    cairo_rectangle(shape_cairo, 0, 0, w, h);
    cairo_set_source(shape_cairo, pat);
    cairo_fill(shape_cairo);

    // Draw axis

    // min y max de (x, y)

    double xmax = world[0].size();
    double xmin = 0;

    double ymax = world.size();
    double ymin = 0;

    double ejex = w - w/8;
    double ejey = h/8;
    double origenx = w/8;
    double origeny = h - h/8;

    double metrica_ejex = (ejex - origenx)/world[0].size();
    double metrica_ejey = (origeny - ejey)/world.size();

    // Draw predator

    int w_predator, h_predator;
    cairo_surface_t *predator;

    cairo_save(shape_cairo);
    predator = cairo_image_surface_create_from_png ("predator.png");
    w_predator = cairo_image_surface_get_width (predator);
    h_predator = cairo_image_surface_get_height (predator);
    cairo_translate (shape_cairo, origenx + (start_pos.first)*metrica_ejex, origeny - (world.size()-start_pos.second)*metrica_ejey);
    cairo_scale  (shape_cairo, metrica_ejex/double(w_predator), metrica_ejey/double(h_predator));
    cairo_set_source_surface (shape_cairo, predator, 0, 0);
    cairo_paint (shape_cairo);
    cairo_surface_destroy (predator);
    cairo_restore(shape_cairo);

    // Draw prey

    int w_prey, h_prey;
    cairo_surface_t *prey;

    cairo_save(shape_cairo);
    prey = cairo_image_surface_create_from_png ("prey.png");
    w_prey = cairo_image_surface_get_width (prey);
    h_prey = cairo_image_surface_get_height (prey);
    cairo_translate (shape_cairo, origenx + (end_pos.first)*metrica_ejex, origeny - (world.size()-end_pos.second)*metrica_ejey);
    cairo_scale  (shape_cairo, metrica_ejex/double(w_prey), metrica_ejey/double(h_prey));
    cairo_set_source_surface (shape_cairo, prey, 0, 0);
    cairo_paint (shape_cairo);
    cairo_surface_destroy (prey);
    cairo_restore(shape_cairo);

    // Color rest of the cells

    for (int i = 1; i < world.size()+1; i++) {

        for (int j = 0; j < world[0].size(); j++) {

            if ( (j != start_pos.first and (i-1) != start_pos.second) or (j != end_pos.first and (i-1) != end_pos.second) ) {

                double x_left = origenx + j*metrica_ejex;
                double y_upper = origeny - i*metrica_ejey;

                if ( world[j][world.size()-i] == 0 ) {

                    int w_water, h_water;
                    cairo_surface_t *water;

                    cairo_save(shape_cairo);
                    water = cairo_image_surface_create_from_png ("water.png");
                    w_water = cairo_image_surface_get_width (water);
                    h_water = cairo_image_surface_get_height (water);
                    cairo_translate (shape_cairo, origenx + j*metrica_ejex, origeny - i*metrica_ejey);
                    cairo_scale  (shape_cairo, metrica_ejex/double(w_water), metrica_ejey/double(h_water));
                    cairo_set_source_surface (shape_cairo, water, 0, 0);
                    cairo_paint (shape_cairo);
                    cairo_surface_destroy (water);
                    cairo_restore(shape_cairo);
                }

                else if( world[j][world.size()-i] == 1 ) {

                    cairo_rectangle(shape_cairo, x_left, y_upper, metrica_ejex, metrica_ejey);
                    cairo_set_source_rgba(shape_cairo, 0, 0.7, 0, 0.5);
                    cairo_fill(shape_cairo);
                }

                else if( world[j][world.size()-i] == 2 ) {

                    cairo_rectangle(shape_cairo, x_left, y_upper, metrica_ejex, metrica_ejey);
                    cairo_set_source_rgba(shape_cairo, 0.9, 0.3, 0.3, 0.5);
                    cairo_fill(shape_cairo);
                }

                else if( world[j][world.size()-i] == 2.5 ) {

                    cairo_rectangle(shape_cairo, x_left, y_upper, metrica_ejex, metrica_ejey);
                    cairo_set_source_rgba(shape_cairo, 0.6, 0.1, 0.1, 0.5);
                    cairo_fill(shape_cairo);
                }
            }
        }
    }

    for (int i = 0; i < path.size(); i++) {

        double x_left = origenx + path[i].first*metrica_ejex;
        double y_upper = origeny - (world.size()-path[i].second)*metrica_ejey;

        cairo_rectangle(cr, x_left, y_upper, 15, 10);
        cairo_set_source_rgba(cr, 1, 1, 1, 1);
        cairo_fill(cr);

        cairo_set_source_rgba(cr, 0, 0, 0, 1);
        cairo_text_extents_t te;
        cairo_text_extents (cr, to_string(i+1).c_str(), &te);
        cairo_move_to (cr, x_left, y_upper + te.width*(1.6));
        cairo_show_text (cr, to_string(i+1).c_str());
    }

    //Grid x

    cairo_set_source_rgb(shape_cairo, 0, 0, 0);
    cairo_set_line_width(shape_cairo, 1.0);

    // x axis
    cairo_move_to(shape_cairo, origenx, origeny);
    cairo_line_to(shape_cairo, ejex, origeny);
    cairo_stroke(shape_cairo);

    for (int i = 1; i < world[0].size()+1; i++) {

        cairo_set_source_rgb(shape_cairo, 0, 0, 0);
        cairo_set_line_width(shape_cairo, 1.0);

        cairo_move_to(shape_cairo, (origenx+(metrica_ejex*i)), origeny);
        cairo_line_to(shape_cairo, (origenx+(metrica_ejex*i)), ejey);

        cairo_stroke(shape_cairo);
    }

    //Grid y

    // y axis
    cairo_move_to(shape_cairo, origenx, origeny);
    cairo_line_to(shape_cairo, origenx, ejey);
    cairo_stroke(shape_cairo);

    for (int i = 1; i < world.size()+1; i++) {

        cairo_set_source_rgb(shape_cairo, 0, 0, 0);
        cairo_set_line_width(shape_cairo, 1.0);

        cairo_move_to(shape_cairo, origenx, (ejey+(metrica_ejey*(i-1))));
        cairo_line_to(shape_cairo, ejex, (ejey+(metrica_ejey*(i-1))));

        cairo_stroke(shape_cairo);
    }

    XShapeCombineMask(dpy, w, ShapeBounding, 0, 0, cairo_xlib_surface_get_drawable(shape_surface), ShapeSet);
}
