#pragma once

#include <vector>
#include "integration.hpp"


class Basic : public Integration{
    std::vector<int> bins;

public:
    Basic();
    Basic(const int N, const int M);
    void print_log(const double a, const double b) const override;
    template <typename Function> 
    void calculate_integral(Function integral, const double a, const double b);
    void calculate_std(const double second_moment);
    void print_results() const;
};

template <typename Function> 
void Basic::calculate_integral(Function integral, const double a, const double b){
    double dx = (double)(b - a) / (double)M;
    double sum = 0.0, second_moment = 0.0, xi;

    for (int i = 0; i != N; ++i){
        xi = a + (b - a) * Utils::get_uniform_number();
        sum += (b - a) * integral(xi);
        second_moment += pow((b - a) * integral(xi), 2);

        for (int m = 0; m != M; ++m){
            if (xi >= a + dx * m && xi < a + dx * (m + 1)){
                ++bins[m];
                break;
            }
        }
    }

    mean_value = sum / (double)N;
    calculate_std(second_moment / (double)N);
    print_log(a, b);
}