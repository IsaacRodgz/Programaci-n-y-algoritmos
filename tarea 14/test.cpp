#include <iostream>
#include<bits/stdc++.h>
#include "Point.hpp"
#include "Geom.hpp"

using namespace std;


void test_ConvexHull(){

    Geom g = Geom();

    g.readPoints("data.txt");

    //g.printPoints();

    g.convexHull();

    cout << "\nConvex hull: \n" << endl;

    g.printConvexHull();

    cout << endl;

}

int main(int argc, char const *argv[]) {

    test_ConvexHull();
}
