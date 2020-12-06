#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#ifndef INCLUDE_DRAWER_HPP_

#define INCLUDE_DRAWER_HPP_

class drawer {
	unsigned int x_size = 800;
	unsigned int y_size = 600;
    unsigned int marker_size = 3;

    unsigned int new_center_x = x_size / 2;
    unsigned int new_center_y = y_size / 2;

    double limit_x0;
    double limit_x1;
    double limit_y0;
    double limit_y1;

	double step_x;
	double step_y;
    double count_marker_y = 20;
    double count_marker_x = 20;

    double scaling_factor_x;
    double scaling_factor_y;

    std::vector<double> x_vec;
    std::vector<double> y_vec;
    std::vector<std::pair<double, double>> coordinates;
public:
    void cicle(const std::vector<double>& x_vec_, const std::vector<double>& y_vec_);
    void set_limits();
    void draw_plate(sf::RenderWindow& window); 
    void draw_curve(sf::RenderWindow& window);
    void calculate_scaling();
    void set_step();
};

#endif // INCLUDE_DRAWER_HPP_