#include <random>
#include <iostream>
#include "bernoulli.hpp"


int main(){
    srand((unsigned)time(NULL));
    Bernoulli b;
    b.fill_values();
    b.calculate_expected_vals();
    b.calculate_variance();
    b.save_data();

    std::cout<<"\nDone\n";
    return 0;
}