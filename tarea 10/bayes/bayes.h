#ifndef bayes_H
#define bayes_H

#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> read_data(const std::string dataset_file, int class_flag);

std::unordered_map< std::string, int > parse_words(std::vector<std::string> emails, int& num_msgs, int& num_words);

bool predict(const std::string dataset_file, const std::string email);

void eval( const std::string dataset_file );

#endif
