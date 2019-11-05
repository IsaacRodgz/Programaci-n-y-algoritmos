#include <iostream>
#include<bits/stdc++.h>
#include "visvalingam.h"
#include "plot.h"

using namespace std;

// g++ -std=c++11 visvalingam.cpp test2.cpp -o test && ./test

void print_point(Point p) {
    cout << "Index: " << p.index << endl;
    cout << "Area: " << p.area << "\n" << endl;
}

void test_visvalingam(const string points_file){
/*
    vector< tuple<double, double> > data = { tuple<double, double>(10, 10), tuple<double, double>(50, 50),
    tuple<double, double>(90, 25), tuple<double, double>(140, 95) };
*/

    vector< tuple<double, double> > data = read_points(points_file);

    vector< tuple<double, double> > points;

    //points = simplify_poly(data, 1);

    plot(data, points);
}

int main(int argc, char const *argv[]) {

    if (argc == 1) {

        cerr << "Error: Argument missing: points_file" << endl;
    }

    else

        test_visvalingam(argv[1]);

    return 0;
}
