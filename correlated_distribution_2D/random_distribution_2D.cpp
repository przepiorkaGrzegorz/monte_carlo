#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include "random_distribution_2D.hpp"


double Utils::get_uniform_number(){
    return rand()/(RAND_MAX + 1.0);
}

double Utils::get_length(const double x, const double y){
    return sqrt(x*x + y*y);
}


Distribution_2D::Distribution_2D() : N(10000), alpha(M_PI/4.0), b1(1.0), b2(0.2){
    gauss_vector.x.resize(N, 0.0);
    gauss_vector.y.resize(N, 0.0);
    in_circle_vector.x.resize(N, 0.0);
    in_circle_vector.y.resize(N, 0.0);
    in_elipse_vector.x.resize(N, 0.0);
    in_elipse_vector.y.resize(N, 0.0);

    print_log();
}

Distribution_2D::Distribution_2D(const int N, const double alpha, const double b1, const double b2)
    : N(N), alpha(alpha), b1(b1), b2(b2){
    
    gauss_vector.x.resize(N, 0.0);
    gauss_vector.y.resize(N, 0.0);
    in_circle_vector.x.resize(N, 0.0);
    in_circle_vector.y.resize(N, 0.0);
    in_elipse_vector.x.resize(N, 0.0);
    in_elipse_vector.y.resize(N, 0.0);

    print_log();
}

void Distribution_2D::print_log() const{
    printf("N = %d\nalpha = %.2f\nb1 = %.2f\nb2 = %.2f\n", N, alpha, b1, b2);
}


void Distribution_2D::generate_gauss_2D(){
    double U1, U2;
    for(int i = 0; i != N; ++i){
        U1 = Utils::get_uniform_number();
        U2 = Utils::get_uniform_number();
        gauss_vector.x[i] = sqrt(-2.0*log(1.0 - U1))*cos(2*M_PI*U2);
        gauss_vector.y[i] = sqrt(-2.0*log(1.0 - U1))*sin(2*M_PI*U2);
    }
}


void Distribution_2D::generate_uniform_on_circle(){
    double denominator;
    for(int i = 0; i != N; ++i){
        denominator = Utils::get_length(gauss_vector.x[i], gauss_vector.y[i]);
        if(denominator != 0.0){
            in_circle_vector.x[i] = gauss_vector.x[i]/denominator;
            in_circle_vector.y[i] = gauss_vector.y[i]/denominator;
        }
    }
}

void Distribution_2D::generate_uniform_in_circle(){
    double U1, r;
    for(int i = 0; i != N; ++i){
        U1 = Utils::get_uniform_number();
        r = sqrt(U1);

        in_circle_vector.x[i] = r*in_circle_vector.x[i];
        in_circle_vector.y[i] = r*in_circle_vector.y[i];
    }
}

void Distribution_2D::generate_uniform_in_elipse(){
    const double ex[2] = {1.0, 0.0}, ey[2] = {0.0, 1.0};
    double r1[2]{}, r2[2]{};
    double R[2][2]{}, A[2][2]{};
    R[0][0] = cos(alpha);
    R[0][1] = sin(alpha);
    R[1][0] = -sin(alpha);
    R[1][1] = cos(alpha);

    for(int i = 0; i != 2; ++i){
        for(int j = 0; j != 2; ++j) {
            r1[i] += b1*R[j][i]*ex[j];
            r2[i] += b2*R[j][i]*ey[j];
        }
    }

    A[0][0] = r1[0];
    A[0][1] = r1[1];
    A[1][0] = r2[0];
    A[1][1] = r2[1];

    for(int i = 0; i != N; ++i){
        in_elipse_vector.x[i] = A[0][0]*in_circle_vector.x[i] +
            A[1][0]*in_circle_vector.y[i];
        in_elipse_vector.y[i] = A[0][1]*in_circle_vector.x[i] + 
            A[1][1]*in_circle_vector.y[i];
    }
}

double Distribution_2D::mean_value(const std::vector<double>& vec) const{
    return std::accumulate(vec.begin(), vec.end(), 0.0)/N;
}

double Distribution_2D::mean2_value(const std::vector<double>& vec) const{
    double sum = 0.0;
    for(const auto& v: vec) 
        sum += v*v;
    return sum/N;
}

double Distribution_2D::mean_value2(const std::vector<double>& vec_1, const std::vector<double>& vec_2) const{
    double sum = 0.0;
    for(int i = 0; i != N; ++i)
        sum += vec_1[i]*vec_2[i];
    return sum/N;
}

void Distribution_2D::print_covariance_matrix(const double* matrix, const int size) const{
    for(int i = 0; i != size; ++i){
        for(int j = 0; j != size; ++j)
            printf("%f, ", *(matrix + i*size + j));
        
        printf("\n");
    }
}

double Distribution_2D::get_correlation_coefficient(const double* matrix) const{
    return *(matrix + 1)/sqrt(*matrix*(*(matrix + 3)));
}

void Distribution_2D::print_covariance_matrix(const Vec_xy& src_vec, const char* str) const{
    
    double cov_matrix[2][2]{};
    cov_matrix[0][0] = mean2_value(src_vec.x) - pow(mean_value(src_vec.x), 2);
    cov_matrix[0][1] = mean_value2(src_vec.x, src_vec.y);
    cov_matrix[1][0] = cov_matrix[0][1];
    cov_matrix[1][1] = mean2_value(src_vec.y) - pow(mean_value(src_vec.y), 2);
    printf("\n[%s]\n", str);
    printf("Covariance matrix:\n");
    print_covariance_matrix(cov_matrix[0], 2);
    printf("Correlation coefficient: %f\n\n", get_correlation_coefficient(cov_matrix[0]));
}

void Distribution_2D::save_data(const Vec_xy& data_vector, const std::string file_path) const{
    std::ofstream file;
    file.open(file_path);

    for(int i = 0; i != N; ++i)
        file<<data_vector.x[i]<<" "<<data_vector.y[i]<<"\n";

    file.close();
}

const Vec_xy& Distribution_2D::get_gauss_vector() const{
    return gauss_vector;
}

const Vec_xy& Distribution_2D::get_in_circle_vector() const{
    return in_circle_vector;
}

const Vec_xy& Distribution_2D::get_in_elipse_vector() const{
    return in_elipse_vector;
}