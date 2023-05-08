#include "../Header/board.h"
#include "../Header/type.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

/**
 * \brief Print the FEN string corresponding to the type_board
 * \param type_board The type_board to print
 */
void print_fen(type_board type_board) {cout << "FEN : " << type_board.get_fen() << endl;}

/**
 * \brief Empty the type_board using set_board_with_fen
 * \n The FEN string used is "8/8/8/8/8/8/8/8 w - - 0 0"
 * \param type_board The type_board to empty
 */
void empty_board(type_board type_board) {type_board.set_board_with_fen("8/8/8/8/8/8/8/8 w - - 0 0");}

/**
 * \brief Reset the game using set_board_with_fen
 * \n The FEN string used is "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
 * \param type_board 
 */
void reset_board(type_board type_board) {type_board.set_board_with_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");}

/**
 * \brief Move a piece from (i1, j1) to (i2, j2)
 * \n The piece at (i1, j1) is replaced by a space
 * \n WARNING : The piece at (i2, j2) is lost
 * \n WARNING : The move is not checked, please check it before calling this function
 * \n i = column, j = row
 * \param i1 the column of the piece to move
 * \param j1 the row of the piece to move
 * \param i2 the column of the destination
 * \param j2 the row of the destination
 * \param type_board The type_board to modify
 */
void move_piece(const int i1, const int j1, const int i2, const int j2, type_board type_board)
{
    char piece = type_board.get_piece(i1, j1);
    type_board.set_piece(i1, j1, ' ');
    type_board.set_piece(i2, j2, piece);
}

/**
 * \brief Check if two pieces are enemies (one is white and the other is black) and return true if it is the case
 * \param piece1 the first piece
 * \param piece2 the second piece
 * \return true if the pieces are enemies, false otherwise
 */
bool is_enemy(const char piece1, const char piece2)
{
    if (piece1 >= 'A' and piece1 <= 'Z' and piece2 >= 'a' and piece2 <= 'z') {return true;}
    if (piece1 >= 'a' and piece1 <= 'z' and piece2 >= 'A' and piece2 <= 'Z') {return true;}
    return false;
}

/**
 * \brief Write FEN corresponding to the type_board in a text file
 * \param type_board the type_board to write
 * \param file_name the name of the file
 */
void write_fen(type_board type_board, std::string file_name)
{
    ofstream file;
    file.open(file_name);
    if (file.is_open()) {file << type_board.get_fen(); file.close();}
    else cout << "Unable to open file";
}

/**
 * \brief Read FEN in a text file and set the type_board with it
 * \param type_board The type_board to modify
 * \param file_name The name of the file
 */
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