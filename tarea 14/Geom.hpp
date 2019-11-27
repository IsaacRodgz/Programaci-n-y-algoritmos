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
    vector<Point> sortedPoints;

public:

    static Point minPoint;

    // Methods

    void readPoints(string data_file);

    void read_pgm(const string image_file_name);

    void printPoints();

    void printConvexHull();

    double det(int p, int q, int r);

    double det(Point p, Point q, Point r);

    void convexHull();

    void convexHullGraham();

    void sortAngle2(int minPointIndex);

    static bool angle_cmp(Point p, Point q);

    static int cross_product(Point p, Point q, Point r);

    static int norm(Point p, Point q);

    void plot(string graph_title);

};

#endif
