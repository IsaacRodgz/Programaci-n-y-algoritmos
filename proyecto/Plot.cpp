#include <math.h>
#include <bits/stdc++.h>
#include <cairo.h>

#include "Plot.hpp"
# define PI 3.14159265359

using namespace std;

void Plot::plot(vector<vector<int> > world, vector<pair<int, int> > path, pair<int, int> start_pos, pair<int, int> end_pos){

    int w = 600;
    int h = 600;

    cairo_surface_t *surface;
    cairo_t *cr;
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
    cr = cairo_create(surface);

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

    cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
    cairo_set_line_width(cr, 0.5);

    //Grid x

    // x axis
    cairo_move_to(cr, origenx, origeny);
    cairo_line_to(cr, ejex, origeny);
    cairo_stroke(cr);

    double metrica_ejex = (ejex - origenx)/world[0].size();
    double metrica_ejey = (origeny - ejey)/world.size();

    for (int i = 1; i < world[0].size()+1; i++) {

        cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
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

        cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
        cairo_set_line_width(cr, 0.5);

        cairo_move_to(cr, origenx, (ejey+(metrica_ejey*(i-1))));
        cairo_line_to(cr, ejex, (ejey+(metrica_ejey*(i-1))));

        cairo_stroke(cr);
    }

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

    // Color cells
    /*
    for (int i = 1; i < world.size()+1; i++) {

        for (int j = 0; j < world[0].size(); j++) {

            double x_left = origenx + j*metrica_ejex;
            double y_upper = origeny - i*metrica_ejey;

            if ( world[j][world.size()-i] == 0 ) {

                cairo_rectangle(cr, x_left, y_upper, metrica_ejex, metrica_ejey);
                cairo_set_source_rgba(cr, 0, 0, 0, 0.5);
                cairo_fill(cr);
            }

            else if( world[j][world.size()-i] == 1 ) {

                cairo_rectangle(cr, x_left, y_upper, metrica_ejex, metrica_ejey);
                cairo_set_source_rgba(cr, 0, 1, 0, 0.3);
                cairo_fill(cr);
            }

        }
    }
    */

    cairo_surface_write_to_png(surface, "board.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

}
