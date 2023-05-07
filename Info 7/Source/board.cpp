#include "../Header/board.h"
#include "../Header/type.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

// Print FEN
void print_fen(type_board type_board) {cout << "FEN: " << type_board.get_fen() << endl;}

// Empty the type_board
void empty_board(type_board type_board) {type_board.set_board_with_fen("8/8/8/8/8/8/8/8 w - - 0 0");}

// Reset the game
void reset_board(type_board type_board) {type_board.set_board_with_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");}

// Move a piece
void move_piece(const int i1, const int j1, const int i2, const int j2, type_board type_board) // i = column, j = row
{
    char piece = type_board.get_piece(i1, j1);
    type_board.set_piece(i1, j1, ' ');
    type_board.set_piece(i2, j2, piece);
}

// Check if two pieces are enemies
bool is_enemy(const char piece1, const char piece2)
{
    if (piece1 >= 'A' and piece1 <= 'Z' and piece2 >= 'a' and piece2 <= 'z') {return true;}
    if (piece1 >= 'a' and piece1 <= 'z' and piece2 >= 'A' and piece2 <= 'Z') {return true;}
    return false;
}

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