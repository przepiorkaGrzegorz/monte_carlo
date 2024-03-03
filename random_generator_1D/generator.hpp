#pragma once
#include <vector>
#include <string>


namespace Utils{
    double get_uniform_number();
    double f_x(const double x);
    double F_x(const double x);
};


class Generator_1D{
public:
    Generator_1D();
    Generator_1D(const int N, const int k, const double x_left, const double x_right, const double f_max);
    void print_log() const;
    void markov_chain(const double delta, const std::string file_path = "./data/markov_chain.dat");
    void acception_rejection(const std::string file_path = "./data/acception_rejection.dat");
    void save_data(const std::string file_path) const;
    void bin_vals(std::vector<int>& bins);
    void get_bins_probability(std::vector<double>& bins_probability);
    double chi2_test();

private:
    int N, k;
    double x_left, x_right, width, bin_size, f_max;
    std::vector<double> data_vec;
};