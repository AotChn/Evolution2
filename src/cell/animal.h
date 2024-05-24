#include "cell.h"

class Animal : public Cell {

public:
    Animal() {
        set_pos(0,0);
        set_dir(0,1);
        set_speed(1);
        set_energy(60*10,60*10);
        alive = true;
        slow_down.set_pos(0,0);
    }

    virtual void draw(sf::RenderWindow& window) override {
        sf::CircleShape cell(2);
        cell.setFillColor(sf::Color::Red);
        if (alive) {
            cell.setPosition(get_vector2f());
            window.draw(cell);
        }
    }

    void set_energy(int e, int E) {
        energy = e;
        MAX_energy = E;
    }

    void eat(double k) {
        energy += k;
    }

    void seek_food(Position p) {

        if (pos.x > p.x) {
            dir.x = -1;
        } else if (pos.x < p.x) {
            dir.x = 1;
        } else {
            dir.x = 0;
        }

        if ( pos.y > p.y) {
            dir.y = -1;
        } else if (pos.y < p.y){
            dir.y = 1;
        } else {
            dir.y = 0;
        }

        if (speed > 1) {
            if (std::abs(speed * dir.x) + std::abs(pos.x) > std::abs(p.x)) {
                slow_down.x = (p.x-pos.x)/dir.x;
            }
            if (std::abs(speed * dir.y) + std::abs(pos.y) > std::abs(p.y)) {
                slow_down.y = (p.y-pos.y)/dir.y;
            }
        }
        
    }

    virtual void move() override {

        if (energy >= MAX_energy) {
            energy = MAX_energy;
            refilling = false;
        }
        
        double m = double(energy)/double(MAX_energy);

        if (slow_down.x != 0 or slow_down.y != 0) {
            pos.x = pos.x + (slow_down.x * dir.x);
            pos.y = pos.y + (slow_down.y * dir.y);
        } else {
            pos.x = pos.x + int(speed * dir.x * m);
            pos.y = pos.y + int(speed * dir.y * m);
        }

        slow_down.set_pos(0,0);
        validate();

        if (energy <= MAX_energy*.10 or refilling) {
            refilling = true;
            energy++;
        } 
        if (energy <= 0) {
            die();
        }

        energy -= (speed * .7) + 1;
    }

    double get_energy() {return energy;}

private: 
    bool refilling;
    double energy;
    double MAX_energy;
};

