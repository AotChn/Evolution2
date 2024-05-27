#include "cell.h"

class Plant : public Cell {

public:
    Plant() {
        set_pos(0,0);
        set_dir(0,0);
        set_speed(0);
        alive = true;
        slow_down.set_pos(0,0);
    }

    ~Plant(){}

    virtual void draw(sf::RenderWindow& window) override {
        sf::CircleShape cell(1);
        cell.setFillColor(sf::Color::Green);
        if (alive) {
            cell.setPosition(get_vector2f());
            window.draw(cell);
        }
    }
};

