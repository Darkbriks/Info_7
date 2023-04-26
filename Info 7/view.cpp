#include "view.h"
#include "type.h"
#include <iostream>

using namespace std;

void print_square(const char piece)// Affiche une case
{
    if(piece== ' ') {cout << '-';}
    else {cout << piece;}
}

void print_board(type_board B)// Affiche le plateau
{
    cout << "Tour " << B.get_fullmove() << ", C'est au " << (B.get_turn() == 'w' ? "blanc" : "noir") << " de jouer." << endl;
    cout << "Il n'y a pas eu de prise ou de coup de pion depuis " << B.get_halfmove() << " coups." << endl;
    
    cout << "-----------------------------" << endl << '|' << "  a  b  c  d  e  f  g  h   " << '|' << endl;
    for(int x = 7; x >= 0; x--)
    {
        cout <<'|' << x+1;
        for(int y = 7; y >= 0; y--)
        {
            cout << ' ';
            print_square(B.get_piece(x, y));
            cout << ' ';
        }
        cout << x+1<< " "<<'|' <<endl;
    }
    cout << '|' << "  a  b  c  d  e  f  g  h   " << '|' << endl << "-----------------------------" << endl;
}
