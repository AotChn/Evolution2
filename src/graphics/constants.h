#ifndef G_CONSTANTS_H
#define G_CONSTANTS_H

#include <SFML/Graphics.hpp>
//#include "color_constants.h"

const double height_width_ratio = 0.675;
const unsigned int SCREEN_WIDTH = 2000;
const unsigned int SCREEN_HEIGHT = SCREEN_WIDTH * height_width_ratio;

namespace board_params {
    const int off_x = int(SCREEN_HEIGHT / (32));
    const double off_y = off_x;
    //screen width * ratio * offset border 
    const double width = (SCREEN_WIDTH * 0.5) - (off_x * 2);
    //screen height * ratio * offset border 
    const double height = (SCREEN_HEIGHT * 1) - (off_y * 2);
    const unsigned int CELLS_AMT = 50;
    const unsigned int FOOD_AMT = 1000;
}

namespace NNVisualTest{
    const double off_x = (SCREEN_WIDTH * 0.5);
    const double off_y = 0;
    const double width = (SCREEN_WIDTH * 0.5);
    const double height = (SCREEN_HEIGHT * 0.5);
}

namespace LINE_GRAPH{
    const double off_x= (SCREEN_WIDTH * 0.5);
    const double off_y= 0;
    const double width= (SCREEN_WIDTH * 0.5);
    const double height= (SCREEN_WIDTH * 0.5);
    const double Mx = (width / 6);
    const double My = Mx;
}

enum CUSTOM_SFEV{
    Idle = -1,
    Draw = sf::Event::EventType::Count,
    
};
#endif