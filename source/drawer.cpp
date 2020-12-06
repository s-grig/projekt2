#include <drawer.hpp>

void drawer::cicle(const std::vector<double>& x_vec_, const std::vector<double>& y_vec_) {
    x_vec = x_vec_;
    y_vec = y_vec_;
    sf::RenderWindow window(sf::VideoMode(x_size, y_size), "Function plot");
    set_limits();
    set_step();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        draw_plate(window);
        draw_curve(window);
        window.display();
    }
}

void drawer::set_step() {
    step_x = (limit_x1 - limit_x0) / count_marker_x;
    step_y = (limit_y1 - limit_y0) / count_marker_y;
}

void drawer::set_limits() {
    for (int i = 0; i < x_vec.size(); i++) {
        coordinates.push_back(std::make_pair(x_vec[i], y_vec[i]));
    }

    auto temp = std::max_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
    double max_x = ceil((*temp).first * 1000) / 1000 ;
    max_x += 0.05 * max_x;

    temp = std::min_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
    double min_x = floor((*temp).first * 1000) / 1000;
    min_x += 0.05 * min_x;

    temp = std::max_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    double max_y = ceil((*temp).second * 1000) / 1000;
    max_y += 0.05 * max_y;

    temp = std::min_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    double min_y = floor((*temp).second * 1000) / 1000;
    min_y += 0.05 * min_y;

    if (abs(max_x) > abs(min_x)) {
        limit_x0 = -max_x;
        limit_x1 = max_x;
    }
    else {
        limit_x0 = min_x;
        limit_x1 = -min_x;
    }
    if (abs(max_y) > abs(min_y)) {
        limit_y0 = -max_y;
        limit_y1 = max_y;
    }
    else {
        limit_y0 = min_y;
        limit_y1 = -min_y;
    }
}

void drawer::draw_plate(sf::RenderWindow& window) {
    window.clear(sf::Color(255, 255, 255, 0));
    //Оси
    sf::RectangleShape line;
    line.setFillColor(sf::Color(0, 0, 0));
    //Вертикаль Y
    line.setPosition(0, new_center_y);
    line.setSize(sf::Vector2f(x_size, 4));
    window.draw(line);
    //Горизонталь X
    line.setPosition(new_center_x, 0);
    line.setSize(sf::Vector2f(4, y_size));
    window.draw(line);

    sf::Font font;
    if (!font.loadFromFile("..\\..\\..\\files\\font\\arial.ttf")) {
        std::cout << "Font reading error" << std::endl;
    }

    sf::Text text;
    text.setCharacterSize(10);
    text.setFillColor(sf::Color(0, 0, 0));
    text.setFont(font);

    double len_axis_y = y_size;
    for (double u = 0; u <= count_marker_y; u++) {
        //Текст
        text.setString(std::to_string(limit_y1 - u * step_y));
        text.setPosition(new_center_x + 15, len_axis_y / count_marker_y * u - 10);
        window.draw(text);

        line.setFillColor(sf::Color(0, 0, 0));
        //Горизонтальные
        line.setPosition(0, len_axis_y / count_marker_y * u);
        line.setSize(sf::Vector2f(x_size, 1));
        window.draw(line);
    }

    //Разметка горизонтальной оси
    double len_axis_x = x_size;
    for (double u = 0; u <= count_marker_x; u++) {
        //Текст
        text.setString(std::to_string(limit_x0 + u * step_x));
        text.setPosition(len_axis_x / count_marker_x * u, new_center_y + 15);
        window.draw(text);
        //Вспомогательные линии сетки
        //вертикальные
        line.setPosition(len_axis_x / count_marker_x * u, 0);
        line.setSize(sf::Vector2f(1, y_size));
        window.draw(line);
    }

    //X
    text.setCharacterSize(20);
    text.setString("X");
    text.setPosition(x_size - 15, new_center_y - 25);
    window.draw(text);
    //Y
    text.setString("Y");
    text.setPosition(new_center_x - 15, 0);
    window.draw(text);
}

void drawer::draw_curve(sf::RenderWindow& window) {
    calculate_scaling();
    sf::Color color_graph(255, 0, 0);
    for (int i = 0; i < coordinates.size(); i++) {
        double point_x = (coordinates[i].first - limit_x0) * scaling_factor_x;
        double point_y = y_size + (limit_y0 - coordinates[i].second) * scaling_factor_y;
        sf::CircleShape shape(marker_size);
        shape.setPosition(point_x - marker_size, point_y - marker_size);
        shape.setFillColor(color_graph);
        window.draw(shape);
        if (i > 0) {
            sf::VertexArray lines(sf::LinesStrip, 2);
            lines[0].position = sf::Vector2f(point_x, point_y);
            lines[0].color = sf::Color::Red;
            lines[1].position = sf::Vector2f((coordinates[i - 1].first - limit_x0) * scaling_factor_x,
                y_size + (limit_y0 - coordinates[i - 1].second) * scaling_factor_y);
            lines[1].color = sf::Color::Red;
            window.draw(lines);
        }
    }
}

void drawer::calculate_scaling() {
    scaling_factor_x = (x_size) / (limit_x1 - limit_x0);
    scaling_factor_y = (y_size) / (limit_y1 - limit_y0);
}
