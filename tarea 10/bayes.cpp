#include <iostream>
#include<bits/stdc++.h>
#include <fstream>
#include <string>

using namespace std;

unordered_map<string, int> parse_words( const string file_name, int& num_msgs, int& num_words ){

    num_msgs = 0;
    num_words = 0;

    // Read file with email dataset

    ifstream file(file_name);

    // Hash map to save word fequencies

    unordered_map<string, int> word_freq;

    // process emails, one per line

    string line;

    while (getline(file, line)) {

        // count number of messages read

        num_msgs += 1;

        stringstream words_stream(line);

        string word;

        // break message into words (tokenize) and increment count for each word

        while( getline(words_stream, word, ' ') ) {

            num_words += 1;

            word_freq[word] += 1;
        }
    }
    /*
    // Printing the token vector
    unordered_map<string, int>:: iterator p;
    for (p = word_freq.begin(); p != word_freq.end(); p++)
        cout << "\n word: " << p->first << ", frec: " << p->second << endl;
        */
    return word_freq;
}

bool predict( const string email_file, const string spam_file, const string test_msg ){

    // tables with word frequencies

    unordered_map<string, int> email_freq;
    unordered_map<string, int> spam_freq;

    // counts of words and messages

    int email_num_words;
    int spam_num_words;

    int email_num_msgs;
    int spam_num_msgs;

    // Calculate table freqs and counts

    email_freq = parse_words(email_file, email_num_msgs, email_num_words);
    spam_freq = parse_words(spam_file, spam_num_msgs, spam_num_words);

    // Remove words not contained in both tables

    // TODO: Update email_num_words and spam_num_words after intersection

    for (auto it = email_freq.begin(); it != email_freq.end();) {

        if ( spam_freq.find(it->first) == spam_freq.end() )
            it = email_freq.erase(it);
        else
            it++;
    }

    for (auto it = spam_freq.begin(); it != spam_freq.end();) {

        if ( email_freq.find(it->first) == email_freq.end() )
            it = spam_freq.erase(it);
        else
            it++;
    }

    // Size of vocabulary

    int vocab_size = email_freq.size() + spam_freq.size();

    // Calculate probability of mail test_msg being spam or not
    // and return label with max probability
    // return argmax(c) P( test_msg | c ) * P( c )

    // Calculate probabilities

    // Start with a priori probabilities P(email) and P(spam)

    double email_prob = static_cast<double>(email_num_msgs) / (email_num_msgs + spam_num_msgs);
    double spam_prob = static_cast<double>(spam_num_msgs) / (email_num_msgs + spam_num_msgs);

    string word;
    stringstream words_stream(test_msg);

    // Calculate P(test_msg | email)*P(email) and P(test_msg | spam)*P(spam)

    while ( getline(words_stream, word, ' ') ) {

        // P(test_msg | email)

        if ( email_freq.find(word) != email_freq.end() )
            email_prob *= ( static_cast<double>( email_freq[word] + 1 ) / ( email_num_words + vocab_size ) );
        else
            email_prob *= (1.0 / vocab_size);

        // // P(test_msg | spam)

        if ( spam_freq.find(word) != spam_freq.end() )
            spam_prob *= ( static_cast<double>( spam_freq[word] + 1 ) / ( spam_num_words + vocab_size ) );
        else
            spam_prob *= (1.0 / vocab_size);
    }

    cout << "\nEmail prob: " << email_prob << "\nSpam prob: " << spam_prob << "\n\n";

    return spam_prob > email_prob;
}
