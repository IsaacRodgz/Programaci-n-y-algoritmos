#ifndef GEOM_HPP
#define GEOM_HPP

#include <bits/stdc++.h>
#include <string.h>
#include "Point.hpp"

using namespace std;

class Geom {

private:

    vector<Point> points;
    vector<int> convex_hull;

public:

    // Methods

    void readPoints(string data_file);

    void printPoints();

    void printConvexHull();

    double det(int p, int q, int r);

    void convexHull();

    void convexHullGraham();

    void plot();

};

#endif
