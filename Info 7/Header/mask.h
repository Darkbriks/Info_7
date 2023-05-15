#ifndef MASK
#define MASK

#include "type.h"

// Methods
type_mask empty_mask(); // Returns an empty mask
void clear_mask(type_mask mask); // Resets the mask to 0

// Check functions
bool king_in_check(char color, type_board board); // Returns true if the king of the color is in check
bool king_in_check(char color, int x1, int y1, int x2, int y2, type_board board); // Returns true if the king of the color is in check after the move
bool king_in_checkmate(char color, type_board board); // Returns true if the king of the color is in checkmate
bool king_in_checkmate(char color, int x1, int y1, int x2, int y2, type_board board); // Returns true if the king of the color is in checkmate after the move


// Higlihts functions
bool set_case_color(int x1, int y1, int x2, int y2, char piece, type_mask *mask, type_board board, int *n); // Set case color in function of the piece color and possible moves
int highlight_possible_moves(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a piece
int highlight_possible_moves_king(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a king (one square in all directions)
int highlight_possible_moves_rook(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a rook (all squares in horizontal and vertical directions)
int highlight_possible_moves_bishop(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a bishop (all squares in diagonal directions)
int highlight_possible_moves_queen(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a queen (all squares in all directions)
int highlight_possible_moves_knight(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a knight (L shape)
int highlight_possible_moves_pawn(int x, int y, type_mask *mask, type_board board); // Highlights all possible moves for a pawn (one square forward, two squares forward (if it's the first move), and one square diagonally forward (if there's an enemy piece))

void highlight_movable_pieces(char color, type_mask *mask, type_board board); // Highlights all movable pieces of a color
bool attacked_piece(const char piece, const int x, const int y, type_board board); // Returns true if the piece is attacked
void highlight_attacked_pieces(char color, type_mask *mask, type_board board); // Highlights all attacked pieces of a color
void highlight_take_pieces(int x, int y, type_mask *mask, type_board board); // Highlights all pieces that can take a piece

int sous_mask_choices(int choix);
void sous_mask_choices(int choix , type_board board, type_mask* mask);
void mask_choices_menu(type_board board, type_mask mask);
void mask_choices(type_board board, type_mask mask);

#endif