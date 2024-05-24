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
    bool same_position(Position p) {return pos == p;}

    void set_pos(int, int);
    void set_dir(int, int);
    void set_speed(double);

    //get position of cell as a vector2f class 
    sf::Vector2f get_vector2f();
    //get position of cell as Position class 
    Position get_position(){return pos;}

    void die() {alive = false;}
    void live() {alive = true;}
    bool is_alive() {return alive==true;}

    //controls where cells will go on next tick 
    virtual void move();
    //draws cell representation to window 
    virtual void draw(sf::RenderWindow& window){}
    //ensures cell position is within screen
    void validate(int k=0);
    

protected:
    Position pos;
    Position dir;
    double speed;
    bool alive;
    Position slow_down;
};

