#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <cmath>
#include "visvalingam.h"

using namespace std;

double line_lenght(Point p1, Point p2){

    return sqrt( pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) );
}

double triangle_area(Point p){

    double a = line_lenght(*p.left, p);
    double b = line_lenght(p, *p.right);
    double c = line_lenght(*p.left, *p.right);
    double s = (a + b + c)/2;

    return sqrt(s*(s-a)*(s-b)*(s-c));
}
