#include <math.h>
#include <bits/stdc++.h>

#include "Point.hpp"

using namespace std;

// Constructor

Point::Point(double x_p, double y_p) : x(x_p), y(y_p), angle(0) {}
Point::Point(double x_p, double y_p, double angle_p) : x(x_p), y(y_p), angle(angle_p) {}

// Getters

double Point::getX(){

    return x;
}

double Point::getY(){

    return y;
}

double Point::getAngle(){

    return angle;
}

// Setters

void Point::setAngle(double angle_p){

    angle = angle_p;
}
