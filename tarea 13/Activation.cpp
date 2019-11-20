#include <math.h>
#include <bits/stdc++.h>

#include "Activation.hpp"

using namespace std;

double Activation::activate(string activation_function, double inner_product){

    if ( activation_function == "relu" ) {

        if ( inner_product < 0.0 )
            return 0.0;
        else
            return inner_product;
    }

    else if ( activation_function == "sigmoid" ) {

        return 1.0/(1.0+exp(-inner_product));
    }

    else

        return 0.0;
}
