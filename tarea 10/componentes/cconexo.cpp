#include <iostream>
#include<bits/stdc++.h>
#include <fstream>
#include<string>
#include "cconexo.h"

using namespace std;

void write_pgm(vector< vector<int> > pgm_image, const string image_file_name){

    ofstream file;
    file.open(image_file_name);

    // Write header

    file << "P2" << endl;

    // Wite dimensions

    file << pgm_image[0].size() << " " << pgm_image.size() << endl;

    // Write max value

    file << "255" << endl;

    // Write image

    for (size_t row = 0; row < pgm_image.size(); row++) {
        for (size_t col = 0; col < pgm_image[0].size(); col++) {
            file << pgm_image[row][col] << endl;
        }
    }

    file.close();
}

vector< vector<int> > read_pgm(const string image_file_name){

    ifstream file(image_file_name);
    string line;

    // Verify version P2

    getline(file, line);

    if(line.compare("P2") != 0)
        cerr << "Error: Not a P2 pgm image" << endl;

    // Ignore coments

    int width;
    int height;

    getline(file, line);

    if(line.find("#") != string::npos){

        getline(file, line);
    }

    stringstream ss(line);
    ss >> width >> height;

    // Ignore max value

    getline(file, line);

    // Create matrix

    stringstream sst;
    sst << file.rdbuf();

    vector< vector<int> > pgm_image(height);
    for (int i = 0; i < height; i++) {
        pgm_image[i].resize(width);
    }

    // Read image

    for(int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            sst >> pgm_image[row][col];
        }
    }

    file.close();

    return pgm_image;

}

void bfs(vector< vector<bool> > &visited, vector< vector < tuple<int, int> > > &components, vector< vector<int> > &pgm_image, int i, int j){

    int rows = pgm_image.size();
    int cols = pgm_image[0].size();

    // Initialize new component

    int comp_index = components.size() - 1;

    // Helper vectors to traverse neighbours of pixel (i, j)
    vector<int> x_neighbours{ -1, 0, 1, -1, 0, 1, -1, 0, 1 };
    vector<int> y_neighbours{ -1, -1, -1, 0, 0, 0, 1, 1, 1 };

    // Queues to traverse connected component pixels
    deque <int> x;
    deque <int> y;

    // Begin travelsal at (i,j) pixel
    x.push_back(i);
    y.push_back(j);

    visited[i][j] = true;

    // Add element to component

    components[comp_index].push_back( tuple<int, int>(i, j));

    while( ! x.empty() ){

        // Get first pixel in queue

        int x_pos = x.front();
        x.pop_front();

        int y_pos = y.front();
        y.pop_front();

        // Visit neighbours

        for (size_t i = 0; i < x_neighbours.size(); i++) {

            int x_new = x_pos+x_neighbours[i];
            int y_new = y_pos+y_neighbours[i];

            if ( x_new >= 0 && x_new < rows && y_new >= 0 && y_new < cols){

                if ( !visited[x_new][y_new] ) {

                    // Validate limits of neighbour and pixel is not black

                    if ( pgm_image[x_new][y_new] > 0 ) {

                        visited[x_new][y_new] = true;

                        // Add element to component

                        components[comp_index].push_back( tuple<int, int>(x_new, y_new));

                        x.push_back(x_new);
                        y.push_back(y_new);
                    }
                }
            }
        }
    }
}

double num_comp_conexas(const string image_file_name){

    // Read image

    //cout << "\nReading image ..." << endl;

    vector< vector<int> > pgm_image = read_pgm(image_file_name);

    int rows = pgm_image.size();
    int cols = pgm_image[0].size();

    // Register visited pixels
    vector< vector<bool> > visited;
    visited.assign(rows, vector<bool>(cols, false));

    // Register connected components
    // Vector of components, where entry k is a vector of tuples (i,j) that belong to component k
    vector< vector < tuple<int, int> > > components;

    // Iterate image and find all components

    //cout << "\nFinding components ...\n" << endl;

    auto start = chrono::steady_clock::now();

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            if ( !visited[i][j] && pgm_image[i][j] > 0 ) {

                vector < tuple<int, int> > new_component;

                components.push_back(new_component);

                bfs(visited, components, pgm_image, i, j);
            }

        }
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "\nAlgorithm took " << chrono::duration <double, milli> (diff).count() << " ms to find all connected components" << endl;

    // Look for the biggest component

    unsigned int max_comp_index = 0 ;
    unsigned int max_comp_val = 0;

    // Look for the smallest component

    unsigned int min_comp_index = 0 ;
    unsigned int min_comp_val = 1<<30;

    for ( size_t i = 0; i < components.size(); i++) {

        if ( components[i].size() > max_comp_val ) {

            max_comp_val = components[i].size();
            max_comp_index = i;
        }

        if ( components[i].size() < min_comp_val ) {

            min_comp_val = components[i].size();
            min_comp_index = i;
        }
    }

    // Create new image with biggest and smallest component

    vector< vector<int> > minmax_comp_image(rows);
    for (int i = 0; i < rows; i++) {
        minmax_comp_image[i].resize(cols, 0);
    }

    int x;
    int y;

    //cout << "\nBiggest component of size: " << components[max_comp_index].size() << endl;
    //cout << "\nSmallest component of size: " << components[min_comp_index].size() << endl;

    for (size_t i = 0; i < components[max_comp_index].size(); i++) {
        x = get<0>(components[max_comp_index][i]);
        y = get<1>(components[max_comp_index][i]);

        minmax_comp_image[x][y] = 255;
    }

    for (size_t i = 0; i < components[min_comp_index].size(); i++) {
        x = get<0>(components[min_comp_index][i]);
        y = get<1>(components[min_comp_index][i]);

        minmax_comp_image[x][y] = 255;
    }

    cout << "\nWriting image to file " << "min_max_"+image_file_name << endl;

    write_pgm(minmax_comp_image, "min_max_"+image_file_name);

    // Write sizes of all connected components to file

    cout << "\nWriting sizes to file " << "comp_sizes_"+image_file_name.substr(0, image_file_name.size()-4)+".txt" << endl;

    ofstream file;
    file.open("comp_sizes_"+image_file_name.substr(0, image_file_name.size()-4)+".txt");

    for (size_t i = 0; i < components.size(); i++) {

        file << i+1 << " " << components[i].size() << endl;
    }

    return components.size();
}
