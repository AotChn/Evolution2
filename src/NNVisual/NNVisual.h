#pragma once

#include "../graphics/window/window_observer.h"
#include "../graphics/constants.h"
#include "../graphics/color_constants.h"
#include "../cell/cell.h"

#include <vector>

namespace tempNode {
    struct Node {
        char c;
        int id; 
        std::vector<int> Links;
        bool active=false;
    };
}

template <class T>
class NodeVisual : public Window_Subscriber {
private:
    sf::Clock clock;
    //each index contains a layer with contains a vector of nodes
    std::vector<T> NodeList;
    double _height;
    double _width;
    double _offset_x;
    double _offset_y;
    
public:
    ~NodeVisual(){}

//===========================================
//	WINDOW INTERACTION
//===========================================
    void onNotify(sf::RenderWindow& window, int event) override;
    void update(sf::Clock);
    void draw(sf::RenderWindow& window);
    bool end();

//===========================================
//	MUTATORS
//===========================================

    void setNodeList(std::vector<T> l) {NodeList = l;}
    void set_parameters(double w, double h, double Offx, double Offy);
    void set_screen_size(double w, double h);
    void set_offset(double Offx, double Offy);

//===========================================
//	UTILITY
//===========================================

    //gets the x position of a node based on # of layers and node's layer
    double get_node_x(double dx, double i);
    //gets the y position of a node based on # of layers and node's layer
    double get_node_y(double dy, double j);
    //draws vertical guide lines 
    void guide_lines_vertical(sf::RenderWindow& window);
    //draws horizontal guide lines
    void guide_lines_horizontal(sf::RenderWindow& window);
    //sets node to active state
    void active(int layer, int node);
    //sets node to inactive state 
    void deactive(int layer, int node);
    //finds the layer with the greatest amount of nodes 
    double largest_layer();

};



#include "NNVisual.cpp"