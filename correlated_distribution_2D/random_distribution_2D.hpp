#pragma once

#include <vector>
#include <string>


namespace Utils{
    double get_uniform_number();
    double get_length(const double x, const double y);
}

struct Vec_xy{
    std::vector<double> x, y;
};

class Distribution_2D{
public:
    Distribution_2D();
    Distribution_2D(const int N, const double alpha, const double b1, const double b2);
    void print_log() const;
    void generate_gauss_2D();
    void generate_uniform_on_circle();
    void generate_uniform_in_circle();
    void generate_uniform_in_elipse();
    double mean_value(const std::vector<double>& vec) const;
    double mean2_value(const std::vector<double>& vec) const;
    double mean_value2(const std::vector<double>& vec_1, const std::vector<double>& vec_2) const;
    void print_covariance_matrix(const double* matrix, const int size) const;
    void print_covariance_matrix(const Vec_xy&, const char* str) const;
    double get_correlation_coefficient(const double* matrix) const;
    void save_data(const Vec_xy& data_vector, const std::string file_path) const;
    const Vec_xy& get_gauss_vector() const;
    const Vec_xy& get_in_circle_vector() const;
    const Vec_xy& get_in_elipse_vector() const;

private:
    int N;
    double alpha, b1, b2;
    Vec_xy gauss_vector, in_circle_vector, in_elipse_vector;
};