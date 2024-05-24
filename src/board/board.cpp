#include "board.h"

//===========================================
//	HELPER
//===========================================
namespace utils{

//removes item at index i from a vector 
template <class T>
void remove(std::vector<T>& v, int idx) {
    v.erase(v.begin() + idx);
    if (v.size() == 1) {
        v.pop_back();
    }
}

//generates a random number from min to max
int gen_num(int min, int max){
    if (min < 0) {
        max = max + -(min);
    }
    return rand() % max + min;
}

}

//===========================================
//	BOARD MANIPULATION
//===========================================

void Board::init_board(int f, int c) {
    fill_board(f, c);
}

void Board::add_cell(int x, int y, int s) {
    Animal a;
    a.set_pos(x, y);
    a.set_speed(s);
    cells.push_back(a);
}

void Board::add_cell(int speed_MIN, int speed_MAX) {
    int x = utils::gen_num(0, SCREEN_WIDTH);
    int y = utils::gen_num(0, SCREEN_HEIGHT);
    int s = utils::gen_num(speed_MIN, speed_MAX);
    add_cell(x, y, s);
}

void Board::add_food(int x, int y) {
    Plant p;
    p.set_pos(x, y);
    food.push_back(p);
}

void Board::add_food() {
    int x = utils::gen_num(0, SCREEN_WIDTH);
    int y = utils::gen_num(0, SCREEN_HEIGHT);
    add_food(x, y);
}

int Board::closest_cell(Position p) {
    int closest = INT_MAX;
    int best = 0;
    for (int i=0; i<food.size()-1; i++) {
        Position k = food[i].get_position();
        int p_score = (std::abs(p.x - k.x)) + (std::abs(p.y - k.y));
        if (p_score < closest) {
            closest = p_score;
            best = i;
        } 
    }

    return best;
}

void Board::fill_board(int f_amt, int c_amt) {
    fill_food(f_amt);
    fill_cells(c_amt);
}

void Board::fill_food(int amt) {
    for (int i=0; i<amt; i++) {
        add_food();
    }
}

void Board::fill_cells(int amt) {
    for (int i=0; i<amt; i++) {
        add_cell();
    }
}

//===========================================
//	UPDATE
//===========================================

void Board::update_cells() {
    for (int i=0; !cells.empty() && i<cells.size()-1; i++) {
        if (!food.empty()) {
            int closest = closest_cell(cells[i].get_position());
            cells[i].seek_food(food[closest].get_position());
            cells[i].move();
            if (cells[i].get_position() == food[closest].get_position()) {
                food[closest].die();
                utils::remove(food, closest);
                cells[i].eat(100);
            }
        }else if (!cells[i].is_alive()) {
            utils::remove(cells, i);
        }else {
            cells[i].move();
        }
    }
}

void Board::update_food() {

}

void Board::update(sf::Clock clock) {
    if (static_cast<int>(clock.getElapsedTime().asSeconds()) % 1 == 0) {
        //clock.restart();
        //gen_food();
    }
    update_cells();
    update_food();
    //std::cout<<food.size()<<"\n";
}

//===========================================
//	ACESSORS
//===========================================

std::vector<Animal>* Board::get_cells() {
    return &cells;
}

std::vector<Plant>* Board::get_food() {
    return &food;
}
