#ifndef cconexo_H
#define cconexo_H

#include<bits/stdc++.h>
#include<string>

std::vector< std::vector<int> > read_pgm(const std::string image_file_name);

void write_pgm(std::vector< std::vector<int> > pgm_image, const std::string image_file_name);

void bfs(std::vector< std::vector<bool> > &visited, std::vector< std::vector < std::tuple<int, int> > > &components, std::vector< std::vector<int> > pgm_image, int i, int j);

double num_comp_conexas(const std::string image_file_name);

#endif
