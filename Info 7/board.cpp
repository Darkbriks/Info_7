#include "board.h"
#include <iostream>
#include <string>
#include <sstream>
#include "type.h"
using namespace std;

#pragma region Methods

// Print FEN
void board::print_fen(type::type_board type_board) {cout << "FEN: " << type_board.get_fen() << endl;}

// Print the type_board


// Empty the type_board
void board::empty_board(type::type_board type_board) {type_board.fen_board = "8/8/8/8/8/8/8/8";}

// Reset the game
void board::reset_game(type::type_board type_board) {type_board.fen_board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"; type_board.fen_other = "wKQkq--0001";}

// Move a piece
void board::move_piece(const int i1, const int j1, const int i2, const int j2, type::type_board type_board) {char piece = type_board.get_piece(i1, j1); type_board.set_piece(i1, j1, ' '); type_board.set_piece(i2, j2, piece);}

#pragma endregion Methods