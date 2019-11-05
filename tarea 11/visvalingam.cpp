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

vector< tuple<double, double> > simplify_poly(vector< tuple<double, double> > data, double epsilon){

    // Create vector of Points

    vector<Point> lineString;

    for (int i = 0; i < data.size(); i++) {

        int left = ( i == 0 ? -1 : i -1 );
        int right = ( i == data.size()-1 ? -1 : i + 1 );

        double area = 0.0;

        if( left == -1 or right == -1 )
            area = 65535.0;
        else
            area = triangle_area( data[left], data[i], data[right] );

        lineString.push_back( Point(area, i, left, right) );
    }

    // Register areas in priority queues

    vector<Point*> points_queue;

    // Initialize queue with all points and deleted with zero (no point has been deleted)

    for (int i = 0; i < lineString.size(); i++) {

        points_queue.push_back(&lineString[i]);
    }

    make_heap(points_queue.begin(), points_queue.end(), CompareArea());

    //cout << "Area: " << (*points_queue.front()).area << endl;

    while ( !points_queue.empty() && (*points_queue.front()).area < epsilon ) {

        //cout << "Status before:" << endl;
        //for_each( lineString.begin(), lineString.end(), print_point );
        //cout << "--------------------------------------\n";

        Point* p = points_queue.front();
        pop_heap(points_queue.begin(), points_queue.end(), CompareArea());
        points_queue.pop_back();

        Point* left_point = &lineString[(*p).left];
        Point* right_point = &lineString[(*p).right];

        (*left_point).right = (*right_point).index;
        (*right_point).left = (*left_point).index;

        if ( (*left_point).left != -1 and (*left_point).right != -1 ) {
            (*left_point).area = triangle_area( data[(*left_point).left], data[(*left_point).index], data[(*left_point).right] );
        }

        if ( (*right_point).left != -1 and (*right_point).right != -1 ) {
            (*right_point).area = triangle_area( data[(*right_point).left], data[(*right_point).index], data[(*right_point).right] );
        }

        //cout << "Status after deleting node:" << (*p).index << endl;
        //for_each( lineString.begin(), lineString.end(), print_point );
        //cout << "--------------------------------------\n";

        make_heap(points_queue.begin(), points_queue.end(), CompareArea());
    }


    Point p = lineString[0];

    vector< tuple<double, double> > points;

    while( p.right != -1 ) {

        points.push_back(data[p.index]);

        p = lineString[p.right];
    }

    points.push_back(data[p.index]);

    return points;
}

vector< tuple<double, double> > read_points(const string points_file){

    ifstream file(points_file);
    string line;

    string x;
    string y;

    vector< tuple<double, double> > data;

    while ( getline(file, line) ) {

        stringstream ss(line);

        getline(ss, x, ',');
        getline(ss, y, ',');

        data.push_back( tuple<double, double>(stod(x), stod(y)) );
    }

    return data;
}

double area_poligon(vector< tuple<double, double> > points){

    double area = 0;

    for (size_t i = 0; i < points.size()-1; i++) {

        area += (get<0>(points[i])*get<1>(points[i+1]) - get<0>(points[i+1])*get<1>(points[i]));
    }

    area += (get<0>(points[points.size()-1])*get<1>(points[0]) - get<0>(points[0])*get<1>(points[points.size()-1]));

    return fabs(area/2);
}
