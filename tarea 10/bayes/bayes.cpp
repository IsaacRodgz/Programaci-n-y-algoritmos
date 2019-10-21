#include <iostream>
#include<bits/stdc++.h>
#include <fstream>
#include <string>

using namespace std;

vector<string> read_data(const string dataset_file, int class_flag){

    //

    string class_pred;

    if ( class_flag == 0 )
        class_pred = "ham";
    else
        class_pred = "spam";

    vector<string> data;

    // Read file with email dataset

    ifstream file(dataset_file);
    string line;

    // Ignore headers

    getline(file, line);

    // Read examples

    int index;

    while ( getline(file, line) ) {

        index = line.find(",");

        if ( line.substr(0, index) == class_pred ) {

            data.push_back( line.substr(index+1, line.size()-4) );
        }
    }

    return data;
}

unordered_map<string, int> parse_words( vector<string> emails, int& num_msgs, int& num_words ){

    num_msgs = 0;
    num_words = 0;

    // Hash map to save word fequencies

    unordered_map<string, int> word_freq;

    // process emails, one per line

    string line;

    for (size_t i = 0; i < emails.size(); i++) {

        line = emails[i];

        string a;
        for( char c : line ) if ( (isalnum(c) && c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9') || c == ' ' )
            a += tolower(c);

        //cout << a << endl;

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

bool predict( const string dataset_file, const string email ){

    // read dataset

    vector<string> spam_data = read_data(dataset_file, 1);
    vector<string> notspam_data = read_data(dataset_file, 0);

    // tables with word frequencies

    unordered_map<string, int> email_freq;
    unordered_map<string, int> spam_freq;

    // counts of words and messages

    int email_num_words;
    int spam_num_words;

    int email_num_msgs;
    int spam_num_msgs;


    // Calculate table freqs and counts

    email_freq = parse_words(notspam_data, email_num_msgs, email_num_words);
    spam_freq = parse_words(spam_data, spam_num_msgs, spam_num_words);

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
    stringstream words_stream(email);

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

void eval( const string dataset_file ){

    // read dataset

    vector<string> spam_data = read_data(dataset_file, 1);
    vector<string> notspam_data = read_data(dataset_file, 0);

    // Divide training and test examples

    int index_spam = spam_data.size() * 0.8;
    int index_notspam = notspam_data.size() * 0.8;

    vector<string> spam_train_data;
    vector<string> notspam_train_data;
    vector<string> test_data;
    vector<int> pred;

    for (int i = 0; i < index_spam; i++) {
        spam_train_data.push_back(spam_data[i]);
    }

    for (int i = 0; i < index_notspam; i++) {
        notspam_train_data.push_back(notspam_data[i]);
    }

    for (int i = index_spam; i < int(spam_data.size()); i++) {
        test_data.push_back(spam_data[i]);
        pred.push_back(1);
    }

    for (int i = index_notspam; i < int(notspam_data.size()); i++) {
        test_data.push_back(notspam_data[i]);
        pred.push_back(0);
    }

    // tables with word frequencies

    unordered_map<string, int> email_freq;
    unordered_map<string, int> spam_freq;

    // counts of words and messages

    int email_num_words;
    int spam_num_words;

    int email_num_msgs;
    int spam_num_msgs;


    // Calculate table freqs and counts

    email_freq = parse_words(notspam_train_data, email_num_msgs, email_num_words);
    spam_freq = parse_words(spam_train_data, spam_num_msgs, spam_num_words);

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

    double accuracy = 0;

    for (int i = 0; i < int(test_data.size()); i++) {

        // Start with a priori probabilities P(email) and P(spam)

        double email_prob = static_cast<double>(email_num_msgs) / (email_num_msgs + spam_num_msgs);
        double spam_prob = static_cast<double>(spam_num_msgs) / (email_num_msgs + spam_num_msgs);

        string word;
        stringstream words_stream(test_data[i]);

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

        if ( ( pred[i] == 1 && spam_prob > email_prob ) || ( pred[i] == 0 && spam_prob <= email_prob ) ) {
            accuracy += 1;
        }
    }

    cout << "\nAccuracy of Naive Bayes predictor of: " << accuracy/(static_cast<double>(test_data.size())) << "\n" << endl;

}
