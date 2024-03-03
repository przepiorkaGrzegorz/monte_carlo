#include "generator.hpp"


int main(){
    srand((unsigned)time(NULL));
    Generator_1D random_generator;
    random_generator.markov_chain(0.5);
    random_generator.acception_rejection();

    printf("\nDone\n");
    return 0;
}