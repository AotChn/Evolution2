#pragma once

#include "../graphics/window/window.h"
#include "../graphics/constants.h"
#include "../cell/cell.h"
#include "../cell/animal.h"
#include "../cell/plant.h"
#include "../utils/utils.h"


#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>

class Board {
    std::vector<Plant> food;
    std::vector<Animal> cells;
    
public:

    Board(){};
    ~Board(){}

//===========================================
//	BOARD MANIPULATION
//===========================================

     //initializes board 
    void init_board(int food=board_params::FOOD_AMT, int cells=board_params::CELLS_AMT);
    //add food with pos 
    void add_food(int x, int y);
    //add food randomly
    void add_food();
    //add cell with pos and speed
    void add_cell(int x, int y, int s);
    //add cell randomly
    void add_cell(int speed_MIN=1, int speed_MAX=4);
    //returns index of closeset food cell
    int closest_cell(Position);
    //fills board with cells and food
    void fill_board(int f_amt=100, int c_amt=10);
    //fills board with food
    void fill_food(int amt=100);
    //fills board with cells
    void fill_cells(int amt=10);

//===========================================
//	UPDATE
//===========================================

    //updates all actions on board
    void update(sf::Clock clock);
    //updates cell actions
    void update_cells();
    //update food generation
    void update_food();

//===========================================
//	ACCESSORS
//===========================================

    //return cells vector
    std::vector<Animal>* get_cells();
    //returns food vector 
    std::vector<Plant>* get_food();

};


