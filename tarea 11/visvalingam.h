#ifndef VISVALINGAM_H
#define VISVALINGAM_H

#include <bits/stdc++.h>

struct Point {

    double x;
    double y;
    double area;
    Point* left;
    Point* right;
    int index;

    Point(double xp, double yp, int indexp) {
        x = xp;
        y = yp;
        area = 0;
        left = NULL;
        right = NULL;
        index = indexp;
    }
};

struct CompareArea {
    bool operator()(Point const& p1, Point const& p2) {

        return p1.area > p2.area;
    }
};

double line_lenght(Point p1, Point p2);

double triangle_area(Point p);

#endif
