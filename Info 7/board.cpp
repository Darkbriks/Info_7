#include "board.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "type.h"
using namespace std;

// Print FEN
void print_fen(type_board type_board) {cout << "FEN: " << type_board.get_fen() << endl;}

// Empty the type_board
void empty_board(type_board type_board) {type_board.set_board_with_fen("8/8/8/8/8/8/8/8");}

// Reset the game
void reset_board(type_board type_board) {type_board.set_board_with_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"); type_board.fen_other = "wKQkq--0001";}

// Move a piece
void move_piece(const int i1, const int j1, const int i2, const int j2, type_board type_board) {char piece = type_board.get_piece(i1, j1); type_board.set_piece(i1, j1, ' '); type_board.set_piece(i2, j2, piece);}

// Write FEN in a file
void write_fen(type_board type_board, std::string file_name)
{
    ofstream file;
    file.open(file_name);
    if (file.is_open()) {file << type_board.get_fen(); file.close();}
    else cout << "Unable to open file";
}

// Read FEN in a file
void read_fen(type_board type_board, std::string file_name)
{
    ifstream file;
    file.open(file_name);
    if (file.is_open())
    {
        string fen;
        getline(file, fen);
        type_board.set_board_with_fen(fen);
        file.close();
    }
    else cout << "Unable to open file";
}