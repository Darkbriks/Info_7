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

void highlight_possible_moves_rook(int x, int y, type_mask* mask, type_board board)
{
    mask->set_mask(x,y,5);
    int i =x+1;
    while(i<=7)
    {
        if(board.get_piece(i,y) != ' ')
        {
            mask->set_mask(i,y,1);
            i = 8;
        }
        else
        {
            mask->set_mask(i,y,4);
            i=i+1;
        }
    }
    i =y-1;
    while(i>=0)
    {
        if(board.get_piece(x,i) != ' ')
        {
            mask->set_mask(x,i,1);
            i = -1;
        }
        else
        {
            mask->set_mask(x,i,4);
            i=i-1;
        }
    }
    i =x-1;
    while(i>=0)
    {
        if(board.get_piece(i,y) != ' ')
        {
            mask->set_mask(i,y,1);
            i = -1;
        }
        else
        {
            mask->set_mask(i,y,4);
            i=i-1;
        }
    }
    i =y+1;
    while(i<=7)
    {
        if(board.get_piece(x,i) != ' ')
        {
            mask->set_mask(x,i,1);
            i = 8;
        }
        else
        {
            mask->set_mask(x,i,4);
            i=i+1;
        }
    }
}
