#pragma once

#include <vector>
#include <string>

namespace Utils{
    double get_uniform_number();
    std::pair<double, double> normal_dist();
}


class XY_Open{
public:
    XY_Open();
    XY_Open(const int n);
    XY_Open(const int n, const double x, const double y);
    double get_dx(const double D, const double dt) const;
    double get_dy(const double D, const double dt) const;
    void next_time_step(const double D, const double dt);
    std::vector<double> get_x_vector() const;
    std::vector<double> get_y_vector() const;
    std::pair<double, double> get_xy_pair(const int i) const;
    void fill_vector(const std::vector<double>& x, const std::vector<double>& y);
    void fill_xy_pair(const double x, const double y, const int i);
    double get_x_mean() const;
    double get_y_mean() const;
    double get_xy_mean() const;
    double get_xx_mean() const;
    double get_yy_mean() const;
    void save_xy_vector(const std::string path);

private:
    std::pair<std::vector<double>, std::vector<double>> xy;
    int n;
};