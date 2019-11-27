#include <iostream>
#include<bits/stdc++.h>
#include "Point.hpp"
#include "Geom.hpp"

using namespace std;


void test_ConvexHull(int algo_type, int data_type){

    Geom g = Geom();

    if (data_type == 1) {

        g.readPoints("data.txt");
    }

    else {

        g.read_pgm("estrella.pgm");
    }


    if (algo_type == 1) {

        g.convexHull();

        g.plot("Jarvis Convex Hull");
    }

    else {

        g.convexHullGraham();

        g.plot("Graham Convex Hull");
    }

}

int main(int argc, char const *argv[]) {

    if(argc < 3){

        cerr << "\nError: Missing arguments\n" << endl;
    }

    else{

        test_ConvexHull(atoi(argv[1]), atoi(argv[2]));
    }
}
