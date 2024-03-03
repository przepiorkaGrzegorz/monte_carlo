#include "../inc/basic.hpp"
#include "../inc/systematic.hpp"
#include "../inc/stratified.hpp"


int main(){
    srand((unsigned)time(NULL));

    Basic b;
    b.calculate_integral(Utils::integral, -3.0, 3.0);
    b.print_results();
    printf("\n");

    Systematic sy;
    sy.calculate_integral(Utils::integral, -3.0, 3.0);
    sy.print_results();
    printf("\n");

    Stratified st;
    st.calculate_integral(Utils::integral, -3.0, 3.0);
    st.print_results();

    printf("\nDone\n");
    return 0;
}