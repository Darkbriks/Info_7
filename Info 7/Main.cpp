#include <iostream>
#include <sstream>
#include <array>
#include <string>
#include <cstdlib>
#include "Header/board.h"
#include "Header/game.h"
#include "Header/mask.h"
#include "Header/type.h"
#include "Header/view.h"

using namespace std;

int main(int argc, char* argv[])
{
    type_board board;
    reset_board(board);

    int p1 = 1, p2 = 1; int param = 0;
    cout << "Choose the type of the first player (1 for computer, 2 for human): "; cin >> p1;
    cout << "Choose the type of the second player (1 for computer, 2 for human): "; cin >> p2;

    while (true)
    {
        one_run(p1, &board, &param);
        if (king_in_check('b', board)) {cout << "Check, white player wins" << endl; break;}
        if (param == 1) {cout << "Les blancs abandonnent" << endl; break;}
        if (param == 2) {cout << "Les blancs proposent un match nul" << endl;}
        if (param == 3) {cout << "Les blancs acceptent le match nul" << endl; break;}
        if (param == 4) {write_fen(board, "Sauvegarde.txt"); break;}
        one_run(p2, &board, &param);
        if (king_in_check('w', board)) {cout << "Check, black player wins" << endl; break;}
        if (param == 1) {cout << "Les noirs abandonnent" << endl; break;}
        if (param == 2) {cout << "Les noirs proposent un match nul" << endl;}
        if (param == 3) {cout << "Les noirs acceptent le match nul" << endl; break;}
        if (param == 4) {write_fen(board, "Sauvegarde.txt"); break;}
    }
    
    system("pause");
    
    return 0;
}
