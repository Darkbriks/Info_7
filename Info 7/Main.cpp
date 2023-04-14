#include <iostream>
#include <sstream>
#include "board.h"
#include "type.h"
#include "view.h"

using namespace std;

int main(int argc, char* argv[])
{
    // Test some functions
    type_board plateau;
    char p[64] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
                    'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
                    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
                    'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    
    plateau.set_board_with_array(p);
    print_board(plateau);

    //plateau.set_board_with_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -- 0 1"); cout << plateau.get_fen() << endl;

    system("pause");
    return 0;
}
