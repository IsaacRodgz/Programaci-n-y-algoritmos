#include <iostream>
#include<bits/stdc++.h>
#include <fstream>
#include <string>

using namespace std;

unordered_map<string, int> parse_words(const string file_name){

    ifstream file(file_name);
    string line;

    vector <string> inbox_words;

    unordered_map<string, int> frec_inbox;

    // process inbox messages, read message per line

    while (getline(file, line)) {

        stringstream check1(line);

        string intermediate;

        // Tokenizing w.r.t. space ""
        while( getline(check1, intermediate, ' ') ) {

            inbox_words.push_back(intermediate);
            frec_inbox[intermediate] += 1;
        }
    }

    // Printing the token vector
    unordered_map<string, int>:: iterator p;
    for (p = frec_inbox.begin(); p != frec_inbox.end(); p++)
        cout << "\n word: " << p->first << ", frec: " << p->second << endl;

    return frec_inbox;
}
