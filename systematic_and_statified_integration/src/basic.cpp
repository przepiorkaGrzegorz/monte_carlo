#include <iostream>
#include <cmath>
#include "../inc/basic.hpp"


Basic::Basic(){
    this->N = 100000;
    this->M = 10;
    bins.resize(M, 0);
}

Basic::Basic(const int N, const int M){
    this->M = M;
    this->N = N;
    bins.resize(M, 0);
}

void Basic::print_log(const double a, const double b) const{
    printf("\nBasic Method\nRange [a, b] = [%.2f, %.2f] for N = %d\n", a, b, N);
}

void Basic::calculate_std(const double second_moment){
    std = sqrt((second_moment - mean_value*mean_value) / (double)N);
}

void Basic::print_results() const{
    printf("Mean value = %.5f, std = %.5f\n", mean_value, std);
}