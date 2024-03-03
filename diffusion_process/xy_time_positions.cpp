#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include "xy_time_positions.hpp"


double Utils::get_uniform_number(){
    return rand()/(RAND_MAX + 1.0);
}

std::pair<double, double> Utils::normal_dist(){
    double u1 = get_uniform_number();
    double u2 = get_uniform_number();
    return std::make_pair(sqrt(-2.0*log(1.0 - u1)) * cos(2.0*M_PI*u2), 
            sqrt(-2.0*log(1.0 - u1)) * sin(2.0*M_PI*u2));
}

XY_Open::XY_Open() : n(100){
    xy.first.resize(n, 0.0);
    xy.second.resize(n, 0.0);
}

XY_Open::XY_Open(const int n) : n(n){
    xy.first.resize(n, 0.0);
    xy.second.resize(n, 0.0);
}

XY_Open::XY_Open(const int n, const double x, const double y) : n(n){
    xy.first.resize(n, x);
    xy.second.resize(n, y);
}

double XY_Open::get_dx(const double D, const double dt) const{
    return sqrt(2.0*D*dt) * Utils::normal_dist().first; 
}

double XY_Open::get_dy(const double D, const double dt) const{
    return sqrt(2.0*D*dt) * Utils::normal_dist().second; 
}

void XY_Open::next_time_step(const double D, const double dt){
    for(int i = 0; i != n; ++i){
        xy.first[i] += get_dx(D, dt);
        xy.second[i] += get_dy(D, dt);
    }
}

std::vector<double> XY_Open::get_x_vector() const{
    return xy.first;
}

std::vector<double> XY_Open::get_y_vector() const{
    return xy.second;
}

std::pair<double, double> XY_Open::get_xy_pair(const int i) const{
    return {xy.first[i], xy.second[i]};
}

void XY_Open::fill_vector(const std::vector<double>& x, const std::vector<double>& y){
    for(int i = 0; i != n; ++i){
        xy.first[i] = x[i];
        xy.second[i] = y[i];
    }
}

void XY_Open::fill_xy_pair(const double x, const double y, const int i){
    xy.first[i] = x;
    xy.second[i] = y;
}

double XY_Open::get_x_mean() const{
    return std::accumulate(xy.first.begin(), xy.first.end(), 0.0)/(double)n;
}

double XY_Open::get_y_mean() const{
    return std::accumulate(xy.second.begin(), xy.second.end(), 0.0)/(double)n;
}

double XY_Open::get_xy_mean() const{
    std::vector<double> tmp(n, 0.0);
    for(int i = 0; i != n; ++i)
        tmp[i] = xy.first[i] * xy.second[i];

    return std::accumulate(tmp.begin(), tmp.end(), 0.0)/(double)n;
}

double XY_Open::get_xx_mean() const{
    std::vector<double> tmp(n, 0.0);
    for(int i = 0; i != n; ++i)
        tmp[i] = xy.first[i] * xy.first[i];

    return std::accumulate(tmp.begin(), tmp.end(), 0.0)/(double)n;
}

double XY_Open::get_yy_mean() const{
    std::vector<double> tmp(n, 0.0);
    for(int i = 0; i != n; ++i)
        tmp[i] = xy.second[i] * xy.second[i];

    return std::accumulate(tmp.begin(), tmp.end(), 0.0)/(double)n;
}

void XY_Open::save_xy_vector(const std::string path){
    std::ofstream file;  
    file.open(path);
    for(int i = 0; i != n; ++i)
        file << xy.first[i] << ' ' << xy.second[i] << ' ' << '\n';

    file.close();
}