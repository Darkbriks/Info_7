#include "view.h"
#include "type.h"
#include <iostream>
using namespace std;
void view::print_square(type::type_board B,int x,int y)// Affiche une case
{
    char G_piece = B.get_piece(x,y);
    if(G_piece== ' ')
    {
        cout << '-';
    }
    else
    {
        cout << G_piece;
    }
}
void view::print_board(type::type_board B)// Affiche le plateau
{
    if(B.get_fullmove()==1)
    {
        cout << "Board Classique : "<<endl;
    }
    else
    {
        cout << "Apres " << B.get_fullmove()<<" mouvements :"<<endl;
    }
    cout <<" ----------------------------"<<endl<< '|' <<"   a  b  c  d  e  f  g  h   "<<'|' << endl;
    for(int x = 7; x >= 0; x--)
    {
        cout <<'|' << x+1<< " ";
        for(int y = 7; y >= 0; y--)
        {
            cout << ' ';
            print_square(B, x, y);
            cout << ' ';
        }
        cout << x+1<< " "<<'|' <<endl;
    }
    cout <<" ----------------------------"<<endl<< "   a  b  c  d  e  f  g  h" << endl;
}
