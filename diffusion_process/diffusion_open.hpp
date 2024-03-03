#pragma once

#include <string>
#include <memory>
#include "xy_time_positions.hpp"


class Diffusion_Open{
public:
    Diffusion_Open();
    Diffusion_Open(const double t_max, const double dt, const double D, const int n);
    void time_evolution();
    void print_time_vector() const;
    void print_time_step(const int time_step) const;
    void save_diffusion_coeffs(const std::string path) const;
    void save_positions(const std::string path, const int time_step) const;

private:
    double t_max, dt, D;
    int n_time, n_particles;
    std::vector<double> time;
    std::vector<std::unique_ptr<XY_Open>> xy_vector;
    std::vector<double> Dxx, Dxy, Dyy;
};