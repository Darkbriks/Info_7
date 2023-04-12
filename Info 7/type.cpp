#include "type.h"
#include <string>
#include <sstream>
using namespace std;

#pragma region Getters
// Get the piece at the position (i, j)
char type::type_board::get_piece(int i, const int j) const // i = row, j = column
{
    // Check if the position is valid
    if (i < 0 || i > 7 || j < 0 || j > 7) {return ' ';}
    
    // If i = 1, it's the last row, so we have to invert the index
    // Split the string with '/'
    stringstream fen_board_stream(fen_board); // Create a string stream
    string fen_board_row; // Create a string to store the row
    i = 7 - i; // Invert the index
    for (int k = 0; k <= i; k++) {getline(fen_board_stream, fen_board_row, '/');} // Get the row
    stringstream fen_board_row_stream(fen_board_row); // Create a string stream

    // Get the piece
    char fen_board_row_piece; // Create a char to store the piece
    for (int k = 0; k <= j; k++)
    {
        fen_board_row_stream >> fen_board_row_piece; // Get the piece
        if (fen_board_row_piece >= '0' && fen_board_row_piece <= '9') {k += fen_board_row_piece - 1;} // If the piece is a number, we have to skip the next pieces
    }

    // Return the piece
    // If the piece is a number, return a space
    if (fen_board_row_piece >= '0' && fen_board_row_piece <= '9') {return ' ';}
    return fen_board_row_piece;
}

// Get the turn
char type::type_board::get_turn() const {return fen_other[0];}

// Get the castling rights for specified color and type
string type::type_board::get_castling(const char color) const
/* @param color : 'w' or 'b', in minuscule
 * @return : "KQ" if white can castle long and short, "Q" if white can castle long, "K" if white can castle short, "-" if white can't castle. Same for black. Empty string if invalid color.
 */
{
    if (color != 'w' && color != 'b') {return "";} // Invalid color
    stringstream castling; // Create a string stream
    castling << fen_other[1 + (color == 'b')*2] << fen_other[2 + (color == 'b')*2]; // Add the castling rights to the string stream (0 = false, 1 = true)
    return castling.str(); // Return the string stream as a string
}

// Get the en passant case
string type::type_board::get_en_passant() const
{
    stringstream en_passant; // Create a string stream
    en_passant << fen_other[5] << fen_other[6]; // Add the en passant case to the string stream
    return en_passant.str(); // Return the string stream as a string
}

// Get the half move number
int type::type_board::get_halfmove()
{
    stringstream halfmove; // Create a string stream
    halfmove << fen_other[7] << fen_other[8]; // Add the halfmove number to the string stream
    return stoi(halfmove.str()); // Return the string stream as an int
}

// Get the full move number
int type::type_board::get_fullmove()
{
    stringstream fullmove; // Create a string stream
    fullmove << fen_other[9] << fen_other[10]; // Add the fullmove number to the string stream
    return stoi(fullmove.str()); // Return the string stream as an int
}

// Get the FEN string
string type::type_board::get_fen() const
{
    stringstream fen; // Create a string stream
    fen << fen_board << " " << fen_other[0] << " " << fen_other[1] << fen_other[2] << fen_other[3] << fen_other[4] << " " << fen_other[5] << fen_other[6] << " " << fen_other[7] << fen_other[8] << " " << fen_other[9] << fen_other[10]; // Add the FEN string to the string stream
    return fen.str(); // Return the string stream as a string
}

#pragma endregion Getters

#pragma region Setters

// Set the piece at the position (i, j)
void type::type_board::set_piece(int i, const int j, const char piece)
{
    // Check if the position is valid
    if (i < 0 || i > 7 || j < 0 || j > 7) {return;}

    // Check if the piece is valid
    if (piece != ' ' && piece != 'p' && piece != 'n' && piece != 'b' && piece != 'r' && piece != 'q' && piece != 'k' && piece != 'P' && piece != 'N' && piece != 'B' && piece != 'R' && piece != 'Q' && piece != 'K') {return;}
    
    stringstream fen_board_stream(fen_board); // Create a string stream
    string fen_board_array[8]; // Create a string array to store the rows
    i = 7 - i; // Invert the index
    for (int k = 0; k < 8; k++) {getline(fen_board_stream, fen_board_array[k], '/');} // Get the rows

    // Convert the row i to a char array
    char fen_board_i_array[8];
    // While the row i is not empty
    int k = 0;
    while (fen_board_array[i].length() > 0)
    {
        // If the first character is a number, we have to skip the next characters
        if (fen_board_array[i][0] >= '0' && fen_board_array[i][0] <= '9')
        {
            for (int l = 0; l < fen_board_array[i][0] - '0'; l++) {fen_board_i_array[k++] = ' ';}
            fen_board_array[i].erase(0, 1); // Erase the first character
        }
        else
        {
            fen_board_i_array[k++] = fen_board_array[i][0]; // Add the first character to the char array
            fen_board_array[i].erase(0, 1); // Erase the first character
        }
    }

    // Set the piece
    fen_board_i_array[j] = piece; // Set the piece

    // Convert the char array to a string
    stringstream fen_board_i_stream; // Create a string stream
    for (int k = 0; k < 8; k++)
    {
        // If the character is a space, we have to count the number of spaces
        if (fen_board_i_array[k] == ' ')
        {
            int l = k;
            while (fen_board_i_array[l] == ' ') {l++;}
            fen_board_i_stream << l - k; // Add the number of spaces to the string stream
            k = l - 1; // Set k to the last space
        }
        else {fen_board_i_stream << fen_board_i_array[k];} // Add the character to the string stream
    }

    // Set the FEN type_board
    fen_board_array[i] = fen_board_i_stream.str(); // Set the row i
    fen_board = ""; // Reset the FEN type_board
    for (int m = 0; m < 8; m++)
    {
        fen_board += fen_board_array[m] + '/'; // Add the row to the FEN type_board
    }

    // Remove the last '/' if it exists
    if (fen_board[fen_board.length() - 1] == '/') {fen_board.erase(fen_board.length() - 1, 1);}
}

// Set the turn
void type::type_board::set_turn(const char turn) {fen_other[0] = turn;}

// Set the castling rights for specified color and type
void type::type_board::set_castling(const char castling, const bool value)
/* @param castling : 'K' or 'Q', in minuscule
 * @param value : true or false
 */
{
    if (castling != 'K' && castling != 'k' && castling != 'Q' && castling != 'q') {return;} // Invalid castling
    fen_other[1 + (castling == 'Q') + (castling == 'k')*2 + (castling == 'q')*3] = value ? castling : '-'; // Set the castling rights. If value = true, set the castling rights to the castling parameter, else set it to '-'
}

// Set the en passant case
void type::type_board::set_en_passant(const string en_passant)
{
    fen_other[5] = en_passant[0];
    fen_other[6] = en_passant[1];
}

// Set the half move number
void type::type_board::set_halfmove(const int halfmove)
{
    stringstream halfmove_stream; // Create a string stream
    if (halfmove < 10) {halfmove_stream << "0";} // If the halfmove number is less than 10, add a 0 to the string stream
    halfmove_stream << halfmove; // Add the halfmove number to the string stream
    fen_other[7] = halfmove_stream.str()[0]; // Set the halfmove number
    fen_other[8] = halfmove_stream.str()[1]; // Set the halfmove number
}

// Set the full move number
void type::type_board::set_fullmove(const int fullmove)
{
    stringstream fullmove_stream; // Create a string stream
    if (fullmove < 10) {fullmove_stream << "0";} // If the fullmove number is less than 10, add a 0 to the string stream
    fullmove_stream << fullmove; // Add the fullmove number to the string stream
    fen_other[9] = fullmove_stream.str()[0]; // Set the fullmove number
    fen_other[10] = fullmove_stream.str()[1]; // Set the fullmove number
}

// Set the FEN
void type::type_board::set_fen(const string fen)
{
    fen_board = fen.substr(0, fen.find(" ")); // Set the type_board
    fen_other = fen.substr(fen.find(" ") + 1); // Set the other
}

#pragma endregion Setters