#include <iostream>
#include<bits/stdc++.h>
#include "visvalingam.h"

using namespace std;

void test_visvalingam(){
    /*
    vector< tuple<double, double> > data = { tuple<double, double>(1, 1), tuple<double, double>(3, 2),
    tuple<double, double>(4, 3), tuple<double, double>(5, 2), tuple<double, double>(5, 1),
    tuple<double, double>(7, 0) };
    */
    vector< tuple<double, double> > data = { tuple<double, double>(1, 1), tuple<double, double>(3, 2),
    tuple<double, double>(4, 3), tuple<double, double>(5, 2), tuple<double, double>(5, 1),
    tuple<double, double>(7, 0) };

    // Create vector of Points

    vector<Point> lineString;

    for (int i = 0; i < data.size(); i++) {

        Point p( get<0>(data[i]), get<1>(data[i]), i );

        lineString.push_back(p);
    }

    // Register areas in priority queues

    vector<Point> areas_vq;
    vector<double> areas;
    vector<int> deleted;

    // Connect points and calculate areas

    for (int i = 0; i < lineString.size(); i++) {

        deleted.push_back(0);

        if ( i == 0 ){

            lineString[i].right = &lineString[i+1];
            areas.push_back(0.0);
        }

        else if( i == lineString.size() - 1 ){

            lineString[i].left = &lineString[i-1];
            areas.push_back(0.0);
        }
        else {

            lineString[i].left = &lineString[i-1];
            lineString[i].right = &lineString[i+1];

            lineString[i].area = triangle_area(lineString[i]);
            areas.push_back(lineString[i].area);
            areas_vq.push_back(lineString[i]);
        }
    }

    make_heap(areas_vq.begin(), areas_vq.end(), CompareArea());

    double epsilon = 1.6;

    while ( !areas_vq.empty() && areas_vq.front().area < epsilon ) {

        Point pv = areas_vq.front();
        pop_heap(areas_vq.begin(), areas_vq.end(), CompareArea());
        areas_vq.pop_back();
        //cout << "\nCurr point: " << "x: " << pv.x << ", y: " << pv.y << endl;
        //cout << "Area curr point: " << pv.area << "\n" << endl;

        deleted[pv.index] = 1;

        if( pv.left->left != NULL ){
            double area_left = triangle_area(*pv.left);
            areas[pv.left->index] = area_left;
        }

        if( pv.right->right != NULL ){
            double area_right = triangle_area(*pv.right);
            areas[pv.right->index] = area_right;
        }

        make_heap(areas_vq.begin(), areas_vq.end(), CompareArea());

        cout << "Status:" << endl;
        for (int i = 0; i < areas_vq.size(); i++) {
            cout << "Point: " << "x: " << areas_vq[i].x << ", y: " << areas_vq[i].y << endl;
            cout << "Area: " << areas_vq[i].area << "\n" << endl;
        }
        cout << "--------------------------------------\n";
        //cout << "\nUpdate right\nCurr point: " << "x: " << pv.right->x << ", y: " << pv.right->y << endl;
        //cout << "Area curr point: " << pv.right->area << "\n" << endl;
    }

    Point p = lineString[0];

    cout << "\nFinal nodes: \n" << endl;

    while( p.right != NULL ) {

        cout << "\n (" << p.x << ", " << p.y << ")\n" << endl;

        if ( p.left != NULL ) {
            //cout << "left: " << p.left->x << ", " << p.left->y << endl;
        }
        //cout << "right: " << p.right->x << ", " << p.right->y << endl;

        p = *p.right;
    }

    cout << "\n (" << p.x << ", " << p.y << ")\n" << endl;

}

int main(int argc, char const *argv[]) {

    test_visvalingam();

    return 0;
}
