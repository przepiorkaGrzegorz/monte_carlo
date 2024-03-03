#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include "simple_integration.hpp"


double Utils::get_uniform_number(){
    return rand()/(RAND_MAX + 1.0);
}

double Utils::get_length(const double x, const double y){
    return sqrt(x*x + y*y);
}

Distribution_2D::Distribution_2D(){
    N = 1E06;
    x_a = 0.0;
    y_a = 0.0;
    x_b = 0.0;
    y_b = 0.0;
    R_a = 1.0;
    R_b = 2.0;

    resize_vectors();
    print_log();
}

Distribution_2D::Distribution_2D(const int N, const double x_a, const double y_a, 
        const double x_b, const double y_b, const double R_a, const double R_b){
    this->N = N;
    this->x_a = x_a;
    this->y_a = y_a;
    this->x_b = x_b;
    this->y_b = y_b;
    this->R_a = R_a;
    this->R_b = R_b;

    resize_vectors();
    print_log();
}

void Distribution_2D::resize_vectors(){
    gauss_vector.x.resize(N, 0.0);
    gauss_vector.y.resize(N, 0.0);
    in_circle_vector_A.x.resize(N, 0.0);
    in_circle_vector_A.y.resize(N, 0.0);
    in_circle_vector_B.x.resize(N, 0.0);
    in_circle_vector_B.y.resize(N, 0.0);
}

void Distribution_2D::print_log() const{
    printf("\nNumber of points, N = %d\nCoordinates of circles:\nx_a = %.2f, "
            "y_a = %.2f, R_a = %.2f\nx_b = %.2f, y_b = %.2f, R_b = %.2f", 
            N, x_a, y_a, R_a, x_b, y_b, R_b);
}

void Distribution_2D::generate_gauss_2D(){
    double U1, U2;
    for(int i = 0; i != N; ++i){
        U2 = Utils::get_uniform_number();
        U1 = Utils::get_uniform_number();
        gauss_vector.x[i] = sqrt(-2.0*log(U1))*cos(2.0*M_PI*U2);
        gauss_vector.y[i] = sqrt(-2.0*log(U1))*sin(2.0*M_PI*U2);
    }
}

void Distribution_2D::generate_uniform_on_circle(){
    double denominator;
    for(int i = 0; i != N; ++i){
        denominator = Utils::get_length(gauss_vector.x[i], gauss_vector.y[i]);
        if(denominator != 0.0){
            in_circle_vector_A.x[i] = gauss_vector.x[i]/denominator;
            in_circle_vector_A.y[i] = gauss_vector.y[i]/denominator;
            in_circle_vector_B.x[i] = gauss_vector.x[i]/denominator;
            in_circle_vector_B.y[i] = gauss_vector.y[i]/denominator;
        }
    }
}

void Distribution_2D::generate_uniform_in_circle(){
    double r_a, r_b;
    for(int i = 0; i != N; ++i){
        r_a = sqrt(Utils::get_uniform_number());
        r_b = sqrt(Utils::get_uniform_number());

        in_circle_vector_A.x[i] = R_a * r_a * in_circle_vector_A.x[i] + x_a;
        in_circle_vector_A.y[i] = R_a * r_a * in_circle_vector_A.y[i] + y_a;
        in_circle_vector_B.x[i] = R_b * r_b * in_circle_vector_B.x[i] + x_b;
        in_circle_vector_B.y[i] = R_b * r_b * in_circle_vector_B.y[i] + y_b;
    }
}

void Distribution_2D::save_distributions(const std::vector<std::string>& file_path) const{
    std::ofstream in_circle_file_A, in_circle_file_B;
    in_circle_file_A.open(file_path[0]);
    in_circle_file_B.open(file_path[1]);

    for(int i = 0; i != N; ++i){
        in_circle_file_A << in_circle_vector_A.x[i] << " " << in_circle_vector_A.y[i] << "\n";
        in_circle_file_B << in_circle_vector_B.x[i] << " " << in_circle_vector_B.y[i] << "\n";
    }
    in_circle_file_A.close();
    in_circle_file_B.close();
}


Simple_Integration::Simple_Integration(){
    this->k = 5;
    common_area_vector.resize(k, 0.0);
    std_vector.resize(k, 0.0);
}

Simple_Integration::Simple_Integration(const int N){
    this->k = (int)log10(N) - 1;
    common_area_vector.resize(k, 0.0);
    std_vector.resize(k, 0.0);
}

bool Simple_Integration::is_common(const double R_b, const double x, const double y) const{
    return (x*x + y*y <= R_b*R_b) ? 1 : 0;
}

void Simple_Integration::common_area(const Distribution_2D& obj){
    int sum = 0, j = 0;
    std::vector<int> tmp_power_vec;
    fill_tmp_power_vec(tmp_power_vec);

    for(int i = 1; i != obj.N + 1; ++i){
        sum += is_common(obj.R_b, 
            (obj.in_circle_vector_A.x[i-1] - obj.x_b), 
            (obj.in_circle_vector_A.y[i-1] - obj.y_b));

        if(i == pow(10, tmp_power_vec[j])){
            common_area_vector[j] = (double)sum*(M_PI * obj.R_a * obj.R_a) / (double)i;
            ++j;
        }
    }
}

void Simple_Integration::fill_tmp_power_vec(std::vector<int>& tmp_power_vec){
    for(int l = 2; l != k + 2; ++l)
        tmp_power_vec.push_back(l);
}

double Simple_Integration::get_second_moment(const double first_moment, const double R) const{
    return M_PI * R * R * first_moment;
}

double Simple_Integration::get_variance(const double first_moment, const double second_moment, 
    const int n) const{
    return (second_moment - first_moment*first_moment)/(double)n;
}

void Simple_Integration::calculate_std(const Distribution_2D& obj){
    double tmp_R = obj.R_a > obj.R_b ? obj.R_a : obj.R_b;

    for(int i = 0; i != k; ++i){
        std_vector[i] = sqrt(get_variance(common_area_vector[i], 
            get_second_moment(common_area_vector[i], tmp_R), 
            pow(10, i + 2)));
    }
}

void Simple_Integration::save_common_area(const std::string moments_path) const{
    std::ofstream file;
    file.open(moments_path);

    for(int i = 0; i != k; ++i)
        file << pow(10, i + 2) << ' ' << common_area_vector[i] << ' ' << std_vector[i] << '\n';

    file.close();
}

void Simple_Integration::print_area_std() const{
    printf("\n\nCommon area = %.6f, std = %.6f\n", common_area_vector[k-1], std_vector[k-1]);
}