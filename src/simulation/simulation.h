#pragma once

#include "../graphics/window/window_observer.h"
#include "../board/board.h"
#include "../graphics/constants.h"
#include "../plot/plot.h"

class simulation : public Window_Subscriber {
private:
    Board env;
    Board *b_ptr;
    sf::Clock clock;
    dataframe<int> df;
    Plot<dataframe<int>>* plot;

public:
    simulation();
    simulation(Plot<dataframe<int>>* p);
    ~simulation(){}

//===========================================
//	WINDOW INTERACTION
//===========================================
    void onNotify(sf::RenderWindow& window, int event) override;
    void draw_background(sf::RenderWindow& window);
    void draw_cells(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool end();
    void update();
    void set_plot(Plot<dataframe<int>>* p);
};

simulation::simulation() {
    env.init_board();
}

simulation::simulation(Plot<dataframe<int>>* p) {
    env.init_board();
    set_plot(p);
    // df.add(10,10);
    // df.add(2,5);
    // df.add(3,7);
    df.add(0, env.get_cells()->size());
    df.print();
    plot->add_data(df);
    plot->set_x_range(0, 10);
    plot->set_y_range(0,50);
    plot->set_x_increment(1);
    plot->set_y_increment(5);
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
    update();
    draw_background(window);
    draw_cells(window);

}

bool simulation::end() {
    if (env.get_cells()->empty()) {
        return true;
    }
    return false;
}

void simulation::draw_background(sf::RenderWindow& window) {
    sf::RectangleShape rec;
    
    //background
    rec.setFillColor(sf::Color(122, 120, 119));
    rec.setPosition(sf::Vector2f(0,0));
    rec.setSize(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT));
    window.draw(rec);

    //board 
    rec.setFillColor(sf::Color(51, 51, 50));
    rec.setPosition(sf::Vector2f(board_params::off_x, board_params::off_y));
    rec.setSize(sf::Vector2f(board_params::width, board_params::height));
    window.draw(rec);

}

void simulation::draw_cells(sf::RenderWindow& window) {
    for (int i=0; i<env.get_food()->size(); i++) {
       env.get_food()->at(i).draw(window);
    }

    for (int i=0; i<env.get_cells()->size(); i++) {
        env.get_cells()->at(i).draw(window);
    }
}

void simulation::update() {
    if (static_cast<int>(clock.getElapsedTime().asSeconds()) % 2 == 0) {
        //std::cout<< env.get_cells()->size() << "<- cells left\n";
        df.add(static_cast<int>(clock.getElapsedTime().asSeconds()), env.get_cells()->size());
        plot->remove_data();
        plot->add_data(df);
        //std::cout<< "updated sim\n";
        plot->set_x_range(0, static_cast<int>(clock.getElapsedTime().asSeconds()));
        //plot->set_y_increment(static_cast<int>(clock.getElapsedTime().asSeconds()/10));
    }
}

void simulation::set_plot(Plot<dataframe<int>>* p) {
    plot = p;
}