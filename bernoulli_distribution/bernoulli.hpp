#pragma once
#include <vector>


class Bernoulli{
public:
    Bernoulli();
    Bernoulli(const int N, const std::vector<double>& p_vec, const std::vector<int>& powers);
    void print_log();
    double get_uniform_val();
    int get_bernoulli_val(const double p);
    void fill_values();
    void calculate_expected_vals();
    void calculate_variance();
    void save_data();

private:
    int N, p_vec_size, powers_size;
    std::vector<double> p_vec;
    std::vector<int> powers;
    std::vector<std::vector<int>> values;
    std::vector<std::vector<double>> expected_vals, expected_vals_sq, var, var_teo;
};