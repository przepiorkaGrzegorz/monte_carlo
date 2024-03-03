#include <iostream>
#include "../inc/systematic.hpp"


Systematic::Systematic(){
    this->N = 1000000;
    this->M = 10;
    N_m.resize(M, 0);
    variance.resize(M, 0.0);
}

Systematic::Systematic(const int N, const int M){
    this->N = N;
    this->M = M;
    N_m.resize(M, 0);
    variance.resize(M, 0.0);
}

void Systematic::print_log(const double a, const double b) const{
    printf("\nSystematic Method\nRange [a, b] = [%.2f, %.2f] for N = %d\n", a, b, N);
}

void Systematic::calculate_std(const double second_moment){
    std = sqrt(second_moment);
}

void Systematic::print_results() const{
    printf("Mean value = %.5f, std = %.5f\n", mean_value, std);
}

const std::vector<double>& Systematic::get_variance() const{
    return variance;
}