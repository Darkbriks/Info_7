#include "type.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#pragma region Getters
// Get the piece at the position (i, j)
char type_board::get_piece(const int i, const int j) const
{
    if (i < 0 || i > 7 || j < 0 || j > 7) {return '!';}
    return board[i*8 + j];
}

// Get the turn
char type_board::get_turn() const {return fen_other[0];}

// Get the castling rights for all colors (more use for fen conversion)
string type_board::get_castling() const
{
    stringstream castling;
    if (fen_other[1] == 'K') {castling << "K";}
    if (fen_other[2] == 'Q') {castling << "Q";}
    if (fen_other[3] == 'k') {castling << "k";}
    if (fen_other[4] == 'q') {castling << "q";}
    if (castling.str() == "") {castling << "-";} // If no castling rights, add a dash
    return castling.str();
}

// Get the castling rights for specified color and type (more use for checking castling rights in the game)
string type_board::get_castling(const char color) const
/* @param color : 'w' or 'b', in minuscule
 * @return : "KQ" if white can castle long and short, "-Q" if white can castle long, "K-" if white can castle short, "--" if white can't castle. Same for black. Empty string if invalid color.
 */
{
    if (color != 'w' && color != 'b') {return "";}
    stringstream castling;
    castling << fen_other[1 + (color == 'b')*2] << fen_other[2 + (color == 'b')*2]; // Add the castling rights to the string stream (0 = false, 1 = true)
    return castling.str(); // Return the string stream as a string
}

// Get the en passant case
string type_board::get_en_passant() const
{
    stringstream en_passant;
    en_passant << fen_other[5] << fen_other[6];
    if (en_passant.str() == "--") {return "-";} // If no en passant, return a dash
    return en_passant.str();
}

// Get the half move number
int type_board::get_halfmove() const
{
    stringstream halfmove;
    halfmove << fen_other[7] << fen_other[8];
    int halfmove_int; halfmove >> halfmove_int;
    return halfmove_int;
}

// Get the full move number
int type_board::get_fullmove() const
{
    stringstream fullmove;
    fullmove << fen_other[9] << fen_other[10];
    int fullmove_int; fullmove >> fullmove_int;
    return fullmove_int;
}

// Get the FEN
string type_board::get_fen() const
{
    stringstream fen_board;
    for (int i = 0; i < 8; i++)
    {
        int empty = 0; // Create an int to store the number of empty squares
        for (int j = 0; j < 8; j++)
        {
            if (board[8*i + j] == ' ') {empty++;} // If the square is empty, increment the number of empty squares
            else
            {
                if (empty > 0) {fen_board << empty; empty = 0;} // If there are empty squares before, add the number of empty squares to the string stream and reset the number of empty squares
                fen_board << board[8*i + j];
            }
        }
        if (empty > 0) {fen_board << empty;}  // If there are empty squares at the end of the row, add the number of empty squares to the string stream
        if (i < 7) {fen_board << '/';} // If it's not the last row, add a slash to the string stream
    }
    
    stringstream fen;
    fen << fen_board.str() << ' ' << get_turn() << ' ' << get_castling() << ' ' << get_en_passant() << ' ' << to_string(get_halfmove()) << ' ' << to_string(get_fullmove());
    return fen.str();
}
#pragma endregion

#pragma region Setters
// Set the piece at the position (i, j)
void type_board::set_piece(const int i, const int j, const char piece)
{
    if (i < 0 || i > 7 || j < 0 || j > 7) {return;}
    board[8*i + j] = piece;
}

// Set the turn
void type_board::set_turn(const char turn) {fen_other[0] = turn;}

// Set the castling rights for specified color and type
void type_board::set_castling(const char color, const bool castling)
/* @param color : 'w' or 'b' for set the castle short, and 'W' or 'B' for set the castle long
 * @param castling : true if the player can castle, false otherwise
 */
{
    if (color == 'w') {fen_other[1] = castling ? 'K' : '-';}
    else if (color == 'b') {fen_other[3] = castling ? 'k' : '-';}
    else if (color == 'W') {fen_other[2] = castling ? 'Q' : '-';}
    else if (color == 'B') {fen_other[4] = castling ? 'q' : '-';}
}

// Set the en passant case
void type_board::set_en_passant(const string en_passant) {fen_other[5] = en_passant[0]; fen_other[6] = en_passant[1];}

// Set the half move number
void type_board::set_halfmove(const int halfmove) {fen_other[7] = to_string(halfmove)[0]; fen_other[8] = to_string(halfmove)[1];}

// Set the full move number
void type_board::set_fullmove(const int fullmove) {fen_other[9] = to_string(fullmove)[0]; fen_other[10] = to_string(fullmove)[1];}

// Set the FEN
void type_board::set_board_with_fen(const string fen)
{
    // Set the board
    int i = 0; int j = 0; string fen_board = fen.substr(0, fen.find(' '));
    // Inversion du plateau, car le FEN est donné de la ligne 8 à la ligne 1
    reverse(fen_board.begin(), fen_board.end());
    
    for (int k = 0; k < fen_board.length(); k++)
    {
        if (fen_board[k] == ' ') {break;}
        if (fen_board[k] == '/') {i++; j = 0;}
        else if (fen_board[k] >= '1' && fen_board[k] <= '8') {for (int l = 0; l < fen_board[k] - '0'; l++) {board[8*i + j] = ' '; j++;}}
        else {board[8*i + j] = fen_board[k]; j++;}
    }
    
    // Set the other FEN parameters
    string fen_other_pure = fen.substr(fen.find(' ') + 1); // = w KQkq - 0 1
    fen_other = "wKQkq--0001";
    set_turn(fen_other_pure[0]);
    
    fen_other_pure = fen_other_pure.substr(fen_other_pure.find(' ') + 1); // = KQkq - 0 1
    set_castling('w', fen_other_pure[0] == 'K');
    set_castling('W', fen_other_pure[0] == 'Q' || fen_other_pure[1] == 'Q');
    set_castling('b', fen_other_pure[0] == 'k' || fen_other_pure[1] == 'k' || fen_other_pure[2] == 'k');
    set_castling('B', fen_other_pure[0] == 'q' || fen_other_pure[1] == 'q' || fen_other_pure[2] == 'q' || fen_other_pure[3] == 'q');

    fen_other_pure = fen_other_pure.substr(fen_other_pure.find(' ') + 1); // = - 0 1
    if (fen_other_pure[0] != '-') {set_en_passant(fen_other_pure.substr(0, 2));} else {set_en_passant("--");}

    fen_other_pure = fen_other_pure.substr(fen_other_pure.find(' ') + 1); // = 0 1
    set_halfmove(stoi(fen_other_pure.substr(0, fen_other_pure.find(' '))));

    fen_other_pure = fen_other_pure.substr(fen_other_pure.find(' ') + 1); // = 1
    set_fullmove(stoi(fen_other_pure));
}

// Set the board with an array of pieces
void type_board::set_board_with_array(char array[64]) {delete[] board; board = array;}
#pragma endregion

#pragma region Constructors
// Default constructor
type_board::type_board()
{
    // Initialize the board to the starting position
    board = new char[64];
    fen_other = "wKQkq--0001";
    cout << "Board initialized" << endl;
}

#pragma endregion