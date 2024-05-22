#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../constants.h"
#include "../color_constants.h"
#include "window_observer.h"

using namespace std;

class Window: public Window_Publisher {
    public: 
    
    Window();
    void run();
    void draw();
    void render();
    void update();
    void process_events();

    private: 
    sf::RenderWindow window;
}; 
