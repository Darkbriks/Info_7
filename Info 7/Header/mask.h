#ifndef MASK
#define MASK

#include "type.h"

// Methods
type_mask empty_mask(); // Returns an empty mask
void clear_mask(type_mask mask); // Resets the mask to 0

// Higlihts functions
int highlight_possible_moves(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a piece
int highlight_possible_moves_king(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a king (one square in all directions)
int highlight_possible_moves_rook(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a rook (all squares in horizontal and vertical directions)
int highlight_possible_moves_bishop(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a bishop (all squares in diagonal directions)
int highlight_possible_moves_queen(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a queen (all squares in all directions)
int highlight_possible_moves_knight(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a knight (L shape)
int highlight_possible_moves_pawn(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a pawn (one square forward, two squares forward (if it's the first move), and one square diagonally forward (if there's an enemy piece))

void highlight_movable_pieces(char color, type_mask *mask, type_board board); // Highlights all movable pieces of a color
void highlight_attacked_pieces(char color, type_mask *mask, type_board board); // Highlights all attacked pieces of a color
void highlight_take_pieces(int x, int y, type_mask *mask, type_board board); // Highlights all pieces that can take a piece

int sous_mask_choices(int choix);
void sous_mask_choices(int choix , type_board board, type_mask* mask);
void mask_choices_menu(type_board board, type_mask mask);
void mask_choices(type_board board, type_mask mask);

#endif