#include <iostream>
#include<bits/stdc++.h>
#include "visvalingam.h"

using namespace std;

void print_point(Point p) {
    cout << "Index: " << p.index << endl;
    cout << "Area: " << p.area << "\n" << endl;
}

void test_visvalingam(){

    vector< tuple<double, double> > data = { tuple<double, double>(1, 1), tuple<double, double>(3, 2),
    tuple<double, double>(4, 3), tuple<double, double>(5, 2), tuple<double, double>(5, 1),
    tuple<double, double>(7, 0) };

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

    double epsilon = 1.0;

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

    cout << "\nFinal nodes: \n" << endl;

    Point p = lineString[0];

    while( p.right != -1 ) {

        cout << "\n (" << get<0>(data[p.index]) << ", " << get<1>(data[p.index]) << ")\n" << endl;

        p = lineString[p.right];
    }

    cout << "\n (" << get<0>(data[p.index]) << ", " << get<1>(data[p.index]) << ")\n" << endl;
}

int main(int argc, char const *argv[]) {

    test_visvalingam();

    return 0;
}
