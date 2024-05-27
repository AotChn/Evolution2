#pragma once 

#pragma once

#include "../graphics/window/window_observer.h"
#include "../graphics/constants.h"
#include "../graphics/color_constants.h"
#include "../cell/cell.h"

#include <vector>

template <class T>
struct dataframe {
    int id;
    std::vector<T> x;
    std::vector<T> y;

    dataframe(){}
    
    void add(T X, T Y) {
        x.push_back(X);
        y.push_back(Y);
    }

    T get_x(int idx) {
        return x[idx];
    }
    T get_y(int idx) {
        return y[idx];
    }

    int size() {
        return y.size();
    }

    T get_max_x() {
        return *std::max_element(x.begin(), x.end());
    }

    T get_max_y() {
        return *std::max_element(y.begin(), y.end());
    }

    T get_min_x() {
        return *std::min_element(x.begin(), x.end());
    }

    T get_min_y() {
        return *std::min_element(y.begin(), y.end());
    }

    void print() {
        for (int i=0; i<size(); i++) {
            std::cout << x[i] << ' ';
        }
         std::cout <<'\n';
        for (int i=0; i<size(); i++) {
            std::cout << y[i] << ' ';
        }
    }
};


namespace Visual {
enum defaults {BACK, SECONDARY, X_LABEL, Y_LABEL, NUMBERS, AXIS_LINE};
enum plots {LINE, BAR, VIOLIN};

template <class T>
class Plot : public Window_Subscriber {
private:
    sf::Clock clock;
    //screen data 
    double _height;
    double _width;
    double _offset_x;
    double _offset_y;
    double _margin_x;
    double _margin_y;
    //type of graph
    int _type;
    //vector of dataframes 
    std::vector<T> data;
    //min and max range of x axis
    std::pair<double, double> x_range;
    //min and max range of y axis
    std::pair<double, double> y_range;
    //how the graph increments the x and y axis
    std::pair<double, double> _incr;
    //decimal points
    int _precision;
    //aes 
    sf::Color colors[6];
    bool _background;
    sf::Font font;
    
public:
    Plot(int t);
    ~Plot(){}

//===========================================
//	WINDOW INTERACTION
//===========================================
    void onNotify(sf::RenderWindow& window, int event) override;
    void update(sf::Clock);
    void draw(sf::RenderWindow& window);
    bool end();
    void load_font(std::string file = "fonts/arial.ttf");
//===========================================
//	MUTATORS
//===========================================

    void set_parameters(double w, double h, double Offx, double Offy);
    void set_screen_size(double w, double h);
    void set_offset(double Offx, double Offy);
    void set_x_range(double min, double max);
    void set_y_range(double min, double max);
    void set_x_axis_label(std::string s);
    void set_y_axis_label(std::string s);
    void set_increment(double x, double y);
    void set_x_increment(double inc);
    void set_y_increment(double inc);
    void set_type(int t);
    void set_background_on(bool t);
    void set_background_color(sf::Color);
    void set_background_color(int, int, int);
    void set_secondary_color(sf::Color);
    void set_secondary_color(int, int, int);
    void set_default_color();
    void set_default_line();
    void set_margin(double Mx, double My);
    void set_precision(int p=1);
    void add_data(T d);
    void remove_data();
    

//===========================================
//	DRAW
//===========================================

    void draw_background(sf::RenderWindow& window);
    void draw_secondary(sf::RenderWindow& window);
    void draw_x_axis_line(sf::RenderWindow& window);
    void draw_y_axis_line(sf::RenderWindow& window);
    void draw_ticks(sf::RenderWindow& window);
    void draw_x_axis_numbers(sf::RenderWindow& window);
    void draw_y_axis_numbers(sf::RenderWindow& window);
    void draw_plot(sf::RenderWindow& window);
    

};

template <class T>
Plot<T>::Plot(int t) {
    set_type(t);
    set_x_range(0, 0);
    set_y_range(0, 0);
    set_increment(1, 1);
    set_default_color();
    set_default_line();
    set_precision();
    load_font();
}


template <class T>
void Plot<T>::onNotify(sf::RenderWindow& window, int event){
	switch (event)
    {
		case CUSTOM_SFEV::Draw:{
			draw(window);
			return;
		    break;
        }
        case sf::Event::MouseButtonPressed:{

            break;
        }
        case sf::Event::MouseButtonReleased:{
            break;
        }   
        case sf::Event::MouseMoved:{
            break;
        }
        case CUSTOM_SFEV::Idle:{
            if (end()) {
                window.close();
            }
        }
    
    default:
        break;
    }
}

template <class T>
void Plot<T>::load_font(std::string file) {
    if(!font.loadFromFile(file)){
            cout<<"animate font CTOR: Font failed to load"<<endl;
            exit(-1);
        }
}

template <class T>
void Plot<T>::draw(sf::RenderWindow& window) {
    update(clock);
    
    draw_background(window);
    draw_secondary(window);
    draw_x_axis_line(window);
    draw_y_axis_line(window);
    draw_x_axis_numbers(window);
    //std::cout<< "out\n";
    //std::cout<< "size: " << data.size();
    if (data.size() >= 1) {
    //    std::cout<< "in\n";
        draw_ticks(window);
        draw_x_axis_numbers(window);
        draw_y_axis_numbers(window);
        draw_plot(window);
    }
}

template <class T>
void Plot<T>::update(sf::Clock) {

}

template <class T>
bool Plot<T>::end() {
    return false;
}



}

#include "plot.cpp"