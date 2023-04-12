#include <iostream>
#include <sstream>
#include "board.h"
#include "type.h"

using namespace std;

int main(int argc, char* argv[])
{
    type::type_board plateau;
    
    board board;
    board.move_piece(1, 0, 3, 0, plateau);
    board.write_fen(plateau, "fen.txt");
    board.empty_board(plateau);
    board.print_board(plateau);
    board.read_fen(plateau, "fen.txt");
    board.print_board(plateau);

    system("pause");
    return 0;
}
