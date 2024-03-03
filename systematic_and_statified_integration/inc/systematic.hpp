#pragma once

#include <vector>
#include <cmath>
#include "integration.hpp"


class Systematic : public Integration{
public:
    Systematic();
    Systematic(const int N, const int M);
    void print_log(const double a, const double b) const override;
    template <typename Function>
    void calculate_integral(Function integral, const double a, const double b);
    void calculate_std(const double second_moment);
    void print_results() const;
    const std::vector<double>& get_variance() const;

private:
    std::vector<int> N_m;
    std::vector<double> variance;
};

template <typename Function>
void Systematic::calculate_integral(Function integral, const double a, const double b){
    double dx = (double)(b - a) / (double)M;
    double second_moment = 0.0, prob_density = 1.0/(double)M;
    double xl, xr, xim;
    std::vector<double> first_moment_vec(M, 0.0), second_moment_vec(M, 0.0);
    mean_value = 0.0;

    for(int m = 0; m != M; ++m){
        N_m[m] = (int)(prob_density * N);
        xl = a + dx*m;
        xr = xl + dx;
        for(int i = 0; i != N_m[m]; ++i){
            xim = xl + (xr - xl)*Utils::get_uniform_number();
            first_moment_vec[m] += (b - a) * integral(xim);
            second_moment_vec[m] += pow((b - a) * integral(xim), 2);
        }
        first_moment_vec[m] = first_moment_vec[m] / (double)N_m[m];
        second_moment_vec[m] = second_moment_vec[m] / (double)N_m[m];
    }

    for(int m = 0; m != M; ++m){
        mean_value += prob_density * first_moment_vec[m];
        variance[m] = second_moment_vec[m] - first_moment_vec[m]*first_moment_vec[m];
        second_moment += prob_density*prob_density * variance[m] / (double)N_m[m];
    }
    calculate_std(second_moment);
    print_log(a, b);
}