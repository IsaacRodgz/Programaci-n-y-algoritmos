#include <iostream>
#include<bits/stdc++.h>
#include "visvalingam.h"
#include "plot.h"

using namespace std;

// g++ -std=c++11 visvalingam.cpp plot.cpp test2.cpp -o test -lcairo && ./test data3.txt 800

void print_point(Point p) {
    cout << "Index: " << p.index << endl;
    cout << "Area: " << p.area << "\n" << endl;
}

void test_visvalingam(const string points_file, double epsilon){

    vector< tuple<double, double> > data = read_points(points_file);

    vector< tuple<double, double> > points;

    points = simplify_poly(data, epsilon);

    cout << "\nUmbral de area minima: " << epsilon << endl;
    cout << "Porcentaje de compresion logrado: " << (1.0 - (static_cast<double>(points.size()+2)/data.size()))*100 << "%" << endl;
    cout << "Porcentaje de error: " << fabs(1.0 - area_poligon(points)/area_poligon(data))*100 << "%\n" << endl;

    plot(data, points);
}

int main(int argc, char const *argv[]) {

    if (argc == 1) {

        cerr << "Error: Arguments missing: points_file area_min" << endl;
    }

    else if (argc == 2) {

        cerr << "Error: Argument missing: area_min" << endl;
    }

    else

        test_visvalingam(argv[1], stod(argv[2]));

    return 0;
}
