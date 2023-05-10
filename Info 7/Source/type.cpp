#include "../Header/type.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#pragma region Type_board
#pragma region Getters
/**
 * \brief return the piece at the position (i, j) with the following convention :
 * \n i = 0 corresponds to the column a
 * \n j = 0 corresponds to the row 1 \n
 * \n If the position is invalid, return '!'
 * \n If the position is empty, return ' '
 * \param i the column
 * \param j the row
 * \return char, the piece at the position (i, j)
 */
char type_board::get_piece(const int i, const int j) const
{
    if (i < 0 || i > 7 || j < 0 || j > 7) {return '!';} // If the position is invalid, return '!'
    return board[8*j + i];
}

/**
 * \brief Return the turn with the following convention :
 * \n 'w' for white
 * \n 'b' for black
 * \return char, the turn
 */
char type_board::get_turn() const {return fen_other[0];}

/**
 * \brief Return the castling rights with the following convention :
 * \n 'K' if white can castle short
 * \n 'Q' if white can castle long
 * \n 'k' if black can castle short
 * \n 'q' if black can castle long
 * \n '-' if no castling rights
 * \return string, the castling rights 
 */
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

/**
 * \brief Return the castling rights for the specified color with the following convention :
 * \n 'K' if the color can castle short
 * \n 'Q' if the color can castle long
 * \n '-' if the color can't castle
 * \n If the color is invalid, return an empty string
 * \param color 'w' or 'b', in minuscule
 * \return string, the castling rights for the specified color
 */
string type_board::get_castling(const char color) const
{
    if (color != 'w' && color != 'b') {return "";}
    stringstream castling;
    castling << fen_other[1 + (color == 'b')*2] << fen_other[2 + (color == 'b')*2]; // Add the castling rights to the string stream (0 = false, 1 = true)
    return castling.str();
}

/**
 * \brief Return the en passant square with the following convention :
 * \n The first character is the column
 * \n The second character is the row
 * \n If there is no en passant, return a dash
 * \return string, the en passant square
 */
string type_board::get_en_passant() const
{
    stringstream en_passant;
    en_passant << fen_other[5] << fen_other[6];
    if (en_passant.str() == "--") {return "-";} // If no en passant, return a dash
    return en_passant.str();
}

/**
 * \brief Return the halfmove clock.
 * \n The halfmove clock is the number since the last capture or pawn move.
 * \return int, the halfmove clock
 */
int type_board::get_halfmove() const
{
    stringstream halfmove;
    halfmove << fen_other[7] << fen_other[8];
    int halfmove_int; halfmove >> halfmove_int;
    return halfmove_int;
}

/**
 * \brief Return the fullmove number.
 * \n The fullmove number is the number of the move, starting at 1, and incremented after black's move.
 * \return int, the fullmove number
 */
int type_board::get_fullmove() const
{
    stringstream fullmove;
    fullmove << fen_other[9] << fen_other[10];
    int fullmove_int; fullmove >> fullmove_int;
    return fullmove_int;
}

/**
 * \brief Return the FEN string.
 * \n The FEN string is the board, the turn, the castling rights, the en passant square, the halfmove clock and the fullmove number.
 * \n An example of FEN string is : "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
 * \return string, the FEN string
 */
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
/**
 * \brief Set a piece on the board at the specified position.
 * \n If the position is invalid, do nothing.
 * \n WARNING : the piece is not checked, so it must be valid.
 * \param i the column
 * \param j the row
 * \param piece 
 */
void type_board::set_piece(const int i, const int j, const char piece)
{
    if (i < 0 || i > 7 || j < 0 || j > 7) {return;}
    board[8*j + i] = piece;
}

/**
 * \brief Set the turn.
 * \n WARNING : the turn is not checked, so it must be valid.
 * \param turn 'w' or 'b'
 */
void type_board::set_turn(const char turn) {fen_other[0] = turn;}

/**
 * \brief Set the castling rights for the specified color.
 * \param color 'w' or 'b' for set the castle short, and 'W' or 'B' for set the castle long
 * \param castling true if the player can castle, false otherwise
 */
void type_board::set_castling(const char color, const bool castling)
{
    if (color == 'w') {castling ? fen_other[1] = 'K' : fen_other[1] = '-';} // true = 'K', false = '-'
    else if (color == 'b') {castling ? fen_other[3] = 'k' : fen_other[3] = '-';}
    else if (color == 'W') {castling ? fen_other[2] = 'Q' : fen_other[2] = '-';}
    else if (color == 'B') {castling ? fen_other[4] = 'q' : fen_other[4] = '-';}
}

/**
 * \brief Set the en passant square.
 * \n WARNING : the en passant square is not checked, so it must be valid.
 * \param en_passant the en passant square with the following convention :
 * \n The first character is the column
 * \n The second character is the row
 * \n If there is no en passant, set a dash
 */
void type_board::set_en_passant(const string en_passant) {fen_other[5] = en_passant[0]; fen_other[6] = en_passant[1];}

/**
 * \brief Set the halfmove clock.
 * \n WARNING : the halfmove clock is not checked, so it must be valid.
 * \param halfmove the halfmove clock
 */
void type_board::set_halfmove(const int halfmove) {fen_other[7] = to_string(halfmove)[0]; fen_other[8] = to_string(halfmove)[1];}

/**
 * \brief Set the fullmove number.
 * \n WARNING : the fullmove number is not checked, so it must be valid.
 * \param fullmove the fullmove number
 */
void type_board::set_fullmove(const int fullmove) {fen_other[9] = to_string(fullmove)[0]; fen_other[10] = to_string(fullmove)[1];}

/**
 * \brief Set the board with a FEN string.
 * \n The FEN string is the board, the turn, the castling rights, the en passant square, the halfmove clock and the fullmove number.
 * \n An example of FEN string is : "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
 * \n WARNING : the FEN string is not checked, so it must be valid.
 * \param fen the FEN string
 */
void type_board::set_board_with_fen(const string fen)
{
    // Set the board
    int i = 0; int j = 7; string fen_board = fen.substr(0, fen.find(' '));
    // Inversion du plateau, car le FEN est donné de la ligne 8 à la ligne 1
    //reverse(fen_board.begin(), fen_board.end());

    // Set the board. The FEN board is given from the 8th rank to the 1st rank, so we assign the board from the last cell to the first cell
    for (int k = 0; k < fen_board.length(); k++)
    {
        if (fen_board[k] == ' ') {break;}
        if (fen_board[k] == '/') {i = 0; j--;}
        else if (fen_board[k] >= '1' && fen_board[k] <= '8') {for (int l = 0; l < fen_board[k] - '0'; l++) {set_piece(i, j, ' '); i++;}}
        else {set_piece(i, j, fen_board[k]); i++;}
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

/**
 * \brief Set the board with an array.
 * \n The array is the board.
 * \n The array must be a 64 characters array.
 * \n An example of array is : "RNBQKBNRPPPPPPPP--/28/--pppppppprnbqkbnr"
 * \n WARNING : the array is not checked, so it must be valid.
 * \param array the array
 */
void type_board::set_board_with_array(char array[64]) {for (int i = 0; i < 64; i++) {board[i] = array[i];}}
#pragma endregion

#pragma region Constructors
/**
 * \brief Default constructor.
 * \n Initialize the board to the starting position.
 */
type_board::type_board()
{
    board = new char[64];
    fen_other = "wKQkq--0001";
    cout << "Board initialized" << endl;
}

#pragma endregion
#pragma endregion

#pragma region Type_mask
/**
 * \brief Get the mask at the given position.
 * \n If the position is out of bounds, return -1.
 * \param i the column
 * \param j the row
 * \return the mask at the given position
 */
int type_mask::get_mask(const int i, const int j) const {return (i >= 0 && i < 8 && j >= 0 && j < 8) ? mask[8*j + i] : -1;}

/**
 * \brief Set the mask at the given position.
 * \n If the position is out of bounds, do nothing.
 * \n WARNING : the mask is not checked, so it must be valid.
 * \param i the column
 * \param j the row
 * \param value the value to set
 */
void type_mask::set_mask(const int i, const int j, const int value) const {if (i >= 0 && i < 8 && j >= 0 && j < 8) {mask[8*j + i] = value;}}

/**
 * \brief Default constructor.
 * \n Initialize the mask to 0.
 */
type_mask::type_mask() {mask = new int[64]; for (int i = 0; i < 64; i++) {mask[i] = 0;}}
#pragma endregion