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
    int powers[] = {2, 3, 4, 5, 6, 7};
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



    for (int i = 0; i != len_p; ++i) {
        for (int j = 0; j != pow_len; ++j) {
            std::printf("%f, ", var_teo[i][j]);
        }
        std::printf("\n");
    }
    std::printf("\n");

    for (int i = 0; i != len_p; ++i) {
        for (int j = 0; j != pow_len; ++j) {
            std::printf("%f, ", var[i][j]);
        }
        std::printf("\n");
    }


    // Zapis do pliku
    std::ofstream exp_file, var_file;
    exp_file.open("exp_err.txt");
    var_file.open("var_err.txt");

    for (int j = 0; j != pow_len; ++j) {
        exp_file<<pow(10, powers[j])<<" ";
        var_file<<pow(10, powers[j])<<" ";
        
        for (int i = 0; i != len_p; ++i) {
            exp_file<<fabs(expected_vals[i][j] - p_tab[i])/p_tab[i]<<" ";
            var_file<<fabs(var[i][j] - var_teo[i][j])/var_teo[i][j]<<" ";
        }
        exp_file<<"\n";
        var_file<<"\n";
    }

    exp_file.close();
    var_file.close();

    return 0;
}