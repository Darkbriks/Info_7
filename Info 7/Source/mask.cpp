#include "../Header/mask.h"
#include "../Header/board.h"
#include <iostream>

using namespace std;

type_mask empty_mask() {const type_mask mask; return mask;}

int get_mask(const type_mask mask) {return *mask.mask;}

void clear_mask(const type_mask mask) {for (int i = 0; i < 64; i++) mask.set_mask(i/8, i%8, 0);}

void highlight_possible_moves(int x, int y, type_mask *mask, type_board board) // x = column, y = row
{
    if (board.get_piece(x, y) == 'K' or board.get_piece(x, y) == 'k') {highlight_possible_moves_king(x, y, mask, board);}
    if (board.get_piece(x, y) == 'R' or board.get_piece(x, y) == 'r') {highlight_possible_moves_rook(x, y, mask, board);}
}

void highlight_possible_moves_king(const int x, const int y, type_mask *mask, type_board board) // x = column, y = row
{
    for (int i = 1; i > -2; i--) // i = column
    {
        for (int j = -1; j < 2; j++) // j = row
        {
            if (i == 0 and j == 0) {mask->set_mask(x, y, 5);} // Check if the position is the king
            //else if (board.get_piece(x+j, y+i) == ' ') {mask->set_mask(x+j, y+i, 4);}
            else if (board.get_piece(x+i, y+j) == ' ') {mask->set_mask(x+i, y+j, 4);}
            //else if (is_enemy(board.get_piece(x, y), board.get_piece(x+j, y+i)) == true) {mask->set_mask(x+j, y+i, 1);}
            else if (is_enemy(board.get_piece(x, y), board.get_piece(x+i, y+j)) == true) {mask->set_mask(x+i, y+j, 1);}
        }
    }
}

void highlight_possible_moves_rook(const int x, const int y, type_mask* mask, type_board board) // x = column, y = row
{
    for (int direction = 0; direction < 4; direction++)
    {
        int i = 0, j = 0; // i = column, j = row
        while (true)
        {
            switch (direction)
            {
                case 0: i++; break; // Right
                case 1: i--; break; // Left
                case 2: j++; break; // Up
                case 3: j--; break; // Down
                default: break;
            }
            if (board.get_piece(x+i, y+j) == ' ') mask->set_mask(x+i, y+j, 4);
            else if (is_enemy(board.get_piece(x, y), board.get_piece(x+i, y+j)) == true) {mask->set_mask(x+i, y+j, 1); break;}
            else break;
        }
    }
    mask->set_mask(x, y, 5);
}