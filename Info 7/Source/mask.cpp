#include "../Header/mask.h"
#include "../Header/board.h"
#include <iostream>

using namespace std;

/**
 * \brief Create and return a mask set to 0
 * \return type_mask, a mask set to 0
 */
type_mask empty_mask() {const type_mask mask; return mask;}

/**
 * \brief Set all cases of a mask to 0
 * \param mask The mask to clear
 */
void clear_mask(const type_mask mask) {for (int i = 0; i < 64; i++) mask.set_mask(i/8, i%8, 0);}

/**
 * \brief Highlight all possible moves of a piece
 * \param x The column of the piece
 * \param y The row of the piece
 * \param mask The mask to highlight
 * \param board The board
 */
void highlight_possible_moves(int x, int y, type_mask *mask, type_board board)
{
    if (board.get_piece(x, y) == 'K' or board.get_piece(x, y) == 'k') {highlight_possible_moves_king(x, y, mask, board);}
    if (board.get_piece(x, y) == 'R' or board.get_piece(x, y) == 'r') {highlight_possible_moves_rook(x, y, mask, board);}
	if (board.get_piece(x, y) == 'B' or board.get_piece(x, y) == 'b') {highlight_possible_moves_bishop(x, y, mask, board);}
}

/**
 * \brief Highlight all possible moves of a king
 * \n The king can move in all directions, but only one case at a time
 * \param x the column of the king
 * \param y the row of the king
 * \param mask the mask to highlight
 * \param board the board
 */
void highlight_possible_moves_king(const int x, const int y, type_mask *mask, type_board board)
{
    for (int i = 1; i > -2; i--) // i = column
    {
        for (int j = -1; j < 2; j++) // j = row
        {
            if (i == 0 and j == 0) {mask->set_mask(x, y, 5);} // Check if the position is the king
            else if (board.get_piece(x+i, y+j) == ' ') {mask->set_mask(x+i, y+j, 4);} // Set mask to blue
            else if (is_enemy(board.get_piece(x, y), board.get_piece(x+i, y+j)) == true) {mask->set_mask(x+i, y+j, 1);} // Set mask to red
        }
    }
}

/**
 * \brief Highlight all possible moves of a rook
 * \n The rook can move in horizontal and vertical directions, as many cases as it wants
 * \param x the column of the rook
 * \param y the row of the rook
 * \param mask the mask to highlight
 * \param board the board
 */
void highlight_possible_moves_rook(const int x, const int y, type_mask* mask, type_board board)
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

void highlight_possible_moves_bishop(const int x, const int y, type_mask* mask, type_board board)
{
    for (int direction = 0; direction < 4; direction++)
    {
        int i = 0, j = 0;
        while (true)
        {
            switch (direction)
            {
                case 0: i++; j++; break;
                case 1: i++; j--; break;
                case 2: i--; j++; break;
                case 3: i--; j--; break;
                default: break;
            }
            if (board.get_piece(x+i, y+j) == ' ') mask->set_mask(x+i, y+j, 4);
            else if (is_enemy(board.get_piece(x, y), board.get_piece(x+i, y+j)) == true) {mask->set_mask(x+i, y+j, 1); break;}
            else break;
        }
    }
	mask->set_mask(x, y, 5);
}