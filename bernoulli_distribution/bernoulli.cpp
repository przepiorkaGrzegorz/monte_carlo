#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include "bernoulli.hpp"


Bernoulli::Bernoulli(){
    N = 1E07;
    p_vec = {0.1, 0.5, 0.9};
    powers = {2, 3, 4, 5, 6, 7};
    p_vec_size = p_vec.size();
    powers_size = powers.size();
    values.resize(p_vec.size(), std::vector<int>(N, 0));
    expected_vals.resize(p_vec.size(), std::vector<double>(powers.size(), 0.0));
    expected_vals_sq.resize(p_vec.size(), std::vector<double>(powers.size(), 0.0));
    var.resize(p_vec.size(), std::vector<double>(powers.size(), 0.0));
    var_teo.resize(p_vec.size(), std::vector<double>(powers.size(), 0.0));
    print_log();
}

Bernoulli::Bernoulli(const int N, const std::vector<double>& p_vec, const std::vector<int>& powers){
    this->N = N;
    this->p_vec = p_vec;
    this->powers = powers;
    p_vec_size = p_vec.size();
    powers_size = powers.size();
    values.resize(p_vec.size(), std::vector<int>(N, 0));
    expected_vals.resize(p_vec.size(), std::vector<double>(powers.size(), 0.0));
    expected_vals_sq.resize(p_vec.size(), std::vector<double>(powers.size(), 0.0));
    var.resize(p_vec.size(), std::vector<double>(powers.size(), 0.0));
    var_teo.resize(p_vec.size(), std::vector<double>(powers.size(), 0.0));
    print_log();
}

void Bernoulli::print_log(){
    printf("N = %d \np = ", N);
    for (auto& p: p_vec)
        printf("%f ", p);
    printf("\npowers = ");
    for (auto& power: powers)
        printf("%d ", power);
}

double Bernoulli::get_uniform_val(){
    return (rand()/(double)RAND_MAX);
}

int Bernoulli::get_bernoulli_val(const double p){
    if (get_uniform_val() <= p) 
        return 1;
    else 
        return 0;
}

void Bernoulli::fill_values(){
    for (int i = 0; i != p_vec_size; ++i){
        for (int j = 0; j != N; ++j)
            values[i][j] = get_bernoulli_val(p_vec[i]);
    }
}

void Bernoulli::calculate_expected_vals(){
    for (int i = 0; i != p_vec_size; ++i){
        for (int j = 0; j != powers_size; ++j){
            var_teo[i][j] = (p_vec[i] - p_vec[i]*p_vec[i])/(pow(10, powers[j]));

            for (int k = 0; k != pow(10, powers[j]); ++k){
                expected_vals[i][j] += values[i][k]/(pow(10, powers[j]));
                expected_vals_sq[i][j] += (values[i][k]*values[i][k])/(pow(10, powers[j]));
            }
        }
    }
}

void Bernoulli::calculate_variance(){
    for (int i = 0; i != p_vec_size; ++i){
        for (int j = 0; j != powers_size; ++j) {
            var[i][j] = (expected_vals_sq[i][j] - expected_vals[i][j]*expected_vals[i][j]) / 
            (pow(10, powers[j]));
        }
    }
}

void Bernoulli::save_data(){
    std::ofstream exp, variance, exp_err, variance_err;
    exp.open("data/exp.dat");
    variance.open("data/var.dat");
    exp_err.open("data/exp_err.dat");
    variance_err.open("data/var_err.dat");
    
    for (int j = 0; j != powers_size; ++j){
        exp_err<<pow(10, powers[j])<<" ";
        variance_err<<pow(10, powers[j])<<" ";
        exp<<pow(10, powers[j])<<" ";
        variance<<pow(10, powers[j])<<" ";
        
        for (int i = 0; i != p_vec_size; ++i){
            exp_err<<fabs(expected_vals[i][j] - p_vec[i])/p_vec[i]<<" ";
            variance_err<<fabs(var[i][j] - var_teo[i][j])/var_teo[i][j]<<" ";
            exp<<expected_vals[i][j]<<" "<<p_vec[i]<<" ";
            variance<<var[i][j]<<" "<<var_teo[i][j]<<" ";
        }
        exp_err<<"\n";
        variance_err<<"\n";
        exp<<"\n";
        variance<<"\n";
    }

    exp.close();
    variance.close();
    exp_err.close();
    variance_err.close();
}