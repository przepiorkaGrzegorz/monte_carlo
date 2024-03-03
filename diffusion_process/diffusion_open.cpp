#include "diffusion_open.hpp"

#include <iostream>
#include <fstream>


Diffusion_Open::Diffusion_Open() : t_max(10.0), dt(0.1), D(1.0), n_particles(100){
    n_time = (int)(t_max/dt) + 1;
    time.resize(n_time);
    xy_vector.resize(n_time);
    Dxx.resize(n_time-1);
    Dxy.resize(n_time-1);
    Dyy.resize(n_time-1);

    for(int i = 0; i != n_time; ++i)
        time[i] = (double)i*dt;
}

Diffusion_Open::Diffusion_Open(const double t_max, const double dt, const double D, const int n_particles) 
    : t_max(t_max), dt(dt), D(D), n_particles(n_particles){

    n_time = (int)(t_max/dt) + 1;
    time.resize(n_time);
    xy_vector.resize(n_time);
    Dxx.resize(n_time-1);
    Dxy.resize(n_time-1);
    Dyy.resize(n_time-1);

    for(int i = 0; i != n_time; ++i)
        time[i] = (double)i*dt;
}

void Diffusion_Open::time_evolution(){
    xy_vector[0] = std::make_unique<XY_Open>(n_particles);
    for(int i = 1; i != n_time; ++i){
        xy_vector[i] = std::make_unique<XY_Open>(n_particles);
        xy_vector[i]->fill_vector(xy_vector[i-1]->get_x_vector(), xy_vector[i-1]->get_y_vector());
        xy_vector[i]->next_time_step(D, dt);

        Dxx[i-1] = 0.5*(xy_vector[i]->get_xx_mean() - 
            xy_vector[i]->get_x_mean()*xy_vector[i]->get_x_mean())/time[i];
        Dxy[i-1] = 0.5*(xy_vector[i]->get_xy_mean() - 
            xy_vector[i]->get_x_mean()*xy_vector[i]->get_y_mean())/time[i];
        Dyy[i-1] = 0.5*(xy_vector[i]->get_yy_mean() - 
            xy_vector[i]->get_y_mean()*xy_vector[i]->get_y_mean())/time[i];
    }
}

void Diffusion_Open::print_time_vector() const{
    for(auto& t: time)
        std::cout << t << '\n';
}

void Diffusion_Open::print_time_step(const int time_step) const{
    for(int i = 0; i != n_particles; ++i)
        std::cout << "x: " << xy_vector[time_step]->get_xy_pair(i).first << 
            ", y: " << xy_vector[time_step]->get_xy_pair(i).second << '\n';
}

void Diffusion_Open::save_diffusion_coeffs(const std::string path) const{
    std::ofstream file;
    file.open(path);
    for(int i = 0; i != n_time - 1; ++i)
        file << Dxx[i] << ' ' << Dxy[i] << ' ' << Dyy[i] << '\n';

    file.close();
}

void Diffusion_Open::save_positions(const std::string path, const int time_step) const{
    xy_vector[time_step]->save_xy_vector(path);
}