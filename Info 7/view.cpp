#include "view.h"
#include "type.h"
#include <iostream>
#include <string>
using namespace std;
#include <map>
//std::map<char,char> symboles={{'r','♔',{'R',""},{'n',""},{'N',""},{'b',""},{'B',""},{'q',"♛"},{'Q',""},{'k',""},{'K',""},{'p',""},{'P',""}};
std::map<char,std::string> symboles={{'r',"\0430"}};
void print_square_color(const char piece,int x,int y)// Affiche une case
{
    if(piece== ' ')
    {
        set_background(x,y);
        cout << '-';
    }
    else
    {
        set_background(x,y);
        set_foreground(piece);
    }
    cout <<" ";
}

void set_background (int x,int y)
{
    if(x%2 ==0)
    {
        y=y+1;
    }
    if(y%2 == 0)
    {
        cout << "\x1b[48;5;130m ";
    }
    else
    {
        cout << "\x1b[48;5;0m ";
    }
}

void set_foreground(const char piece)
{
    //cout << symboles[piece];
    cout << piece;
} 

void print_board(type_board B)// Affiche le plateau
{
    cout << "Tour " << B.get_fullmove() << ", C'est au " << (B.get_turn() == 'w' ? "blanc" : "noir") << " de jouer." << endl;
    cout << "Il n'y a pas eu de prise ou de coup de pion depuis " << B.get_halfmove() << " coups." << endl;
    
    cout << " ----------------------------" << endl << '|' << "   a  b  c  d  e  f  g  h   " << '|' << endl;
    for(int x = 7; x >= 0; x--)
    {
        cout <<"\x1b[48;5;0m|" << x+1 << " " ;
        for(int y = 7; y >= 0; y--)
        {
            print_square_color(B.get_piece(x, y),x,y);
        }
        cout << "\x1b[48;5;0m ";
        cout << x+1<<'|' <<endl;
    }
    cout << '|' << "   a  b  c  d  e  f  g  h   " << '|' << endl << " ----------------------------" << endl;
}
