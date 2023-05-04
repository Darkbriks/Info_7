#include "mask.h"
#include "board.h"
#include <iostream>

using namespace std;

type_mask empty_mask() {const type_mask mask; return mask;}

int get_mask(const type_mask mask) {return *mask.mask;}

void clear_mask(const type_mask mask) {for (int i = 0; i < 64; i++) mask.set_mask(i/8, i%8, 0);}

void highlight_possible_moves(int x, int y, type_mask *mask, type_board board)
{
    if (board.get_piece(x, y) == 'K' or board.get_piece(x, y) == 'k') {highlight_possible_moves_king(x, y, mask, board);}
    if (board.get_piece(x, y) == 'R' or board.get_piece(x, y) == 'r') {highlight_possible_moves_rook(x, y, mask, board);}
}

void highlight_possible_moves_king(int x, int y, type_mask *mask, type_board board)
{
    for (int i = 1; i > -2; i--)
    {
        for (int j = -1; j < 2; j++)
        {
            if (i == 0 and j == 0) {mask->set_mask(x, y, 5);} // Check if the position is the king
            else if (board.get_piece(x+j, y+i) == ' ') {mask->set_mask(x+j, y+i, 4);}
            else if (is_enemy(board.get_piece(x, y), board.get_piece(x+j, y+i)) == true) {mask->set_mask(x+j, y+i, 1);}
        }
    }
}

void highlight_possible_moves_rook(int x, int y, type_mask* mask, type_board board)
{
    for (int i = 0; i < 4; i++)
    {
        int n = 0, m = 0;
        while (true)
        {
            switch (i)
            {
                case 0: n++; break;
                case 1: n--; break;
                case 2: m++; break;
                case 3: m--; break;
                default: break;
            }
            if (board.get_piece(x+n, y+m) == ' ') mask->set_mask(x+n, y+m, 4);
            else if (is_enemy(board.get_piece(x, y), board.get_piece(x+n, y+m)) == true) {mask->set_mask(x+n, y+m, 1); break;}
            else break;
        }
    }
    mask->set_mask(x, y, 5);
}