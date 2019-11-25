#include <math.h>
#include <bits/stdc++.h>

#include "Point.hpp"
#include "Geom.hpp"

using namespace std;

// Methods

void Geom::readPoints(string data_file){

    ifstream file(data_file);
    string line;

    double val_x;
    double val_y;

    while ( getline(file, line) ) {

        stringstream ss(line);

        ss >> val_x >> val_y;

        points.push_back(Point(val_x, val_y));

    }

    file.close();
}

void Geom::printPoints(){

    for (int i = 0; i < points.size(); i++) {

        double x = points[i].getX();
        double y = points[i].getY();

        cout << "x: " << x << "    " << "y: " << y << endl;
    }
}

void Geom::printConvexHull(){

    for (int i = 0; i < convex_hull.size(); i++) {

        int next = convex_hull[i];

        double x = points[next].getX();
        double y = points[next].getY();

        cout << "x: " << x << "    " << "y: " << y << endl;
    }
}

double Geom::det(int p, int q, int r){

    double x1 = points[r].getX() - points[p].getX();
    double y1 = points[r].getY() - points[p].getY();

    double x2 = points[q].getX() - points[p].getX();
    double y2 = points[q].getY() - points[p].getY();

    return x1*y2 - y1*x2;
}

void Geom::convexHull(){

    // Find min x point

    int minX = 0;

    for (int i = 0; i < points.size(); i++) {

        if ( points[minX].getX() < points[i].getX() ) {
            minX = i;
        }
    }

    // Find remaining points

    int p = minX;
    int q;

    do {

        convex_hull.push_back(p);

        q = (p+1)%points.size();

        for (int i = 0; i < points.size(); i++) {

            // If point i is below line p->q, determinant of cross product between vectors p->r and p->q is positive

            if ( det(p, q, i) > 0 ) {

                q = i;
            }
        }

        p = q;

    } while( p != minX );

}
