#include <iostream>
#include <random>

#include "diffusion_open.hpp"


int main(){
    srand((unsigned)time(NULL));

    for(int i = 2; i != 6; ++i){
        Diffusion_Open open_system_diffusion(10.0, 0.1, 1.0, (int)pow(10, i)); // t_max, dt, D, n_particles
        open_system_diffusion.time_evolution();
        std::string file_path = "data/coeffs_open_" + std::to_string(i) + ".dat";
        open_system_diffusion.save_diffusion_coeffs(file_path);

        if(5 == i){
            open_system_diffusion.save_positions("data/pos1.dat", 1);
            open_system_diffusion.save_positions("data/pos40.dat", 40);
        }
        printf("n_particles = %d\n", (int)pow(10, i));
    }

    printf("\nDone\n");
    return 0;
}