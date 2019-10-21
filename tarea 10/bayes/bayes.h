#ifndef bayes_H
#define bayes_H

#include <string>
#include <unordered_map>

std::unordered_map< std::string, int > parse_words(const std::string file_name, int& num_msgs, int& num_words);

bool predict(const std::string email_file, const std::string spam_file, const std::string test_msg);

#endif
