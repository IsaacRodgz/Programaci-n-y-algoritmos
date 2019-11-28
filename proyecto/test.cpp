#include <iostream>
#include<bits/stdc++.h>
#include "ASearch.hpp"

using namespace std;


void test_ASearch(){

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

    pair<int, int> start_pos(8, 0);

    pair<int, int> end_pos(0, 9);

    ASearch aSearch(start_pos, end_pos);

    aSearch.search(world);
}

int main(int argc, char const *argv[]) {

    test_ASearch();
}
