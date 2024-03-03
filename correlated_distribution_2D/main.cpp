#include "random_distribution_2D.hpp"


int main(){
    srand((unsigned)time(NULL));

    Distribution_2D d;
    d.generate_gauss_2D();
    d.generate_uniform_on_circle();
    d.generate_uniform_in_circle();
    d.generate_uniform_in_elipse();

    d.print_covariance_matrix(d.get_gauss_vector(), "gauss");
    d.print_covariance_matrix(d.get_in_circle_vector(), "in circle");
    d.print_covariance_matrix(d.get_in_elipse_vector(), "in elipse");

    d.save_data(d.get_gauss_vector(), "./data/gauss.dat");
    d.save_data(d.get_in_circle_vector(), "./data/in_circle.dat");
    d.save_data(d.get_in_elipse_vector(), "./data/in_elipse.dat");

    printf("Done\n");
}