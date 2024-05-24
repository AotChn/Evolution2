#pragma once

#include "../graphics/window/window_observer.h"
#include "../board/board.h"
#include "../graphics/constants.h"

class simulation : public Window_Subscriber {
private:
    Board env;
    Board *b_ptr;
    sf::Clock clock;

public:
    simulation();
    ~simulation(){}

    void onNotify(sf::RenderWindow& window, int event) override;
    void draw(sf::RenderWindow& window);
    bool end();
};

simulation::simulation() {
    env.init_board();
}

void simulation::onNotify(sf::RenderWindow& window, int event){
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


void simulation::draw(sf::RenderWindow& window) {
    env.update(clock);

    for (int i=0; i<env.get_food()->size(); i++) {
       env.get_food()->at(i).draw(window);
    }

    for (int i=0; i<env.get_cells()->size(); i++) {
        env.get_cells()->at(i).draw(window);
    }

}

bool simulation::end() {
    if (env.get_cells()->empty()) {
        return true;
    }
    return false;
}