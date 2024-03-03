#include "simple_integration.hpp"


int main(){
    srand((unsigned)time(NULL));
    const int N = 1E5;

    Distribution_2D Uniform_2D(N, 0.0, 0.0, 2.0, 2.0, 2.00, 1.00); // N, x_a, y_a, x_b, y_b, R_a, R_b
    Uniform_2D.generate_gauss_2D();
    Uniform_2D.generate_uniform_on_circle();
    Uniform_2D.generate_uniform_in_circle();
    Uniform_2D.save_distributions({"./data/in_circle_A.dat", "./data/in_circle_B.dat"});

    Simple_Integration si(N);
    si.common_area(Uniform_2D);
    si.calculate_std(Uniform_2D);
    si.print_area_std();
    si.save_common_area("./data/common_area.dat");

    printf("\nDone\n");
    return 0;
}