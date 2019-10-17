#include <iostream>
#include "bayes.h"

using namespace std;

void test_bayes(){

    parse_words("email_dataset_clean.txt");
}

int main(int argc, char const *argv[]) {

    test_bayes();

    return 0;
}
