#ifndef GEOM_HPP
#define GEOM_HPP

#include <bits/stdc++.h>
#include <string.h>
#include "Point.hpp"

using namespace std;

class Geom {

private:

    vector<Point> points;
    vector<Point> convex_hull_points;

public:

    // Methods

    void readPoints(string data_file);

    void printPoints();

    void printConvexHull();

    double det(int p, int q, int r);

    double det(Point p, Point q, Point r);

    void convexHull();

    void convexHullGraham();

    vector<Point> sortAngle(int minPoint);

    static bool cmp(Point a, Point b);

    double calculateSinAngle(Point p_min, Point p);

    int initialPoint();

    void plot(string graph_title);

};

#endif
