#ifndef POINT_HPP
#define POINT_HPP

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

class Point {

private:

    double x;
    double y;
    double angle;

public:

    // Constructor

    Point(double x_p, double y_p);

    Point(double x_p, double y_p, double angle_p);

    // Methods



    // Getters

    double getX();

    double getY();

    double getAngle();

    // Setters

    void setAngle(double angle_p);

};

#endif
