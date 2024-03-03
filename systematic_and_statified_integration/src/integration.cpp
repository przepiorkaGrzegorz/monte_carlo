#define _USE_MATH_DEFINES
#include <cmath>
#include "../inc/integration.hpp"


double Utils::get_uniform_number(){
    return rand()/(RAND_MAX + 1.0);
}

double Utils::integral(const double x){
    return 1.0 + tanh(x);
}