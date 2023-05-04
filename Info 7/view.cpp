#include "view.h"
#include "type.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<char,char> symbole ={{'R', 'R'},{'N', 'N'},{'B', 'B'},{'Q', 'Q'},{'K', 'K'},{'P', 'P'},{'r', 'r'},{'n', 'n'},{'b', 'b'},{'q', 'q'},{'k', 'k'},{'p', 'p'}, {' ', '-'}};
map<int, int> color_map = {{0, 0}, {1, 130}, {2, 160}, {3, 82}, {4, 214}, {5, 27}, {6, 57}, {7, 51}, {8, 153}};

void print_square_color(const char piece,const int color) {set_background(color); set_foreground(piece);}

void set_background(const int color) {string _color = "\x1b[48;5;" + to_string(color_map[color]) + "m"; cout << _color;}

void set_foreground(const char piece) {cout << ' ' << symbole[piece] << ' ';} 

void print_board(type_board board)// Affiche le plateau
{
    cout << "Tour " << board.get_fullmove() << ", C'est au " << (board.get_turn() == 'w' ? "blanc" : "noir") << " de jouer." << endl;
    cout << "Il n'y a pas eu de prise ou de coup de pion depuis " << board.get_halfmove() << " coups." << endl;
    
    cout << " ----------------------------" << endl << '|' << "   a  b  c  d  e  f  g  h   " << '|' << endl;
    for(int x = 7; x >= 0; x--)
    {
        cout <<"\x1b[48;5;0m|" << x+1 << " " ;
        for(int y = 7; y >= 0; y--)
        {
            print_square_color(board.get_piece(x, y), (x+y+1)%2);
        }
        cout << "\x1b[48;5;0m ";
        cout << x+1<<'|' <<endl;
    }
    cout << '|' << "   a  b  c  d  e  f  g  h   " << '|' << endl << " ----------------------------" << endl;
}
