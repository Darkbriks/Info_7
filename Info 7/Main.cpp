#include <iostream>
#include <sstream>
#include "board.h"
#include "type.h"
#include "view.h"

using namespace std;

int main(int argc, char* argv[])
{
    // Test board functions
    type_board type_board;
    type_board.set_board_with_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    print_board(type_board);
    
    system("pause");
    move_piece(1, 5, 3, 5, type_board);
    print_board(type_board);
    print_fen(type_board);
    cout << endl;
    system("pause");
    move_piece(6, 5, 4, 5, type_board);
    print_board(type_board);
    print_fen(type_board);
    cout << endl;
    system("pause");
    
    return 0;
}
