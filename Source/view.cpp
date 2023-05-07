#include "../Header/view.h"
#include "../Header/type.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<char,char> symbole_map ={{'R', 'R'},{'N', 'N'},{'B', 'B'},{'Q', 'Q'},{'K', 'K'},{'P', 'P'},{'r', 'r'},{'n', 'n'},{'b', 'b'},{'q', 'q'},{'k', 'k'},{'p', 'p'}, {' ', '-'}};
map<int, int> color_map = {{0, 0}, {1, 130}, {2, 160}, {3, 82}, {4, 214}, {5, 27}, {6, 57}, {7, 51}, {8, 153}};

void print_square_color(const char piece,const int color) {set_background(color); set_foreground(piece);}

void set_background(const int color) {cout << "\x1b[48;5;" + to_string(color_map[color]) + "m" ;}

void set_foreground(const char piece) {cout << ' ' << symbole_map[piece] << ' ';}

void print_board(type_board board)// Affiche le plateau
{
    cout << "Tour " << board.get_fullmove() << ", C'est au " << (board.get_turn() == 'w' ? "blanc" : "noir") << " de jouer." << endl;
    cout << "Il n'y a pas eu de prise ou de coup de pion depuis " << board.get_halfmove() << " coups." << endl;
    
    cout << " ----------------------------" << endl << '|' << "   a  b  c  d  e  f  g  h   " << '|' << endl;
    for(int y = 7; y >= 0; y--)
    {
        cout << "|" << y+1 << " " ;
        for(int x = 0; x < 8; x++)
        {
            set_foreground(board.get_piece(x, y));
        }
        cout << ' ' << y+1 << '|' << endl;
    }
    cout << '|' << "   a  b  c  d  e  f  g  h   " << '|' << endl << " ----------------------------" << endl;
}

void print_board(type_board board, const type_mask mask)// Affiche le plateau avec un mask
{
    cout << "Tour " << board.get_fullmove() << ", C'est au " << (board.get_turn() == 'w' ? "blanc" : "noir") << " de jouer." << endl;
    cout << "Il n'y a pas eu de prise ou de coup de pion depuis " << board.get_halfmove() << " coups." << endl;
    
    cout << " ----------------------------" << endl << '|' << "   a  b  c  d  e  f  g  h   " << '|' << endl;
    for(int y = 7; y >= 0; y--)
    {
        cout <<"\x1b[48;5;0m|" << y+1 << " " ;
        for(int x = 0; x < 8; x++)
        {
            print_square_color(board.get_piece(x, y), mask.get_mask(x, y) == 0 ? (x+y)%2 : mask.get_mask(x, y) + 1);
        }
        cout << "\x1b[48;5;0m ";
        cout << y+1<<'|' <<endl;
    }
    cout << '|' << "   a  b  c  d  e  f  g  h   " << '|' << endl << " ----------------------------" << endl;
}