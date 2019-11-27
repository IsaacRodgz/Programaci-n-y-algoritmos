#include <math.h>
#include <bits/stdc++.h>
#include <cairo.h>

#include "Point.hpp"
#include "Geom.hpp"
# define PI 3.14159265359

using namespace std;
Point Geom::minPoint(0, 0);

// Methods

void Geom::read_pgm(const string image_file_name){

    ifstream file(image_file_name);
    string line;

    // Verify version P2

    getline(file, line);

    if(line.compare("P2") != 0)
        cerr << "Error: Not a P2 pgm image" << endl;

    // Ignore coments

    int width;
    int height;

    getline(file, line);

    if(line.find("#") != string::npos){

        getline(file, line);
    }

    stringstream ss(line);
    ss >> width >> height;

    // Ignore max value

    getline(file, line);

    // Create matrix

    stringstream sst;
    sst << file.rdbuf();

    // Read image

    for(int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {

            double val;
            sst >> val;

            if (val > 0) {

                points.push_back(Point(row, col));
            }
        }
    }

    file.close();
}

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

    for (int i = 0; i < convex_hull_points.size(); i++) {

        double x = convex_hull_points[i].getX();
        double y = convex_hull_points[i].getY();

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

double Geom::det(Point p, Point q, Point r){

    double x1 = p.getX();
    double y1 = p.getY();

    double x2 = q.getX();
    double y2 = q.getY();

    double x3 = r.getX();
    double y3 = r.getY();

    return x1*(y2-y3) - y1*(x2-x3) + (x2*y3-x3*y2);
}

void Geom::convexHull(){

    vector<int> convex_hull_indexes;

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

        convex_hull_indexes.push_back(p);

        q = (p+1)%points.size();

        for (int i = 0; i < points.size(); i++) {

            // If point i is below line p->q, determinant of cross product between vectors p->r and p->q is positive

            if ( det(p, q, i) > 0 ) {

                q = i;
            }
        }

        p = q;

    } while( p != minX );

    for (int i = 0; i < convex_hull_indexes.size(); i++) {

        convex_hull_points.push_back(points[convex_hull_indexes[i]]);
    }

}

void Geom::convexHullGraham(){

    // Find initial point

    int minPointIndex = 0;

    for (int i = 1; i < points.size(); i++) {

        if (points[i] < points[minPointIndex]){

            minPointIndex = i;
        }
    }

    // Point to calculate angles of all other points

    minPoint = points[minPointIndex];

    // Sort points by angle with respect to minPoint

    sortedPoints = points;

    sortAngle2(minPointIndex);

    // Iterate through ordered points

    convex_hull_points.push_back(sortedPoints[0]);
    convex_hull_points.push_back(sortedPoints[1]);
    convex_hull_points.push_back(sortedPoints[2]);

    for (int i = 3; i < sortedPoints.size(); i++) {

        Point top = convex_hull_points.back();
        convex_hull_points.pop_back();

        while ( cross_product(convex_hull_points.back(), top, sortedPoints[i]) != -1 ) {

            top = convex_hull_points.back();
            convex_hull_points.pop_back();
        }

        convex_hull_points.push_back(top);
        convex_hull_points.push_back(sortedPoints[i]);
    }

}

void Geom::sortAngle2(int minPointIndex){

    Point temp = sortedPoints[0];
    sortedPoints[0] = sortedPoints[minPointIndex];
    sortedPoints[minPointIndex] = temp;

    sort(sortedPoints.begin() + 1, sortedPoints.end(), angle_cmp);
}

bool Geom::angle_cmp(Point p, Point q){

    int val = cross_product(minPoint, p, q);

    if (val == 0) {

        return norm(minPoint, p) < norm(minPoint, q);
    }

    return (val == -1);
}

int Geom::cross_product(Point p, Point q, Point r){

    int val = (q.getX() - p.getX()) * (r.getY() - p.getY()) - (q.getY() - p.getY()) * (r.getX() - p.getX());

    if (val > 0){

        return -1;
    }

    else if (val < 0){

        return 1;
    }

    return 0;
}

int Geom::norm(Point p, Point q){

    int diff_x = p.getX() - q.getX();
    int diff_y = p.getY() - q.getY();

    return diff_x*diff_x + diff_y*diff_y;
}

void Geom::plot(string graph_title){

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

    // Nombre grafica

    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, (ejey/3.0));
    cairo_move_to(cr, w/3.0, ejey/2.0);
    cairo_show_text(cr, graph_title.c_str());

    // Draw point

    for (int i = 0; i < points.size(); i++) {

        double valx = origenx + ((ejex-origenx)/(xmax-xmin))*(points[i].getX()-xmin);
        double valy = ejey + ((origeny-ejey)/(ymin-ymax))*(points[i].getY()-ymax);

        cairo_set_source_rgb(cr, 0.69, 0.19, 0.0);
        cairo_arc(cr, valx, valy, 1.0, 0, 2*PI);
        cairo_fill(cr);
        cairo_stroke(cr);
    }

    // Draw convex hull

    cairo_set_source_rgba(cr, 0.2, 0.2, 0.8, 0.3);

    for (size_t i = 0; i < convex_hull_points.size(); i++) {

        double valx = origenx + ((ejex-origenx)/(xmax-xmin))*(convex_hull_points[i].getX()-xmin);
        double valy = ejey + ((origeny-ejey)/(ymin-ymax))*(convex_hull_points[i].getY()-ymax);

        cairo_line_to(cr, valx, valy);
    }
    double valx = origenx + ((ejex-origenx)/(xmax-xmin))*(convex_hull_points[0].getX()-xmin);
    double valy = ejey + ((origeny-ejey)/(ymin-ymax))*(convex_hull_points[0].getY()-ymax);
    cairo_line_to(cr, valx, valy);
    cairo_stroke(cr);

    cairo_surface_write_to_png(surface, (graph_title+".png").c_str());
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

}
