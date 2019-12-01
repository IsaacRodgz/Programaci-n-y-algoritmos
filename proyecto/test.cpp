#include <iostream>
#include<bits/stdc++.h>
#include "ASearch.hpp"
#include "Plot.hpp"
#include <random>

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

    /*
    vector<vector<double> > world = {

        { 1, 0, 0, 0 },
        { 1, 1, 2, 2.5 },
        { 1, 0, 0, 1 },
        { 1, 1, 1, 1 }
    };
    */

    vector<vector<double> > world = {

        { 1, 0, 0, 1, 0 },
        { 1, 1, 2, 2.5, 1 },
        { 1, 0, 0, 1, 1 },
        { 2.5, 1, 1, 1, 1 },
        { 1, 1, 2, 1, 1 }
    };

    vector<pair<int, int> > available;

    for (int i = 0; i < world.size(); i++) {

        for (int j = 0; j < world[0].size(); j++) {

            if ( world[i][j] == 1 ) {

                available.push_back(make_pair(i, j));
            }
        }
    }

    // Random initial and end positon

    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, available.size());

    // Random initial position

    int start_index = distr(eng);
    int start_x = available[start_index].first;
    int start_y = available[start_index].second;

    pair<int, int> start_pos(start_x, start_y);

    available.erase(available.begin() + start_index);

    // Random final position

    int end_index = distr(eng);
    int end_x = available[end_index].first;
    int end_y = available[end_index].second;

    pair<int, int> end_pos(end_x, end_y);

    // Search for best path

    cout << "\nInitial position: " << start_pos.first << " , " << start_pos.second << endl;
    cout << "\nFinal position: " << end_pos.first << " , " << end_pos.second << endl;

    ASearch aSearch(start_pos, end_pos);

    aSearch.search(world);

    cout << "\n Solution: \n" << endl;

    aSearch.printPath();

    // Plot window with world matrix and solution found

    Plot p = Plot(world, aSearch.getPath(), start_pos, end_pos);
    p.plot();

}

int main(int argc, char const *argv[]) {

    test_ASearch();
}
