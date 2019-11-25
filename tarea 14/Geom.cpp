#include <math.h>
#include <bits/stdc++.h>
#include <cairo.h>

#include "Point.hpp"
#include "Geom.hpp"
# define PI 3.14159265359

using namespace std;

// Methods

void Geom::readPoints(string data_file){

    ifstream file(data_file);
    string line;

    double val_x;
    double val_y;

    while ( getline(file, line) ) {

        stringstream ss(line);

        ss >> val_x >> val_y;

        points.push_back(Point(val_x, val_y));

    }

    file.close();
}

void Geom::printPoints(){

    for (int i = 0; i < points.size(); i++) {

        double x = points[i].getX();
        double y = points[i].getY();

        cout << "x: " << x << "    " << "y: " << y << endl;
    }
}

void Geom::printConvexHull(){

    for (int i = 0; i < convex_hull.size(); i++) {

        int next = convex_hull[i];

        double x = points[next].getX();
        double y = points[next].getY();

        cout << "x: " << x << "    " << "y: " << y << endl;
    }
}

double Geom::det(int p, int q, int r){

    double x1 = points[r].getX() - points[p].getX();
    double y1 = points[r].getY() - points[p].getY();

    double x2 = points[q].getX() - points[p].getX();
    double y2 = points[q].getY() - points[p].getY();

    return x1*y2 - y1*x2;
}

void Geom::convexHull(){

    // Find min x point

    int minX = 0;

    for (int i = 0; i < points.size(); i++) {

        if ( points[minX].getX() > points[i].getX() ) {
            minX = i;
        }
    }

    // Find remaining points

    int p = minX;
    int q;

    do {

        convex_hull.push_back(p);

        q = (p+1)%points.size();

        for (int i = 0; i < points.size(); i++) {

            // If point i is below line p->q, determinant of cross product between vectors p->r and p->q is positive

            if ( det(p, q, i) > 0 ) {

                q = i;
            }
        }

        p = q;

    } while( p != minX );

}

bool cmp(Point a, Point b) {
    return a.getX() < b.getX() || (a.getX() == b.getX() && a.getY() < b.getY());
}

void Geom::convexHullGraham(){

    // Find min y point

    int minY = 0;

    for (int i = 0; i < points.size(); i++) {

        if ( points[minY].getY() > points[i].getY() ) {
            minY = i;
        }
    }

    // Find remaining points



}

void Geom::plot(){

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

    double xmax = 0;
    double xmin = 1<<30;

    double ymax = 0;
    double ymin = 1<<30;

    for (int i = 0; i < points.size(); i++) {

        if ( xmin > points[i].getX() ) {
            xmin = points[i].getX();
        }

        if ( xmax < points[i].getX() ) {
            xmax = points[i].getX();
        }

        if ( ymin > points[i].getY() ) {
            ymin = points[i].getY();
        }

        if ( ymax < points[i].getY() ) {
            ymax = points[i].getY();
        }
    }

    double ejex = w - w/8;
    double ejey = h/8;
    double origenx = w/8;
    double origeny = h - h/8;
    /*
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

    for (int i = 01; i < 11; i++) {

        cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
        cairo_set_line_width(cr, 0.5);

        cairo_move_to(cr, (origenx+(metrica_ejex*i)), origeny);
        cairo_line_to(cr, (origenx+(metrica_ejex*i)), ejey);

        cairo_move_to(cr, origenx, (ejey+(metrica_ejey*(i-1))));
        cairo_line_to(cr, ejex, (ejey+(metrica_ejey*(i-1))));

        cairo_stroke(cr);
    }

    // x labels

    double xstep = (xmax - xmin)/10;

    for (int i = 1; i < 11; i++) {

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
        cairo_show_text(cr, to_string(ystep*i).c_str());
        cairo_restore(cr);
    }
    */
    // Nombre grafica

    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, (ejey/3.0));
    cairo_move_to(cr, w/3.0, ejey/2.0);
    string title = "Convex Hull Jarvis";
    cairo_show_text(cr, title.c_str());

    // Draw point

    for (int i = 0; i < points.size(); i++) {

        double valx = origenx + ((ejex-origenx)/(xmax-xmin))*(points[i].getX()-xmin);
        double valy = ejey + ((origeny-ejey)/(ymin-ymax))*(points[i].getY()-ymax);

        cairo_set_source_rgb(cr, 0.69, 0.19, 0.0);
        cairo_arc(cr, valx, valy, 2.0, 0, 2*PI);
        cairo_fill(cr);
        cairo_stroke(cr);
    }

    // Draw convex hull

    vector<Point> ch;

    for (int i = 0; i < convex_hull.size(); i++) {

        ch.push_back(points[convex_hull[i]]);
    }

    cairo_set_source_rgba(cr, 0.2, 0.2, 0.8, 0.3);

    for (size_t i = 0; i < ch.size(); i++) {

        double valx = origenx + ((ejex-origenx)/(xmax-xmin))*(ch[i].getX()-xmin);
        double valy = ejey + ((origeny-ejey)/(ymin-ymax))*(ch[i].getY()-ymax);

        cairo_line_to(cr, valx, valy);
    }
    double valx = origenx + ((ejex-origenx)/(xmax-xmin))*(ch[0].getX()-xmin);
    double valy = ejey + ((origeny-ejey)/(ymin-ymax))*(ch[0].getY()-ymax);
    cairo_line_to(cr, valx, valy);
    cairo_stroke(cr);

    cairo_surface_write_to_png(surface, "convexHull.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

}
