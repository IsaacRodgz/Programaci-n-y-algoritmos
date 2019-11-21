
#include <bits/stdc++.h>
#include <string.h>

#include "Data.hpp"

using namespace std;

void Data::readDataSet(vector<vector<double> > &x, vector<vector<double> > &y, string dataset_file){

    ifstream file(dataset_file);
    string line;
    int lines_read = 0;
    int num_columns = 0;

    vector<double> x_i;
    vector<double> y_i;

    while ( getline(file, line) ) {

        stringstream ss(line);
        string token;

        if (lines_read++ == 0) {

            while(getline(ss, token, '\t')){

                num_columns++;
            }

            continue;
        }

        int current_col = 0;

        while(getline(ss, token, '\t')){

            if (current_col++ < 4) {

                x_i.push_back(stod(token));
            }

            else{

                y_i.push_back(stod(token));
            }
        }

        x.push_back(x_i);
        x_i.clear();

        y.push_back(y_i);
        y_i.clear();

    }
}
