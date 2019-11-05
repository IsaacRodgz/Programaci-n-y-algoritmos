#ifndef VISVALINGAM_H
#define VISVALINGAM_H

#include <bits/stdc++.h>
using namespace std;

struct Point {

    double area;
    int index;
    int left;
    int right;

    Point(double areap, int indexp, int leftp, int rightp) {

        area = areap;
        index = indexp;
        left = leftp;
        right = rightp;
    }
};

struct CompareArea {
    bool operator()(Point* p1, Point* p2) {

        return (*p1).area > (*p2).area;
    }
};

double line_lenght(tuple<double, double> x, tuple<double, double> y);

double triangle_area( tuple<double, double> x, tuple<double, double> y, tuple<double, double> z );

vector< tuple<double, double> > simplify_poly(vector< tuple<double, double> > data, double epsilon);

vector< tuple<double, double> > read_points(const string points_file);

double area_poligon(vector< tuple<double, double> > points);

#endif
