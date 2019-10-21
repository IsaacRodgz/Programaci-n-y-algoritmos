#include <iostream>
#include "cconexo.h"

using namespace std;

void test_cconexo(const string image_file_name){

    cout << "\n" << num_comp_conexas(image_file_name) << endl;
}

int main(int argc, char const *argv[]) {

    if ( argc == 1 ) {
        cout << "\nError: Falta argumento image_file_name" << endl;
    }

    else{
        test_cconexo(argv[1]);
    }

    return 0;
}
