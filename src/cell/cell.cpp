#include "cell.h"

void Cell::set_pos(int X, int Y) {
    pos.set_pos(X, Y);
    validate();
}

void Cell::set_dir(int X, int Y) {
    dir.set_pos(X, Y);
}

void Cell::set_speed(int s) {
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

void Cell::validate(int k) { //keep cells on the board
    if (pos.x > SCREEN_WIDTH) {
        pos.x = SCREEN_WIDTH-k;
        dir.x *= -1;
    }
    if (pos.y > SCREEN_HEIGHT) {
        pos.y = SCREEN_HEIGHT-k;
        dir.y *= -1;
    }
    if (pos.x + (speed * dir.x) <= 0) {
        pos.x = 0+k;
        dir.x *= -1;
    }
    if (pos.y + (speed * dir.y) <= 0) {
        pos.y = 0+k;
        dir.y *= -1;
    }
}