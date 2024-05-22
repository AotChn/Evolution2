#pragma once 

#include "../graphics/constants.h"

#include <cmath>
#include <iostream>

struct Position {
    int x;
    int y;

    void set_pos(int X, int Y) {
        x = X;
        y = Y;
    }

    Position& operator=(const Position& RHS){
        x = RHS.x;
        y = RHS.y;
    return *this; 
}

    bool operator==(const Position& other) {
        if (other.x == x) {
            if (other.y == y) {
                return true;
            }
        }
        return false;
    }

    bool operator!=(const Position& other) {
            if (other.x == x) {
                if (other.y == y) {
                return false;
            }
        }
        return true;
    }

    bool operator<(const Position& other) const{
        return x + y < other.x + other.y;
    }

    bool operator>(const Position& other) const{
        return x + y > other.x + other.y;
    }

}; 

class Cell {

public: 
    Cell() {
        set_pos(0,0);
        set_dir(0,1);
        set_speed(0);
        alive = true;
    }

    Cell(int X, int Y) {
        set_pos(X, Y);
    }

    ~Cell(){}

    bool same_position(const Cell& other) {return pos == other.pos;}

    void set_pos(int, int);
    void set_dir(int, int);
    void set_speed(int);
    sf::Vector2f get_vector2f();
    Position get_position(){return pos;}

    void die() {alive = false;}
    void live() {alive = true;}
    bool is_alive() {return alive==true;}
    void validate(int k=0);

    virtual void move();
    virtual void draw(sf::RenderWindow& window){}
    

protected:
    Position pos;
    Position dir;
    int speed;
    bool alive;
    Position slow_down;
};

//*******************************************
//	CHILD CLASSES
//-------------------------------------------

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
        sf::CircleShape cell(2);
        cell.setFillColor(sf::Color::Green);
        if (alive) {
            cell.setPosition(get_vector2f());
            window.draw(cell);
        }
    }
};

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

    void eat(int k) {
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

