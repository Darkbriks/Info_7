#include "mask.h"
#include <iostream>

using namespace std;

type_mask empty_mask() {const type_mask mask; return mask;}

int get_mask(const type_mask mask) {return *mask.mask;}

void clear_mask(const type_mask mask) {for (int i = 0; i < 64; i++) mask.set_mask(i/8, i%8, 0);}

void highlight_possible_moves(int x, int y, type_mask mask, type_board board)
{
    if (board.get_piece(x, y) == 'K' or board.get_piece(x, y) == 'k') {highlight_possible_moves_king(x, y, mask, board);}
    if (board.get_piece(x, y) == 'R' or board.get_piece(x, y) == 'r') {highlight_possible_moves_rook(x, y, mask, board);}
}

void highlight_possible_moves_king(int x, int y, type_mask mask, type_board board) {}

void highlight_possible_moves_rook(int x, int y, type_mask mask, type_board board) {}