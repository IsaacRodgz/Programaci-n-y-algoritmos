#include <iostream>
#include "bayes.h"

using namespace std;

void test_bayes(const string dataset_file, const string email){

    //cout << "\n" << (predict(dataset_file, email) ? "Spam" : "Not spam") << "\n";
    eval(dataset_file);

}

int main(int argc, char const *argv[]) {

    if ( argc == 1 ) {
        cout << "\nError: Faltan argumentos: dataset_file, email" << endl;
    }

    else if ( argc == 2 ) {
        eval(argv[1]);
    }

    else{
        predict(argv[1], argv[2]);
    }

    return 0;
}
