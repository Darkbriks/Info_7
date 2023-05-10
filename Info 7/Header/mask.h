#ifndef MASK
#define MASK

#include "type.h"

// Methods
type_mask empty_mask(); // Returns an empty mask
void clear_mask(type_mask mask); // Resets the mask to 0

// Higlihts functions
void highlight_possible_moves(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a piece
void highlight_possible_moves_king(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a king (one square in all directions)
void highlight_possible_moves_rook(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a rook (all squares in horizontal and vertical directions)
void highlight_possible_moves_bishop(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a bishop (all squares in diagonal directions)
void highlight_possible_moves_queen(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a queen (all squares in all directions)
void highlight_possible_moves_knight(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a knight (L shape)
void highlight_possible_moves_pawn(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a pawn (one square forward, two squares forward (if it's the first move), and one square diagonally forward (if there's an enemy piece))
int sous_mask_choices(int choix);
void sous_mask_choices(int choix , type_board board, type_mask* mask);
void mask_choices_menu(type_board board, type_mask mask);
void mask_choices(type_board board, type_mask mask);

#endif
