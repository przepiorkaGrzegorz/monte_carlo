#pragma once
#include <random>

namespace Utils{
    double get_uniform_number();
    double integral(const double x);
};


class Integration{
public:
    virtual ~Integration() = default;
    virtual void print_log(const double a, const double b) const = 0;
    
protected:
    int N, M;
    double mean_value, std;
};