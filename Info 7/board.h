#pragma once
#include "type.h"

class board 
{
public:
    // Methods
    void print_fen(type::type_board type_board);
    void empty_board(type::type_board type_board);
    void reset_game(type::type_board type_board);
    void move_piece(int i1, int j1, int i2, int j2, type::type_board type_board);
};