#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <cmath>
#include "visvalingam.h"

using namespace std;

double line_lenght(tuple<double, double> x, tuple<double, double> y){

    return sqrt( pow( get<0>(x) - get<0>(y), 2 ) + pow( get<1>(x) - get<1>(y), 2 ) );
}

double triangle_area( tuple<double, double> x, tuple<double, double> y, tuple<double, double> z ){

    double a = line_lenght(x, y);
    double b = line_lenght(y, z);
    double c = line_lenght(x, z);
    double s = (a + b + c)/2;

    return sqrt(s*(s-a)*(s-b)*(s-c));
}
