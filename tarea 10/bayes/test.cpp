#include <iostream>
#include "bayes.h"

using namespace std;

void test_bayes(){

    cout << "\n" << (predict("email.txt", "spam.txt", "rogelio") ? "Spam" : "Not spam") << "\n";
}

int main(int argc, char const *argv[]) {

    test_bayes();

    return 0;
}
