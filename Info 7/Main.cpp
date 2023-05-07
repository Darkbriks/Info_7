#include <iostream>
#include <sstream>
#include "Header/board.h"
#include "Header/type.h"
#include "Header/view.h"
#include "Header/mask.h"
#include "Header/test_function.h"

using namespace std;

int main(int argc, char* argv[])
{
    /*type_board  board;
    board.set_board_with_fen("rnbqkbnr/pppppppp/8/8/3R3P/8/PPPpPpPP/4KpNR w KQkq - 0 1");
    
    type_mask mask;
    //highlight_possible_moves(0, 3, &mask, board);
    highlight_possible_moves_rook(3, 4, &mask, board);
    
    print_board(board, mask)*/

    type_board board;
    char piece[64] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
                    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
                    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                    'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
                    'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};

    char test_mask[64] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                        ' ', ' ', 'P', ' ', ' ', ' ', ' ', ' ',
                        ' ', ' ', 'R', ' ', 'p', ' ', ' ', ' ',
                        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                        ' ', ' ', ' ', ' ', ' ', 'p', ' ', ' ',
                        ' ', ' ', ' ', ' ', ' ', ' ', 'K', ' ',
                        ' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ',
                        ' ', ' ', 'p', ' ', ' ', ' ', ' ', ' '};
    board.set_board_with_fen("8/2P5/2R1p3/8/5p2/6K1/6P1/3p4 w - - 0 1");
    //board.set_board_with_array(test_mask);

    type_mask mask;
    highlight_possible_moves(2, 2, &mask, board);
    highlight_possible_moves(6, 5, &mask, board);
    
    print_board(board, mask);
        
    //test_all_type_board_getters(board);
    //system("pause");

    //test_all_type_board_setters(board);
    //system("pause");

    system("pause");
    
    return 0;
}
