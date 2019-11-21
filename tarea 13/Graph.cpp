#include <cairo.h>
#include <bits/stdc++.h>
#include <math.h>
#include "Graph.hpp"
# define PI 3.14159265359
using namespace std;

void plot(vector<double> x){

    int w = 500;
    int h = 500;

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

    double xmax = x.size()-1;
    double xmin = 0;

    double ymax = *min_element(x.begin(), x.end());
    double ymin = *max_element(x.begin(), x.end());

    double ejex = w - w/8;
    double ejey = h/8;
    double origenx = w/8;
    double origeny = h - h/8;

    //cout << "\nejex: " << ejex << endl;
    //cout << "\nejey: " << ejey << endl;
    //cout << "\norigenx: " << origenx << endl;
    //cout << "\norigeny: " << origeny << endl;

    cairo_set_source_rgb(cr, 0.2, 0.2, 0.6);
    cairo_set_line_width(cr, 3.0);

    // x axis

    cairo_move_to(cr, origenx, origeny);
    cairo_line_to(cr, ejex, origeny);

    // y axis

    cairo_move_to(cr, origenx, origeny);
    cairo_line_to(cr, origenx, ejey);

    // Draw axis

    cairo_stroke(cr);

    //Grid

    double metrica_ejex = (ejex - origenx)/10.0;
    double metrica_ejey = (origeny - ejey)/10.0;

    for (int i = 1; i < 11; i++) {

        cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
        cairo_set_line_width(cr, 0.5);

        cairo_move_to(cr, (origenx+(metrica_ejex*i)), origeny);
        cairo_line_to(cr, (origenx+(metrica_ejex*i)), ejey);

        cairo_move_to(cr, origenx, (ejey+(metrica_ejey*(i-1))));
        cairo_line_to(cr, ejex, (ejey+(metrica_ejey*(i-1))));

        cairo_stroke(cr);
    }

    // Labels

    /*
    vector<string> metricax;

    for (size_t i = 0; i < 11; i++) {

        metricay.push_back(to_string(double(i)/10));
    }

    metricay[i].c_str();
    */

    // x labels

    double xstep = (xmax - xmin)/10;

    for (int i = 0; i < 11; i++) {

        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 10.0);
        cairo_move_to(cr, (origenx+(metrica_ejex*i)), (origeny + 10));
        cairo_save(cr);
        cairo_rotate(cr, 45.0);
        cairo_show_text(cr, to_string(int(xstep*i)).c_str());
        cairo_restore(cr);
    }

    // y labels

    double ystep = (ymax - ymin)/10;

    for (int i = 0; i < 11; i++) {

        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 10.0);
        cairo_move_to(cr, (origenx - 30), (origeny-(metrica_ejey*i)));
        cairo_save(cr);
        cairo_rotate(cr, -45.0);
        cairo_show_text(cr, to_string(-ystep*i).c_str());
        cairo_restore(cr);
    }

    // Nombre grafica

    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, (ejey/3.0));
    cairo_move_to(cr, w/3.0, ejey/2.0);
    string title = "Epochs vs Loss";
    cairo_show_text(cr, title.c_str());

    // Draw point

    for (int i = 0; i < x.size(); i++) {

        double valx = origenx + ((ejex-origenx)/(xmax-xmin))*i;
        double valy = ejey - ((origeny-ejey)/(ymax-ymin))*(x[i]-ymin);

        cairo_set_source_rgb(cr, 0.69, 0.19, 0.0);
        cairo_arc(cr, valx, valy, 1.5, 0, 2*PI);
        cairo_fill(cr);
        cairo_stroke(cr);
    }

    cairo_surface_write_to_png(surface, "loss.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

}
