#include <iostream>
#include<bits/stdc++.h>
#include "ASearch.hpp"
#include "Plot.hpp"

using namespace std;


void test_ASearch(){

    /*
    vector<vector<int> > world = {

        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
    };
    */

    vector<vector<double> > world = {

        { 1, 0, 0, 0 },
        { 1, 1, 2, 2.5 },
        { 1, 0, 0, 1 },
        { 1, 1, 1, 1 },
    };

    pair<int, int> start_pos(0, 0);

    pair<int, int> end_pos(2, 3);

    ASearch aSearch(start_pos, end_pos);

    aSearch.search(world);
    /*
    cout << "\n Solution: \n" << endl;

    aSearch.printPath();
    */
    Plot::plot(world, aSearch.getPath(), start_pos, end_pos);
}

int main(int argc, char const *argv[]) {

    test_ASearch();
}
