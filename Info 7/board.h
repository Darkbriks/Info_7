﻿#pragma once
#include "type.h"

class board 
{
public:
    // Methods
    void print_fen(type::type_board type_board);
    void empty_board(type::type_board type_board);
    void reset_game(type::type_board type_board);
    void move_piece(int i1, int j1, int i2, int j2, type::type_board type_board);

    // Write and read FEN in a file
    void write_fen(type::type_board type_board, std::string file_name);
    void read_fen(type::type_board type_board, std::string file_name);
};