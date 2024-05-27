#ifndef PLOT_CPP
#define PLOT_CPP

#include "plot.h"

using namespace Visual;


template <class T>
void Plot<T>::set_parameters(double width, double height, double offx, double offy) {
    set_screen_size(width, height);

    set_offset(offx, offy);

}

template <class T>
void Plot<T>::set_offset(double Offx, double Offy) {
    _offset_x = Offx;
    _offset_y = Offy;

}

template <class T>
void Plot<T>::set_screen_size(double width, double height) {
    _width = width;

    _height = height;

}

template <class T>
void Plot<T>::set_type(int t) {
    _type = t;

}

template <class T>
void Plot<T>::set_default_color() {
    colors[defaults::BACK] = LINE_GRAPH::BACKGROUND;

    colors[defaults::SECONDARY] = LINE_GRAPH::SECONDARY;

    colors[defaults::X_LABEL] = LINE_GRAPH::X_LABEL;

    colors[defaults::Y_LABEL] = LINE_GRAPH::Y_LABEL;

    colors[defaults::NUMBERS] = LINE_GRAPH::NUMBERS;

    colors[defaults::AXIS_LINE] = LINE_GRAPH::AXIS_LINE;

}


template <class T>
void Plot<T>::set_x_range(double min, double max){
    x_range.first = min;
    x_range.second = max;
}

template <class T>
void Plot<T>::set_y_range(double min, double max){
    y_range.first = min;
    y_range.second = max;
}

template <class T>
void Plot<T>::set_x_axis_label(std::string s){

}

template <class T>
void Plot<T>::set_y_axis_label(std::string s){

}

template <class T>
void Plot<T>::set_increment(double x, double y){
    _incr.first = x;
    _incr.second = y;
}

template <class T>
void Plot<T>::set_x_increment(double inc){
    _incr.first = inc;
}

template <class T>
void Plot<T>::set_y_increment(double inc){
    _incr.second = inc;
}


template <class T>
void Plot<T>::set_background_on(bool t){
    _background = t;
}

template <class T>
void Plot<T>::set_background_color(sf::Color){

}

template <class T>
void Plot<T>::set_background_color(int x, int y, int z){

}

template <class T>
void Plot<T>::set_secondary_color(sf::Color){

}

template <class T>
void Plot<T>::set_secondary_color(int x, int y, int z){

}

template <class T>
void Plot<T>::set_margin(double Mx, double My) {
    _margin_x = Mx;
    _margin_y = My;
}

template <class T>
void Plot<T>::set_default_line() {
    _offset_x = LINE_GRAPH::off_x;
    _offset_y = LINE_GRAPH::off_y;
    _width = LINE_GRAPH::width;
    _height = LINE_GRAPH::height;
    _margin_x = LINE_GRAPH::Mx;
    _margin_y = LINE_GRAPH::My;
}

template <class T>
void Plot<T>::set_precision(int p){
    _precision = p;
}

template <class T> //test this
void Plot<T>::add_data(T d) {
    if (d.get_max_x() > x_range.second) {
        x_range.second = d.get_max_x();
    }
    if (d.get_min_x() < x_range.first) {
        x_range.first = d.get_min_x();
    }
    if (d.get_max_y() > y_range.second) {
        y_range.second = d.get_max_y();
    }
    if (d.get_min_y() < y_range.first) {
        y_range.first = d.get_max_y();
    }
    data.push_back(d);
    //std::cout<<"dataframes :" << data.size() << '\n';
}

template <class T> //test this
void Plot<T>::remove_data() {
    data.pop_back();
}

template <class T>
void Plot<T>::draw_background(sf::RenderWindow& window){
    sf::RectangleShape rec;
    rec.setFillColor(colors[BACK]);
    rec.setPosition(sf::Vector2f(_offset_x, _offset_y));
    rec.setSize(sf::Vector2f(_width, _height));
    window.draw(rec);

}

template <class T>
void Plot<T>::draw_secondary(sf::RenderWindow& window){
    sf::RectangleShape rec;
    //M is the margin size between background and secondary 
    rec.setFillColor(colors[SECONDARY]);
    rec.setPosition(sf::Vector2f(_offset_x + _margin_x, _offset_y));
    rec.setSize(sf::Vector2f(_width - _margin_x, _height - _margin_y));
    window.draw(rec);
}

template <class T>
void Plot<T>:: draw_y_axis_line(sf::RenderWindow& window){
    int stroke = 3;
    for (int i=0; i<stroke; i++) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(_offset_x + _margin_x + i, _offset_y), colors[AXIS_LINE]),
            sf::Vertex(sf::Vector2f(_offset_x + _margin_x + i, _offset_y + _height - _margin_y), colors[AXIS_LINE])
        };
        window.draw(line, 2, sf::Lines);
    }

}

template <class T>
void Plot<T>::draw_x_axis_line(sf::RenderWindow& window){
    int stroke = 3;
    for (int i=0; i<stroke; i++) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(_offset_x + _margin_x, _offset_y + _height - _margin_y - i), colors[AXIS_LINE]),
            sf::Vertex(sf::Vector2f(_offset_x + _width, _offset_y + _height - _margin_y - i), colors[AXIS_LINE])
        };
        window.draw(line, 2, sf::Lines);
    }
}

template <class T>
void Plot<T>::draw_ticks(sf::RenderWindow& window){

}

int power_of_10(double n) {
    int power = 0;
    while ((int)n > 0) {
        power++;
        n = n/10;
    }
    return power;
}

template <class T>
void Plot<T>::draw_x_axis_numbers(sf::RenderWindow& window){
    sf::Text text;
    std::string out;
    double end = _width - _margin_x - 50;
    double increments = x_range.second/_incr.first;
    double dx = end/(increments);
    double size = (end * double(double(24) / double(750))) * double(10/increments);
    sf::Vector2f start(_offset_x + _margin_x, _offset_y + _height - _margin_y);
    text.setFont(font);
    text.setFillColor(colors[NUMBERS]);
    text.setCharacterSize(size);

    sf::CircleShape point;
    point.setRadius(1);
    point.setOutlineThickness(5);
    point.setOutlineColor(sf::Color::Blue);

    for (double i=x_range.first; i<=x_range.second; i=i+_incr.first) {
        int p = power_of_10(i);
        out = std::to_string(i);
        double pos_x = start.x + ((i / _incr.first) * dx);
        double pos_y = start.y;
        text.setPosition(pos_x - (((size/3) * (_precision + 1))), pos_y);
        point.setPosition(pos_x, start.y);
        if (i == 0) {
            text.setString("");
        } else {
            text.setString(out.substr(0, p + 1 + _precision));
        }
        window.draw(text);
        window.draw(point);
    }
}

template <class T>
void Plot<T>::draw_y_axis_numbers(sf::RenderWindow& window){
    sf::Text text;
    std::string out;
    double end = _height - _margin_y - 50;
    double increments = y_range.second/_incr.second;
    double dy = end/(increments);
    double size = (end * double(double(24) / double(750))) * double(10/increments);
    sf::Vector2f start(_offset_x + _margin_x, _offset_y + _height - _margin_y);
    text.setFont(font);
    text.setFillColor(colors[NUMBERS]);
    text.setCharacterSize(size);

    sf::CircleShape point;
    point.setRadius(1);
    point.setOutlineThickness(5);
    point.setOutlineColor(sf::Color::Blue);

    for (double i=y_range.first; i<=y_range.second; i=i+_incr.second) {
        int p = power_of_10(i);
        out = std::to_string(i);
        double pos_x = start.x - (size * (_precision + 1));
        double pos_y = start.y - ((i / _incr.second) * dy);
        text.setPosition(pos_x - 10, pos_y - ((size/3) * (_precision + 1)));
        point.setPosition(start.x, pos_y);
        if (i == 0) {
            text.setString("");
        } else {
            text.setString(out.substr(0, p + 1 + _precision));
        }
        window.draw(text);
        window.draw(point);
    }
}

template <class T>
void Plot<T>::draw_plot(sf::RenderWindow& window){
//find x point on plot
//find y point on plot 
    sf::CircleShape point;
    point.setRadius(1);
    point.setOutlineThickness(2);
    point.setFillColor(LINE_GRAPH::POINT);
    point.setOutlineColor(LINE_GRAPH::POINT);

    sf::Vector2f start(_offset_x + _margin_x, _offset_y + _height - _margin_y);
    double max_screen_x = _width - _margin_x - 50;
    double max_screen_y = _height - _margin_y - 50;

    double pos_x;
    double pos_y;;

    int x;
    int y;

    //std::cout<< data[0].size();
    sf::VertexArray lines(sf::LinesStrip, data[0].size());
    for (int i=0; i<=data[0].size()-1; i++) {
        x = data[0].get_x(i);
        y = data[0].get_y(i);
        double ratio_x = double(x) / (x_range.first + x_range.second);
        double ratio_y = double(y) / (y_range.first + y_range.second);
        pos_x = start.x + (ratio_x * max_screen_x);
        pos_y = start.y - (ratio_y * max_screen_y);
        point.setPosition(sf::Vector2f(pos_x, pos_y));
        lines[i].position = sf::Vector2f(pos_x, pos_y);
        lines[i].color = sf::Color::Blue;
        window.draw(point);
    }


 window.draw(lines);

}





#endif