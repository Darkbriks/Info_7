#include <iostream>
#include <sstream>
#include "board.h"
#include "type.h"
#include "view.h"
#include "mask.h"

using namespace std;

int main(int argc, char* argv[])
{
    type_board  board;
    board.set_board_with_fen("rnbqkbnr/pppppppp/8/8/3R3P/8/PPPpPpPP/4KpNR w KQkq - 0 1");
    
    type_mask mask;
    //highlight_possible_moves(0, 3, &mask, board);
    highlight_possible_moves_rook(3, 4, &mask, board);
    
    print_board(board, mask);

    system("pause");
    
    return 0;
}
