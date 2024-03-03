#pragma once

#include <vector>
#include <numeric>
#include <cmath>
#include "integration.hpp"
#include "systematic.hpp"


class Stratified : Integration{
public:
    Stratified();
    Stratified(const int N, const int M);
    ~Stratified();
    void print_log(const double a, const double b) const override;
    template <typename Function>
    void calculate_integral(Function integral, const double a, const double b);
    void calculate_std(const double second_moment);
    void print_results() const;

private:
    std::vector<int> N_m, bins;
    Systematic* s = nullptr;
};

template <typename Function>
void Stratified::calculate_integral(Function integral, const double a, const double b){
    double dx = (double)(b - a) / (double)M;
    double prob_density = 1.0/(double)M, mean_var = 0.0;
    double xl, xr, xim;
    std::vector<double> first_moment_vec(M, 0.0), second_moment_vec(M, 0.0), variance(M, 0.0);
    mean_value = 0.0;

    s->calculate_integral(integral, a, b);
    std::vector<double> old_std(M, 0.0);
    for(int i = 0; i != M; ++i)
        old_std[i] = sqrt(s->get_variance()[i]);
    
    double denominator = prob_density * std::accumulate(old_std.begin(), old_std.end(), 0.0);

    for(int m = 0; m != M; ++m){
        N_m[m] = (int)(prob_density * N * old_std[m] / denominator);
        xl = a + dx*m;
        xr = xl + dx;
        for(int i = 0; i != N_m[m]; ++i){
            xim = xl + (xr - xl)*Utils::get_uniform_number();
            first_moment_vec[m] += (b - a) * integral(xim);
            second_moment_vec[m] += pow((b - a) * integral(xim), 2);
        }

        if(N_m[m] != 0){
            first_moment_vec[m] = first_moment_vec[m] / (double)N_m[m];
            second_moment_vec[m] = second_moment_vec[m] / (double)N_m[m];
        }

        bins[m] = N_m[m];
    }

    for(int m = 0; m != M; ++m){
        mean_value += prob_density * first_moment_vec[m];
        variance[m] = second_moment_vec[m] - first_moment_vec[m]*first_moment_vec[m];

        if(N_m[m] != 0)
            mean_var += prob_density*prob_density * variance[m] / (double)N_m[m];
    }
    calculate_std(mean_var);
    print_log(a, b);
}