#include<iostream>
#include<random>
#include<vector>
#include<fstream>


double uniform() {
    return (rand()/(double)RAND_MAX);
}

double bernoulli(double p) {
    double u = uniform();
    if (u <= p) return 1;
    else return 0;
}


int main() {
    srand((unsigned)time(NULL));
    const int N = 10E07;
    const float p_tab[] = {0.1, 0.5, 0.9};
    const int len_p = sizeof(p_tab)/sizeof(p_tab[0]);
    const int powers[] = {2, 3, 4, 5, 6, 7};
    const int pow_len = sizeof(powers)/sizeof(powers[0]);
    double expected_vals[len_p][pow_len] = {0.0};
    double expected_vals_sq[len_p][pow_len] = {0.0};
    double var[len_p][pow_len] = {0.0};
    double var_teo[len_p][pow_len] = {0.0};
    std::vector<std::vector<double>> vals(len_p, std::vector<double>(N, 0.0));

    for (int i = 0; i != len_p; ++i) {
        for (int j = 0; j != N; ++j) vals[i][j] = bernoulli(p_tab[i]);
    }

    for (int i = 0; i != len_p; ++i) {
        for (int j = 0; j != pow_len; ++j) {
            var_teo[i][j] = (p_tab[i] - p_tab[i]*p_tab[i])/(pow(10, powers[j]));

            for (int k = 0; k != pow(10, powers[j]); ++k) {
                expected_vals[i][j] += vals[i][k]/(pow(10, powers[j]));
                expected_vals_sq[i][j] += (vals[i][k]*vals[i][k])/(pow(10, powers[j]));
            }
        }
    }

    for (int i = 0; i != len_p; ++i) {
        for (int j = 0; j != pow_len; ++j) {
            var[i][j] = (expected_vals_sq[i][j] - expected_vals[i][j] * 
                        expected_vals[i][j])/(pow(10, powers[j]));
        }
    }

    // for (int i = 0; i != len_p; ++i) {
    //     for (int j = 0; j != pow_len; ++j) {
    //         std::printf("%f, ", var_teo[i][j]);
    //     }
    //     std::printf("\n");
    // }
    // std::printf("\n");

    // for (int i = 0; i != len_p; ++i) {
    //     for (int j = 0; j != pow_len; ++j) {
    //         std::printf("%f, ", var[i][j]);
    //     }
    //     std::printf("\n");
    // }

    // Zapis do pliku
    std::ofstream exp, varr, exp_err, var_err;
    exp.open("exp.txt"); // wartość oczekiwana
    varr.open("var.txt"); // wariancja
    exp_err.open("exp_err.txt"); // błąd wartości oczekiwanej
    var_err.open("var_err.txt"); // błąd wariancji
    
    for (int j = 0; j != pow_len; ++j) {
        exp_err<<pow(10, powers[j])<<" ";
        var_err<<pow(10, powers[j])<<" ";
        exp<<pow(10, powers[j])<<" ";
        varr<<pow(10, powers[j])<<" ";
        
        for (int i = 0; i != len_p; ++i) {
            exp_err<<fabs(expected_vals[i][j] - p_tab[i])/p_tab[i]<<" "; // n err
            var_err<<fabs(var[i][j] - var_teo[i][j])/var_teo[i][j]<<" "; // n err
            exp<<expected_vals[i][j]<<" "<<p_tab[i]<<" "; // n exp exp_teo
            varr<<var[i][j]<<" "<<var_teo[i][j]<<" "; // n var var_teo
        }
        exp_err<<"\n";
        var_err<<"\n";
        exp<<"\n";
        varr<<"\n";
    }

    exp.close();
    varr.close();
    exp_err.close();
    var_err.close();

    return 0;
}