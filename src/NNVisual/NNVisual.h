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
        int layer;
        bool active=false;
    };
}


template <class T>
class NodeVisual : public Window_Subscriber {
private:
    sf::Clock clock;
    int layers;
    //each index contains a vector of Nodes 
    std::vector<T> NodeList;
    
public:
    NodeVisual(int l);
    ~NodeVisual(){}

    void setNodeList(std::vector<T> l) {NodeList = l; layers = NodeList.size();}
    void onNotify(sf::RenderWindow& window, int event) override;
    void draw(sf::RenderWindow& window);
    bool end();

    double get_node_x(double dx, double i) {
        return (dx * i) + (dx * (i + 1));
    }

    double get_node_y(double dy, double j) {
        return (dy * j) + (dy * (j + 1));
    }

    void guide_lines_vertical(sf::RenderWindow& window);
    void guide_lines_horizontal(sf::RenderWindow& window);

    void active(int layer, int node) {
        NodeList[layer][node].active = true;
    }

    void deactive(int layer, int node) {
        NodeList[layer][node].active = false;
    }

    void update(sf::Clock);
    double largest_layer();

};

template <class T>
NodeVisual<T>::NodeVisual(int l) {
    layers = l;
}
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

    for (int i=0; i<NodeList.size(); i++) {
        double ratio = 0.5;
        //should be the greatest amount of partitions
        double size = (SCREEN_HEIGHT / largest_layer()) * ratio * 0.5;
        int N = NodeList[i].size();//number of partitions
        double Dx = SCREEN_WIDTH / (layers * 2);
        double Mid_x = get_node_x(Dx, i);
        sf::Color c = sf::Color::Blue;
        for (int j=0; j<N; j++) {
            double Dy = SCREEN_HEIGHT / (N * 2);
            double Mid_y = get_node_y(Dy, j);
            for (int k=0; k<NodeList[i][j].Links.size(); k++) {
                int link = NodeList[i][j].Links[k];
                double Link_Dy = SCREEN_HEIGHT / (NodeList[i+1].size() * 2);
                double Link_y = get_node_y(Link_Dy, link);
                double Link_x = get_node_x(Dx, i+1);
                sf::Color co = sf::Color::Red;
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(Mid_x, Mid_y), co),
                    sf::Vertex(sf::Vector2f(Link_x, Link_y), co)
                };
                window.draw(line, 2, sf::Lines);
            }
            sf::CircleShape node;
            node.setFillColor(c);
            sf::Color o;
            if (NodeList[i][j].active) {
                o = sf::Color::Green;
            } else{
                o = sf::Color::White;
            }
            node.setOutlineColor(o);
            node.setPosition(sf::Vector2f(Mid_x, Mid_y));
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
        double x = (SCREEN_WIDTH/3)*i;
        sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(x, 0), c),
        sf::Vertex(sf::Vector2f(x, SCREEN_HEIGHT), c)
        };
        window.draw(line, 2, sf::Lines);
    }
}

template <class T>
void NodeVisual<T>::guide_lines_horizontal(sf::RenderWindow& window) {
    //draw each layer partitions
    for (int i=0; i<NodeList.size(); i++) {
        int N = NodeList[i].size();//number of partitions
        double Dx = SCREEN_WIDTH/3;
        double Startx = Dx * i;
        double Endx = Dx * (i+1);
        sf::Color c = sf::Color::Green;
        for (int j=0; j<N; j++) {
            double y = (SCREEN_HEIGHT/N)*j;
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
    if (static_cast<int>(clock.getElapsedTime().asSeconds()) % 5 == 0) {
        active(0,0);
        active(1,0);
        active(1,1);
        active(2,0);
        active(2,1);
        active(2,2);
    } else {
        deactive(0,0);
        deactive(1,0);
        deactive(1,1);
        deactive(2,0);
        deactive(2,1);
        deactive(2,2);
    }

    if (static_cast<int>(clock.getElapsedTime().asSeconds()) % 3 == 0) {
        active(0,2);
        active(1,0);
        active(2,0);
        active(2,1);
    } else {
        deactive(0,2);
        deactive(1,0);
        deactive(2,0);
        deactive(2,1);
    }

    if (static_cast<int>(clock.getElapsedTime().asSeconds()) % 2 == 0) {
        active(0,3);
        active(1,1);
        active(2,0);
        active(2,2);
    } else {
        deactive(0,0);
        deactive(1,1);
        deactive(2,0);
        deactive(2,2);
    }

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