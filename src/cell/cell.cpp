#include "cell.h"

void Cell::set_pos(int X, int Y) {
    pos.set_pos(X, Y);
    validate();
}

void Cell::set_dir(int X, int Y) {
    dir.set_pos(X, Y);
}

void Cell::set_speed(double s) {
    if (s <= 0) {
        s = 1;
    }
    speed = s;
}

sf::Vector2f Cell::get_vector2f() {
    return sf::Vector2f(pos.x, pos.y);
}

void Cell::move() {
    if (slow_down.x != 0 or slow_down.y != 0) {
        pos.x = pos.x + (slow_down.x * dir.x);
        pos.y = pos.y + (slow_down.y * dir.y);
    } else {
        pos.x = pos.x + (speed * dir.x);
        pos.y = pos.y + (speed * dir.y);
    }

    slow_down.set_pos(0,0);
    validate();
}

void Cell::validate(double width, double height, double offset_x, double offset_y, int k) { //keep cells on the board
    if (pos.x > width + offset_x) {
        pos.x = width + offset_x -k;
        dir.x *= -1;
    }
    if (pos.y > height + offset_y) {
        pos.y = height + offset_y - k;
        dir.y *= -1;
    }
    if (pos.x + (speed * dir.x) <= 0 + offset_x) {
        pos.x = 0 + offset_x + k;
        dir.x *= -1;
    }
    if (pos.y + (speed * dir.y) <= 0 + offset_y) {
        pos.y = 0 + offset_y + k;
        dir.y *= -1;
    }
}