#ifndef TYPE
#define TYPE

#include <string>

struct type_board
{
    // Attributes
    char *board = new char[64];// Tableau de 64 cases qui contiennent les pièces
    std::string fen_other;

    // Constructor
    type_board();

    // Getters
    char get_piece(int i, int j) const;
    char get_turn() const;
    std::string get_castling() const;
    std::string get_castling(char color) const;
    std::string get_en_passant() const;
    int get_halfmove() const;
    int get_fullmove() const;
    std::string get_fen() const;

    // Setters
    void set_piece(int i, int j, char piece);
    void set_turn(char turn);
    void set_castling(char castling, bool value);
    void set_en_passant(std::string en_passant);
    void set_halfmove(int halfmove);
    void set_fullmove(int fullmove);
    void set_board_with_fen(std::string fen);
    void set_board_with_array(char array[64]);
};

#endif