#ifndef POINT_H
#define POINT_H

#include<tuple>

using namespace std;

class Point{

protected:

    tuple<double, double> coords;
    double area;
    Point left;
    Point right;

public:

    Point(double x, double y, double area, Point left, Point right):
        coords(make_tuple(x, y)), area

    // Getters

    tuple<double, double> getArea() const;

    // Setters



};
