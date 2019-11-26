#include <iostream>
#include<bits/stdc++.h>
#include "Point.hpp"
#include "Geom.hpp"

using namespace std;


void test_ConvexHull(){

    Geom g = Geom();

    g.readPoints("data.txt");

    g.convexHull();

    g.plot("Jarvis Convex Hull");

    //g.convexHullGraham();

    //g.plot("Graham Convex Hull");

}

int main(int argc, char const *argv[]) {

    test_ConvexHull();
}
