#ifndef NNVISUAL_CPP
#define NNVISUAL_CPP

#include "NNVisual.h"

template <class T>
void NodeVisual<T>::onNotify(sf::RenderWindow& window, int event){
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
void NodeVisual<T>::draw(sf::RenderWindow& window) {
    update(clock);
    double ratio = 0.5;
    double size = (_height / largest_layer()) * ratio * 0.5;
    for (int i=0; i<NodeList.size(); i++) {
        int N = NodeList[i].size();//number of partitions
        double Dx = _width / (NodeList.size() * 2);
        double Node_x = get_node_x(Dx, i);
        for (int j=0; j<N; j++) {
            double Dy = _height / (N * 2);
            double Node_y = get_node_y(Dy, j);
            for (int k=0; k<NodeList[i][j].Links.size(); k++) {
                int link = NodeList[i][j].Links[k];
                double Link_Dy = _height / (NodeList[i+1].size() * 2);
                double Link_y = get_node_y(Link_Dy, link);
                double Link_x = get_node_x(Dx, i+1);
                sf::Color co = sf::Color::Red;
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(Node_x + _offset_x, Node_y + _offset_y), co),
                    sf::Vertex(sf::Vector2f(Link_x + _offset_x, Link_y + _offset_y), co)
                };
                window.draw(line, 2, sf::Lines);
            }
            sf::CircleShape node;
            sf::Color o;
            if (NodeList[i][j].active) {
                o = sf::Color::Green;
            } else{
                o = sf::Color::White;
            }
            node.setOutlineColor(o);
            node.setPosition(sf::Vector2f(Node_x + _offset_x, Node_y + _offset_y));
            node.setRadius(1);
            node.setOutlineThickness(size);
            window.draw(node);
        }
    }
}

template <class T>
bool NodeVisual<T>::end() {
    return false;
}

template <class T>
void NodeVisual<T>::guide_lines_vertical(sf::RenderWindow& window) {
     //draw layer lines
    for (int i=1; i<NodeList.size(); i++) {
        sf::Color c = sf::Color::Red;
        double x = (_width/3)*i;
        sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(x, 0), c),
        sf::Vertex(sf::Vector2f(x, _height), c)
        };
        window.draw(line, 2, sf::Lines);
    }
}

template <class T>
void NodeVisual<T>::guide_lines_horizontal(sf::RenderWindow& window) {
    //draw each layer partitions
    for (int i=0; i<NodeList.size(); i++) {
        int N = NodeList[i].size();//number of partitions
        double Dx = _width/3;
        double Startx = Dx * i;
        double Endx = Dx * (i+1);
        sf::Color c = sf::Color::Green;
        for (int j=0; j<N; j++) {
            double y = (_height/N)*j;
            sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(Startx, y), c),
            sf::Vertex(sf::Vector2f(Endx, y), c)
            };
            window.draw(line, 2, sf::Lines);
        }
    }
}

template <class T>
void NodeVisual<T>::update(sf::Clock) {

}

template <class T>
double NodeVisual<T>::largest_layer() {
    double max = -1;
    for (int i=0; i<NodeList.size(); i++) {
        if (NodeList[i].size() > max) {
            max = NodeList[i].size();
        }
    }
    return max;
}

template <class T>
double NodeVisual<T>::get_node_x(double dx, double i) {
    return (dx * i) + (dx * (i + 1));
}

template <class T>
double NodeVisual<T>::get_node_y(double dy, double j) {
    return (dy * j) + (dy * (j + 1));
}

template <class T>
void NodeVisual<T>::active(int layer, int node) {
    NodeList[layer][node].active = true;
}

template <class T>
void NodeVisual<T>::deactive(int layer, int node) {
    NodeList[layer][node].active = false;
}

template <class T>
void NodeVisual<T>::set_parameters(double width, double height, double offx, double offy) {
    set_screen_size(width, height);
    set_offset(offx, offy);
}

template <class T>
void NodeVisual<T>::set_offset(double Offx, double Offy) {
    _offset_x = Offx;
    _offset_y = Offy;
}

template <class T>
void NodeVisual<T>::set_screen_size(double width, double height) {
    _width = width;
    _height = height;
}


#endif