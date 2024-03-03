#include <iostream>
#include <cmath>
#include "../inc/stratified.hpp"


Stratified::Stratified(){
    this->N = 1000000;
    this->M = 10;
    N_m.resize(M, 0);
    bins.resize(M, 0);
    s = new Systematic(100, M);
}

Stratified::Stratified(const int N, const int M){
    this->N = N;
    this->M = M;
    N_m.resize(M, 0);
    bins.resize(M, 0);
    s = new Systematic(100, M);
}

Stratified::~Stratified(){
    delete s;
}

void Stratified::print_log(const double a, const double b) const{
    printf("\nStratified Method\nRange [a, b] = [%.2f, %.2f] for N = %d\n", a, b, N);
}

void Stratified::calculate_std(const double second_moment){
    std = sqrt(second_moment);
}

void Stratified::print_results() const{
    printf("Mean value = %.5f, std = %.5f\n", mean_value, std);
}