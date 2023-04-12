#pragma once
#include <string>

class type
{
public:
    struct type_board
    {
        // Attributes
        std::string fen_board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
        std::string fen_other = "wKQkq--0001";
        
        // Getters
        char get_piece(int i, int j) const;
        char get_turn() const;
        std::string get_castling(char color) const;
        std::string get_en_passant() const;
        int get_halfmove();
        int get_fullmove();
        std::string get_fen() const;

        // Setters
        void set_piece(int i, int j, char piece);
        void set_turn(char turn);
        void set_castling(char castling, bool value);
        void set_en_passant(std::string en_passant);
        void set_halfmove(int halfmove);
        void set_fullmove(int fullmove);
        void set_fen(std::string fen);
    };
};