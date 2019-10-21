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

    getline(file, line);

    // Get dimensions

    int width;
    int height;

    getline(file, line);
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

void bfs(vector< vector<bool> > &visited, vector< vector < tuple<int, int> > > &components, vector< vector<int> > pgm_image, int i, int j){

    //cout << "BFS start at: " << i << ", " << j << "\n" << endl;

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

    while( ! x.empty() ){

        // Get first pixel in queue

        int x_pos = x.front();
        x.pop_front();

        int y_pos = y.front();
        y.pop_front();

        visited[x_pos][y_pos] = true;

        // Add element to component

        components[comp_index].push_back( tuple<int, int>(x_pos, y_pos));

        // Visit neighbours

        for (size_t i = 0; i < x_neighbours.size(); i++) {

            int x_new = x_pos+x_neighbours[i];
            int y_new = y_pos+y_neighbours[i];

            if ( !visited[x_new][y_new] ) {

                visited[x_new][y_new] = true;

                // Validate limits of neighbour and pixel is not black

                if ( x_new >= 0 && x_new < cols && y_new >= 0 && y_new < rows  &&  pgm_image[x_new][y_new] > 0 ) {

                    //cout << "Visit: " << x_new << ", " << y_new << "\n" << endl;
                    x.push_back(x_new);
                    y.push_back(y_new);
                }
            }
        }
    }
}

double num_comp_conexas(const string image_file_name){

    // Read image

    cout << "\nReading image ..." << endl;

    vector< vector<int> > pgm_image = read_pgm(image_file_name);

    int rows = pgm_image.size();
    int cols = pgm_image[0].size();

    /*
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%5d", pgm_image[i][j]);
        }
        cout << "\n";
    }
    */

    // Register visited pixels
    vector< vector<bool> > visited;
    visited.assign(rows, vector<bool>(cols, false));

    // Register connected components
    // Vector of components, where entry k is a vector of tuples (i,j) that belong to component k
    vector< vector < tuple<int, int> > > components;

    // Iterate image and find all components

    cout << "\nFinding components ...\n" << endl;

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            if ( !visited[i][j] && pgm_image[i][j] > 0 ) {

                vector < tuple<int, int> > new_component;

                components.push_back(new_component);

                bfs(visited, components, pgm_image, i, j);
            }

        }
    }

    cout << "Found " << components.size() << " components" << endl;

    // Look for the biggest component

    unsigned int max_comp_index = 0  ;
    unsigned int max_comp_val = 0;

    for ( size_t i = 0; i < components.size(); i++) {

        if ( components[i].size() > max_comp_val ) {

            max_comp_val = components[i].size();
            max_comp_index = i;
        }
    }

    // Create new image with biggest component

    vector< vector<int> > max_comp_image(rows);
    for (int i = 0; i < rows; i++) {
        max_comp_image[i].resize(cols, 0);
    }

    int x;
    int y;

    //cout << "\nIndex of biggest component: " << max_comp_index << endl;
    cout << "\nBiggest component of size: " << components[max_comp_index].size() << endl;

    for (size_t i = 0; i < components[max_comp_index].size(); i++) {
        x = get<0>(components[max_comp_index][i]);
        y = get<1>(components[max_comp_index][i]);

        //cout << "x: " << x << ", y: " << y << endl;

        max_comp_image[x][y] = 255;
    }

    cout << "\nWriting image ..." << endl;

    write_pgm(max_comp_image, "copy.pgm");

    return 0.0;
}
