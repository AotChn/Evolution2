#ifndef G_CONSTANTS_H
#define G_CONSTANTS_H

#include <SFML/Graphics.hpp>
//#include "color_constants.h"

const unsigned int SCREEN_WIDTH = 1200;
const unsigned int SCREEN_HEIGHT = 1000;

const unsigned int NUM_CELLS = 30;
const unsigned int FOOD_AMT = 10000;

enum CUSTOM_SFEV{
    Idle = -1,
    Draw = sf::Event::EventType::Count,
    
};
#endif