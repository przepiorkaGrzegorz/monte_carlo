#include <iostream>
#include <random>
#include <fstream>
#include "generator.hpp"


double Utils::get_uniform_number(){
    return rand()/(RAND_MAX + 1.0);
}

double Utils::f_x(const double x){
    return 0.8 * (1.0 + x - pow(x, 3));
}

double Utils::F_x(const double x){
    return 0.8 * (x + 0.5*x*x - 0.25*pow(x, 4));
}


Generator_1D::Generator_1D() : N(1E06), k(20), x_left(0.0), x_right(1.0), f_max(1.15){
    width = x_right - x_left;
    bin_size = width/(double)k;
    data_vec.resize(N, 0.0);
    print_log();
}

Generator_1D::Generator_1D(const int N, const int k, const double x_left, 
    const double x_right, const double f_max) : N(N), k(k), x_left(x_left), x_right(x_right), f_max(f_max){

    width = x_right - x_left;
    bin_size = width/(double)k;
    data_vec.resize(N, 0.0);
    print_log();
}

void Generator_1D::print_log() const{
    printf("\nN = %d\nk = %d\nwidth = %0.2f\n\n", N, k, width);
}

void Generator_1D::markov_chain(const double delta, const std::string file_path){
    double U1, p_acc, tmp;
    data_vec[0] = Utils::get_uniform_number();

    for(int i = 0; i != N - 1; ++i){
        U1 = Utils::get_uniform_number();
        tmp = data_vec[i] + (2.0*U1 - 1.0) * delta;
        p_acc = std::min(1.0, Utils::f_x(tmp)/Utils::f_x(data_vec[i]));

        if(Utils::get_uniform_number() < p_acc && (tmp > x_left && tmp < x_right))
            data_vec[i+1] = tmp;
        else 
            data_vec[i+1] = data_vec[i];
    }
    save_data(file_path);
    printf("(markov_chain) Chi2 value = %f\n", chi2_test());

    std::fill(data_vec.begin(), data_vec.end(), 0.0);
}

void Generator_1D::acception_rejection(const std::string file_path){
    double U1, Y;

    for(auto& val: data_vec){
        U1 = x_left + width * Utils::get_uniform_number();
        Y = f_max * Utils::get_uniform_number();

        while(Y > Utils::f_x(U1)){
            U1 = x_left + width * Utils::get_uniform_number();
            Y = f_max * Utils::get_uniform_number();
        }
        val = U1;
    }

    save_data(file_path);
    printf("(acception_rejection) Chi2 value = %f\n", chi2_test());

    std::fill(data_vec.begin(), data_vec.end(), 0.0);
}

void Generator_1D::save_data(const std::string file_path) const{
    std::ofstream file;
    file.open(file_path);

    for(auto& v: data_vec) 
        file << " " << v << "\n";
    file.close();
}

void Generator_1D::bin_vals(std::vector<int>& bins){
    for(auto& val: data_vec) 
        ++bins[(int)(val/bin_size)];
}

void Generator_1D::get_bins_probability(std::vector<double>& bins_probability){
    for(int i = 0; i != k; ++i)
        bins_probability[i] = Utils::F_x(bin_size*((double)i + 1.0)) - Utils::F_x(bin_size*(double)i);
}

double Generator_1D::chi2_test(){
    std::vector<int> bins(k, 0);
    std::vector<double> bins_probability(k, 0.0);
    double chi2_value = 0.0;
    bin_vals(bins);
    get_bins_probability(bins_probability);

    for(int i = 0; i != k; ++i)
        chi2_value += pow((bins[i] - bins_probability[i]*(double)N), 2)/(bins_probability[i]*(double)N);

    return chi2_value;
}