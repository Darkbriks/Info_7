#include "board.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "type.h"
using namespace std;

// Print FEN
void board::print_fen(type::type_board type_board) {cout << "FEN: " << type_board.get_fen() << endl;}

// Empty the type_board
void board::empty_board(type::type_board type_board) {type_board.fen_board = "8/8/8/8/8/8/8/8";}

// Reset the game
void board::reset_game(type::type_board type_board) {type_board.fen_board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"; type_board.fen_other = "wKQkq--0001";}

// Move a piece
void board::move_piece(const int i1, const int j1, const int i2, const int j2, type::type_board type_board) {char piece = type_board.get_piece(i1, j1); type_board.set_piece(i1, j1, ' '); type_board.set_piece(i2, j2, piece);}

// Write FEN in a file
void board::write_fen(type::type_board type_board, std::string file_name)
{
    ofstream file;
    file.open(file_name);
    if (file.is_open()) {file << type_board.get_fen(); file.close();}
    else cout << "Unable to open file";
}

// Read FEN in a file
void board::read_fen(type::type_board type_board, std::string file_name)
{
    ifstream file;
    file.open(file_name);
    if (file.is_open())
    {
        string fen;
        getline(file, fen);
        type_board.set_fen(fen);
        file.close();
    }
    else cout << "Unable to open file";
}