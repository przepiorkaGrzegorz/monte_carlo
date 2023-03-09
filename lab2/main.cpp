#include<iostream>
#include<random>
#include<vector>
#include<fstream>
#include<string>


double uniform() {
    return rand()/(RAND_MAX + 1.0) ;
}

double fX(const double x) {
    return 0.8 * (1 + x - pow(x, 3));
}

double FX(const double x) {
    return 0.8 * (x + 0.5*x*x + 0.25*pow(x, 4));
}

void probDensity(std::vector<double>& vec, const int N, const double width) {
    double dx = width/(N - 1);
    for (int x = 0; x != N; ++x) vec[x] = fX(x * dx);
}

void composite(std::vector<double>& vec) {
    const double g1 = 0.8;
    double U1, U2;

    for (auto &v: vec) {
        U1 = uniform();
        U2 = uniform();

        if (U1 <= g1) v = U2;
        else v = sqrt(1 - sqrt(1 - U2));
    }
}

void markovChain(std::vector<double>& vec, const int N, const double delta) {
    double U1, pAcc, tmp;
    vec[0] = uniform();

    for (int i = 0; i != N-1; ++i) {
        U1 = uniform();
        tmp = vec[i] + (2*U1 - 1) * delta;
        pAcc = std::min(1.0, fX(tmp) / fX(vec[i]));

        if ((tmp > 0.0 && tmp < 1.0) && uniform() <= pAcc) vec[i+1] = tmp;
        else vec[i+1] = vec[i];
    }
}


void rejection(std::vector<double>& vec) {
    double U1, G2;

    for (auto &v: vec) {
        U1 = uniform();
        G2 = 1.15 * uniform();
    
        while (G2 > fX(U1)) {
            U1 = uniform();
            G2 = 1.15 * uniform();
        }
        v = U1;
    }
}


void saveToFile(const std::vector<double>& vec, const std::string filePath) {
    std::ofstream file;
    file.open(filePath);

    for (auto &v: vec) {
        file << " " << v << "\n";
    }

    file.close();
}


void printn(const std::vector<double>& vec, const int n) {
    for (int i = 0; i != n; ++i) printf("%f, ", vec[i]);
    printf("\n");
}


int main() {
    const int N = 10E06;
    std::vector<double> fVec(N, 0.0), compVec(N, 0.0), markovVec(N, 0.0), rejectVec(N, 0.0);

    probDensity(fVec, N, 1.0);
    // composite(compVec);
    // saveToFile(compVec, "composite.txt");
    // saveToFile(fVec, "fX.txt");
    markovChain(markovVec, N, 0.05);
    saveToFile(markovVec, "markov.txt");
    // rejection(rejectVec);
    // saveToFile(rejectVec, "reject.txt");

    printf("OK\n");
    return 0;
}