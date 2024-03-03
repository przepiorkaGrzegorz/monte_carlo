#pragma once

#include <vector>
#include <string>


namespace Utils{
    double get_uniform_number();
    double get_length(const double x, const double y);
};

struct Vec_xy{
    std::vector<double> x, y;
};

class Distribution_2D;

class Simple_Integration{
public:
    Simple_Integration();
    Simple_Integration(const int N);
    double get_second_moment(const double first_moment, const double R) const;
    double get_variance(const double first_moment, const double second_moment, const int n) const;
    bool is_common(const double R_b, const double x, const double y) const;
    void fill_tmp_power_vec(std::vector<int>& tmp_power_vec);
    void common_area(const Distribution_2D& obj);
    void calculate_std(const Distribution_2D& obj);
    void save_common_area(const std::string moments_path) const;
    void print_area_std() const;

private:
    int k;
    std::vector<double> common_area_vector, std_vector;
};


class Distribution_2D{
public:
    Distribution_2D();
    Distribution_2D(const int N, const double x_a, const double y_a, 
        const double x_b, const double y_b, const double R_a, const double R_b);
    void print_log() const;
    void resize_vectors();
    void generate_gauss_2D();
    void generate_uniform_on_circle();
    void generate_uniform_in_circle();
    void save_distributions(const std::vector<std::string>& file_path) const;

    friend bool Simple_Integration::is_common(const double, const double, const double) const;
    friend void Simple_Integration::common_area(const Distribution_2D&);
    friend void Simple_Integration::calculate_std(const Distribution_2D&);

private:
    int N;
    double x_a, y_a, x_b, y_b;
    double R_a, R_b;
    Vec_xy gauss_vector, in_circle_vector_A, in_circle_vector_B;
};