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
    bool operator()(Point const& p1, Point const& p2) {

        return p1.area > p2.area;
    }
};

double line_lenght(tuple<double, double> x, tuple<double, double> y);

double triangle_area( tuple<double, double> x, tuple<double, double> y, tuple<double, double> z );

#endif
