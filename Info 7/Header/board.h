#ifndef BOARD
#define BOARD
#include <string>
#include "type.h"

// Methods
void print_fen(type_board type_board); // Print the FEN string corresponding to the type_board
void empty_board(type_board type_board); // Empty the type_board
void reset_board(type_board type_board); // Reset the game
void move_piece(int i1, int j1, int i2, int j2, type_board type_board); // Move a piece
bool is_enemy(char piece1, char piece2); // Check if two pieces are enemies

// Write and read FEN in a file
void write_fen(type_board type_board, std::string file_name); // Write FEN corresponding to the type_board in a file
void read_fen(type_board type_board, std::string file_name); // Read FEN in a file and set the type_board with it

#endif